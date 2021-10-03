/**
 * Set up the GL Rendering
 */
#include <stdio.h>
#include <stdlib.h>

#include "../Desktop.h"
#include "GL_Render.h"

const uint8_t shaderCount = 1;
const char* ShaderNames[1] = {"Test shader.glsl"};

GLuint renderProgram = 0;

/*Define the forward declared vertex component arrays */
float* gl_vertex_pos = NULL;

/*Define the forward declared vertex componet mask we're using this draw*/
concorde_vertex_mask gl_internal_vertex_mask = 0;

Concorde_GL_Render init_gl_rendering(void) {
  /*Create some basic shaders*/
  const char* vertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";
  const char* fragmentShaderSource =
      "#version 330 core\n"
      "out vec4 FragColor;\n"
      "void main()\n"
      "{\n"
      "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}\0";

  /*Vertex program*/
  GLuint vertexProgram = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexProgram, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexProgram);

  /*Fragment program*/
  GLuint fragProgram = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragProgram, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragProgram);

  renderProgram = glCreateProgram();

  glAttachShader(renderProgram, vertexProgram);
  glAttachShader(renderProgram, fragProgram);
  glLinkProgram(renderProgram);
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
