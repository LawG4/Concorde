/**
 * Adds the GL implementation for the immediate rendering commands
 */
#include <stdio.h>

#include "Concorde.h"
#include "Concorde_Internal_Render.h"
#include "Concorde_Render.h"
#include "GL_Render.h"

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
