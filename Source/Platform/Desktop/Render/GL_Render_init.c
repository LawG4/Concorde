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

Concorde_GL_Render init_gl_rendering(void) {
  /*Firstly read in the shader source codes*/
  char* vertSource = readShaderSource(Vertex_Shader_Name);
  char* fragSource = readShaderSource(Fragment_Shader_Name);

  /*Ensure we retrieved some data*/
  if (!vertSource || !fragSource) {
    printf("Error loading in the shader source code\n");
    return GL_Shader_Not_Found;
  }

  /*Compile the vertex source code into a shader*/
  GLuint vert = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert, 1, &vertSource, NULL);
  glCompileShader(vert);

  /*Ensure the compilation was successful*/
  GLint gl_success;
  glGetShaderiv(vert, GL_COMPILE_STATUS, &gl_success);
  if (!gl_success) {
    printf("Error compiling the vertex shader!\n");
    return GL_Shader_comp_fail;
  }

  /*Compile the fragment source code shader*/
  GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag, 1, &fragSource, NULL);
  glCompileShader(frag);

  glGetShaderiv(frag, GL_COMPILE_STATUS, &gl_success);
  if (!gl_success) {
    printf("Error compiling the fragment shader!\n");
    return GL_Shader_comp_fail;
  }

  /*Link the two shaders together to create a program*/
  renderProgram = glCreateProgram();
  glAttachShader(renderProgram, vert);
  glAttachShader(renderProgram, frag);
  glLinkProgram(renderProgram);

  glGetShaderiv(renderProgram, GL_LINK_STATUS, &gl_success);
  if (!gl_success) {
    printf("Error Linking the shaders!\n");
    return GL_Shader_comp_fail;
  }

  glUseProgram(renderProgram);

  /*Free our char buffers*/
  free(vertSource);
  free(fragSource);

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
  if (vertex_mask & cvm_position) {
    /*Three floats per position vector per vertex*/
    gl_vertex_pos = malloc(3 * vertex_count * sizeof(float));
    if (!gl_vertex_pos) {
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
  if (gl_internal_vertex_mask & cvm_position) {
    free(gl_vertex_pos);
    gl_vertex_pos = NULL;
  }

  /*Reset the internal vertex component mask*/
  gl_internal_vertex_mask = 0;
  return crec_success;
}
