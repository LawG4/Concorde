/**
 * Writes the common code for the rendering systems
 */
#include <stdarg.h>

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
  concorde_render_error_codes err = platform_render_begin(
      rendering_mode, primative, vertex_mask, vertex_count);
  return err;
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
  /*Are we currently rendering?*/
  if (!Concorde_Rendering || Concorde_Vert_Remaining == 0) return crec_success;

  /*Start the indefinite length variable list*/
  float z;
  va_list vl;
  va_start(vl, y);

  /*Depending on the vertex component passed, call into a different type of
   * platform dependant rendering command*/
  concorde_render_error_codes err = crec_success;
  switch (vertex_component) {
    case cvm_position:
      /*Use variable arguments to get the third component*/
      z = va_arg(vl, float);
      err = platform_immediate_render_pos(x, y, z);
      break;
    default:
      /*Invalid vertex mask*/
      err = crec_invalid_vertex_mask;
      break;
  }
  /*Reduce the current number of vertices left to count*/
  Concorde_Vert_Remaining--;
  return err;
}
