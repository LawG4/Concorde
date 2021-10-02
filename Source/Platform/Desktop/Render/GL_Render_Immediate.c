/**
 * Adds the GL implementation for the immediate rendering commands
 */
#include <stdio.h>

#include "../Desktop.h"
#include "Concorde.h"
#include "Concorde_Internal_Render.h"
#include "Concorde_Render.h"
#include "GL_Render.h"

GLuint immediate_vao = 0;
GLuint* immediate_vbo;
concorde_vertex_mask previous_vm = 0;

void gl_immediate_render() {
  /*Check that the vertex array has been generated yet*/
  if (!immediate_vao) {
    glGenVertexArrays(1, &immediate_vao);

    /*Allocate enough space for the immediare vbos*/
    const uint32_t supportedAttributeCount = 2;
    immediate_vbo = malloc(supportedAttributeCount * sizeof(GLuint));
    if (!immediate_vbo) {
      return;
    }
    glGenBuffers(supportedAttributeCount, immediate_vbo);
  }
  glBindVertexArray(immediate_vao);

  /*The immediate renderer needs to reset the enabled attrubtes when they
   * change*/
  if (Concorde_current_vm != previous_vm) {
  }

  /*Save the previous vm before returning*/
  previous_vm = Concorde_current_vm;
}

concorde_render_error_codes platform_immediate_render_pos(float x, float y,
                                                          float z) {
  printf("Draw vertex pos[%i] :(%f, %f, %f)\n", Concorde_immediate_index, x, y,
         z);
  return crec_success;
}

concorde_render_error_codes platform_immediate_render_col(float R, float G,
                                                          float B, float A) {
  printf("Draw vertex col[%i] :(%f, %f, %f, %f)\n", Concorde_immediate_index, R,
         G, B, A);
  return crec_success;
}
