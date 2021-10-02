/**
 * Set up the GL Rendering
 */
#include <stdlib.h>

#include "GL_Render.h"

const uint8_t shaderCount = 1;
const char* ShaderNames[1] = {"Test shader.glsl"};

/*Define the forward declared vertex component arrays */
float* gl_vertex_pos = NULL;

/*Define the forward declared vertex componet mask we're using this draw*/
concorde_vertex_mask gl_internal_vertex_mask = 0;

Concorde_GL_Render init_gl_rendering(void) { return GL_Success; }

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
  /*Free each of the vertex components allocated this draw call*/
  if (gl_internal_vertex_mask & cvm_position) {
    free(gl_vertex_pos);
    gl_vertex_pos = NULL;
  }

  /*Reset the internal vertex component mask*/
  gl_internal_vertex_mask = 0;
  return crec_success;
}
