/**
 * Writes the common code for the rendering systems
 */
#include "Concorde.h"
#include "Concorde_Internal_Render.h"
#include "Concorde_Render.h"

/*Define the forward declared render state tracking variables*/
bool Concorde_Rendering = false;
uint32_t Concorde_Vert_Remaining = 0;

/*Provide a wrapper for the external rendering functions*/

concorde_render_error_codes concorde_render_begin(
    concorde_rendering_mode rendering_mode, concorde_primative primative,
    concorde_vertex_mask vertex_mask, uint32_t vertex_count) {
  /*Check concorde isn't already rendering something else*/
  if (Concorde_Rendering) {
    return crec_already_rendering;
  }
  Concorde_Rendering = true;
  Concorde_Vert_Remaining = vertex_count;

  /*Call into the platform specific rendering function*/
  /*Todo implement this bad boi*/

  return crec_success;
}

concorde_render_error_codes concorde_render_end(void) {
  /*Is concorde even rendering?*/
  if (!Concorde_Rendering) {
    return crec_already_rendering;
  }
  /*Assume the user has done this correctly until proven otherwise*/
  concorde_render_error_codes err = crec_success;

  /*Has the user submitted enough vertices?*/
  if (Concorde_Vert_Remaining != 0) {
    err = crec_not_finished_rendering;
    /*Somehow recover from this?*/
  }

  /*Call the platform specific end rendering function*/

  /*Exit out*/
  Concorde_Rendering = false;
  Concorde_Vert_Remaining = 0;
  return err;
}

concorde_render_error_codes concorde_immediate_vertex(
    concorde_vertex_mask vertex_component, float x, float y, ...) {
  return crec_success;
}
