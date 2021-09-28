/**
 * Adds the GL implementation for the immediate rendering commands
 */
#include "Concorde.h"
#include "Concorde_Internal_Render.h"
#include "Concorde_Render.h"

concorde_render_error_codes platform_immediate_render_pos(float x, float y,
                                                          float z) {
  return crec_success;
}
