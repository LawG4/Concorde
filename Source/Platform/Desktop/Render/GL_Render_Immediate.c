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
    glBindVertexArray(immediate_vao);

    /*Create one vertex buffer object for each vertex component*/
    glGenBuffers(supportedAttributeCount, immediate_vbo);

    /*Position data which is attribute 0 and made up of 3 floats*/
    glEnableVertexAttribArray(__GL_VC_POS);
    glBindBuffer(GL_ARRAY_BUFFER, immediate_vbo[__GL_VC_POS]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    /*Color data which is attribute 1 and made up of 3 floats*/
    glEnableVertexAttribArray(__GL_VC_COL);
    glBindBuffer(GL_ARRAY_BUFFER, immediate_vbo[__GL_VC_COL]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    /*Unbind from the vertex buffers*/
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(immediate_vao);

  /*Dependending on the currently bound vertex components buffer the data we
   * have built up*/
  /*Enabled position component*/
  if (Concorde_current_vm & cvm_position) {
    glEnableVertexAttribArray(__GL_VC_POS);
    glBindBuffer(GL_ARRAY_BUFFER, immediate_vbo[__GL_VC_POS]);
    glBufferData(GL_ARRAY_BUFFER, Concorde_immediate_index * 3 * sizeof(float),
                 gl_vertex_pos, GL_STATIC_DRAW);
  }
  /*Enabled color component*/
  if (Concorde_current_vm & cvm_color) {
    glEnableVertexAttribArray(__GL_VC_POS);
    glBindBuffer(GL_ARRAY_BUFFER, immediate_vbo[__GL_VC_COL]);
    glBufferData(GL_ARRAY_BUFFER, Concorde_immediate_index * 3 * sizeof(float),
                 gl_vertex_color, GL_STATIC_DRAW);
  }

  /*Do the draw call*/
  glDrawArrays(GL_TRIANGLES, 0, Concorde_immediate_index);

  /*Save the previous vm before returning*/
  previous_vm = Concorde_current_vm;
}

concorde_render_error_codes platform_immediate_render_pos(float x, float y,
                                                          float z) {
  gl_vertex_pos[Concorde_immediate_index * 3 + 0] = x;
  gl_vertex_pos[Concorde_immediate_index * 3 + 1] = y;
  gl_vertex_pos[Concorde_immediate_index * 3 + 2] = z;
  return crec_success;
}

concorde_render_error_codes platform_immediate_render_col(float R, float G,
                                                          float B, float A) {
  gl_vertex_color[Concorde_immediate_index * 3 + 0] = R;
  gl_vertex_color[Concorde_immediate_index * 3 + 1] = G;
  gl_vertex_color[Concorde_immediate_index * 3 + 2] = B;
  return crec_success;
}
