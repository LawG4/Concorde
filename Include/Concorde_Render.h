/**
 * Concorde rendering abstraction layer. We allow the user to do 2 types of
 * rendering
 * Immediate rendering : where you submit a vertex once at a time
 * Buffered rendering  : where you submit an ordered array of vertices
 * Indexed rendering   : where you submit a vertex buffer ordered by the indices
 *						 in an index buffer
 *
 */
#ifndef __CONCORDE_RENDER_H__
#define __CONCORDE_RENDER_H__

#include <stdint.h>

/*Define the different styles of rendering concorde will let a user do*/
typedef enum {
  /*Submit each vertex point component one at a time in order*/
  crm_immediate,
  /*Submit a buffer of ordered vertices*/
  crm_buffered,
  /*Submit a buffer of vertices access by the order described in the index
     buffer*/
  crm_indexed
} concorde_rendering_mode;

/*Define a list of all the primatives concorde will let you render*/
typedef enum { cp_triangle = 3, cp_quad = 4 } concorde_primative;

/*Define flags that tell concorde which properties the users vertices have*/
typedef enum {
  cvm_position = 1,
  cvm_color = 1 << 1,
  cvm_tex = 1 << 2
} concorde_vertex_mask;

typedef enum {
  crec_success = 0,
  crec_already_rendering,
  crec_not_finished_rendering,
  crec_invalid_vertex_mask,
  crec_vertex_alloc_failed

} concorde_render_error_codes;

/**
 * Starts the concorde draw call
 * @param rendering_mode Type of concorde rendering the user would like to use
 * see enum concorde_rendering_mode
 * @param primative The primative the user is using, see enum concorde_primative
 * @param vertex_mask Which features the vertices have, ie texture or color
 * coords
 * @param vertex_count How many vertices the user is submitting
 * @returns a render error code or success
 */
concorde_render_error_codes concorde_render_begin(
    concorde_rendering_mode rendering_mode, concorde_primative primative,
    concorde_vertex_mask vertex_mask, uint32_t vertex_count);

/**
 * Ends the concorde draw call, validates the user has submitted enough vertices
 * @returns 0 if the draw call was successful or else an error code.
 */
concorde_render_error_codes concorde_render_end(void);

/*Define the functions needed for specific types of rendering*/

/**
 * Submits a vertex component directly to the graphics proccessor
 * @param vertex_component Which component of the vertex we're writing this data
 * for
 * @param x First subsection of the vertex component
 * @param y second subsection of the vertex component
 * @param ... Any remaining sections of the vertex component
 */
concorde_render_error_codes concorde_immediate_vertex(
    concorde_vertex_mask vertex_component, float x, float y, ...);

#endif  // !__CONCORDE_RENDER_H__
