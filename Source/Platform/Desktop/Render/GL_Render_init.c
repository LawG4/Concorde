/**
 * Set up the GL Rendering
 */
#include <stdio.h>
#include <stdlib.h>

#include "../Desktop.h"
#include "GL_Render.h"

const uint8_t shaderCount = 1;
const char* Vertex_Shader_Name = "GLSL_Vertex.glsl";
const char* Fragment_Shader_Name = "GLSL_Fragment.glsl";

GLuint renderProgram = 0;

/*Define the forward declared vertex component arrays */
float* gl_vertex_pos = NULL;
float* gl_vertex_color = NULL;

/*Define the forward declared vertex componet mask we're using this draw*/
concorde_vertex_mask gl_internal_vertex_mask = 0;

/**
 * Searches for a shader source file and reads it in as text
 * @param shaderName The file name of the shader
 * @return The text contained in that shader
 */
char* readShaderSource(const char* shaderName) {
  FILE* fp = fopen(shaderName, "r");
  if (!fp) {
    printf("Could not open shader : %s\n", shaderName);
    return NULL;
  }

  /*Get the number of bytes in the file to reserve enough space*/
  fseek(fp, 0, SEEK_END);
  long byteCount = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  /*malloc that buffer*/
  char* buffer = calloc(byteCount, sizeof(char));
  if (!buffer) {
    printf("Failed to calloc char buffer for shader : %s\n", shaderName);
    return 0;
  }

  /*Read the file, place a null terminator at the end of string*/
  fread(buffer, sizeof(char), byteCount, fp);
  fclose(fp);
  printf("Loaded contents of shader : %s\n", shaderName);
  return buffer;
}

/**
 * If we detect an error in the shader comp, get the info log
 */
void print_shader_log(GLuint shaderID) {
  GLint logLength = 0;
  glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

  if (logLength) {
    char* log = malloc(logLength * sizeof(char));

    if (!log) {
      printf("Couldn't allocate log space for %i chars\n", logLength);
      return;
    }
    glGetShaderInfoLog(shaderID, logLength, &logLength, log);
    printf("Shader info log:\n*******\n%s\n*******\n", log);
  } else {
    printf("Couldn't fetch log length\n");
  }
}

/**
 * Generates a shader program consisting of just a vertex and fragment shader
 * @param vertex_name The local path from the executable to the vertex shader
 * source
 * @param frag_name The local path from the executable to the fragment shader
 * source
 * @returns A name used to identify the shader program within GL
 */
GLuint init_shader_program(const char* vertex_name, const char* frag_name) {
  /*Using the file path read in the shader sources*/
  char* vertSource = readShaderSource(Vertex_Shader_Name);
  char* fragSource = readShaderSource(Fragment_Shader_Name);

  /*Ensure that we did not recieve null pointers, this means we definitley read
   * some kind of shader source*/
  if (!vertSource || !fragSource) {
    printf("Error loading in the shader source code\n");
    return GL_Shader_Not_Found;
  }

  /*Create a variable to track success status*/
  GLint gl_success;

  /*Compile the vertex shader*/
  GLuint vert = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert, 1, &vertSource, NULL);
  glCompileShader(vert);

  /*Ensure shader comp was successful*/
  glGetShaderiv(vert, GL_COMPILE_STATUS, &gl_success);
  if (!gl_success) {
    printf("Error compiling the vertex shader!\n");
    print_shader_log(vert);
    return GL_Shader_comp_fail;
  }

  /*Compile the fragment shader and check for errors*/
  GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag, 1, &fragSource, NULL);
  glCompileShader(frag);

  glGetShaderiv(frag, GL_COMPILE_STATUS, &gl_success);
  if (!gl_success) {
    printf("Error compiling the fragment shader!\n");
    print_shader_log(frag);
    return GL_Shader_comp_fail;
  }

  /*Link the two shaders together to create a program*/
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vert);
  glAttachShader(shaderProgram, frag);
  glLinkProgram(shaderProgram);

  /*Check for linking success state*/
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &gl_success);
  if (!gl_success) {
    printf("Error Linking the shaders!\n");
    return GL_Shader_comp_fail;
  }

  /*Free the arrays used to store the shader source code*/
  if (vertSource) {
    free(vertSource);
  }
  if (fragSource) {
    free(fragSource);
  }

  /*Finally return the shader program*/
  return shaderProgram;
}

Concorde_GL_Render init_gl_rendering(void) {
  /*init the immediate render program which is currently our only one*/
  renderProgram = init_shader_program(Vertex_Shader_Name, Fragment_Shader_Name);

  /*Set GL to use the immediate render program*/
  glUseProgram(renderProgram);

  return 0;
}

/*When we init a render we always need to allocate enough memory from the
 * vertices*/
concorde_render_error_codes platform_render_begin(
    concorde_rendering_mode rendering_mode, concorde_primative primative,
    concorde_vertex_mask vertex_mask, uint32_t vertex_count) {
  /*Store the vertex components required for the render*/
  gl_internal_vertex_mask = vertex_mask;

  /*We always need to malloc enough space for the vertex components*/
  /*Has the user enabled positions*/
  if (vertex_mask & cvm_position) {
    /*Three floats per position vector per vertex*/
    gl_vertex_pos = malloc(3 * vertex_count * sizeof(float));
    if (!gl_vertex_pos) {
      return crec_vertex_alloc_failed;
    }
  }

  /*Has the user enabled color*/
  if (vertex_mask & cvm_color) {
    gl_vertex_color = malloc(3 * vertex_count * sizeof(float));
    if (!gl_vertex_color) {
      return crec_vertex_alloc_failed;
    }
  }
  return crec_success;
}

concorde_render_error_codes platform_render_end() {
  /*Once the render has come to an end on desktop we knowe that the vertex array
   * has been filled, so now we can make the draw call*/
  if (Concorde_current_mode == crm_immediate) {
    gl_immediate_render();
  }

  /*Free each of the vertex components allocated this draw call*/
  /*Free positions*/
  if (gl_internal_vertex_mask & cvm_position) {
    free(gl_vertex_pos);
    gl_vertex_pos = NULL;
  }

  /*Free colors*/
  if (gl_internal_vertex_mask & cvm_color) {
    free(gl_vertex_color);
    gl_vertex_color = NULL;
  }

  /*Reset the internal vertex component mask*/
  gl_internal_vertex_mask = 0;
  return crec_success;
}
