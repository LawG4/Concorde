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
  Immediate,
  /*Submit a buffer of ordered vertices*/
  Buffered,
  /*Submit a buffer of vertices access by the order described in the index
     buffer*/
  Indexed
} concorde_rendering_mode;

/*Define a list of all the primatives concorde will let you render*/
typedef enum { Triangle, Quad } concorde_primative;

/*Define flags that tell concorde which properties the users vertices have*/
typedef enum {
  Position = 1,
  Color = 1 << 1,
  Tex = 1 << 2
} concorde_vertex_mask;

/**
 * Starts the concorde draw call
 * @param rendering_mode Type of concorde rendering the user would like to use
 * see enum concorde_rendering_mode
 * @param primative The primative the user is using, see enum concorde_primative
 * @param vertex_mask Which features the vertices have, ie texture or color
 * coords
 * @param vertex_count How many vertices the user is submitting
 */
void concorde_render_begin(concorde_rendering_mode rendering_mode,
                           concorde_primative primative,
                           concorde_vertex_mask vertex_mask,
                           uint32_t vertex_count);

/**
 * Ends the concorde draw call, validates the user has submitted enough vertices
 * @returns 0 if the draw call was successful or else an error code.
 */
uint8_t concorde_render_end(void);

/*Define the functions needed for specific types of rendering*/

/**
 * Submits a vertex component directly to the graphics proccessor
 * @param vertex_component Which component of the vertex we're writing this data
 * for
 * @param x First subsection of the vertex component
 * @param y second subsection of the vertex component
 * @param ... Any remaining sections of the vertex component
 */
void concorde_immediate_vertex(concorde_vertex_mask vertex_component, float x,
                               float y, ...);

#endif  // !__CONCORDE_RENDER_H__
