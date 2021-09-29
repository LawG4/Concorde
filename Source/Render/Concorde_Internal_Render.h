/**
 * Rather than wasting space on the call stack space to set render state
 * Just expose the variables directly to source files inside concorde
 */
#ifndef __CONCORDE_INT_RENDER_H__
#define __CONCORDE_INT_RENDER_H__

#include <stdbool.h>

#include "Concorde.h"
#include "Concorde_Render.h"

/*Is concorde currently trying to render?*/
extern bool Concorde_Rendering;

/*How many vertices remain to be drawn before concorde can end*/
extern uint32_t Concorde_Vert_Remaining;

/**
 * Pass on the variables for beginning the draw call passed onto the platform
 * dependant rendering system
 */
concorde_render_error_codes platform_render_begin(
    concorde_rendering_mode rendering_mode, concorde_primative primative,
    concorde_vertex_mask vertex_mask, uint32_t vertex_count);

/**
* End the platform specfic rendering call
*/
concorde_render_error_codes platform_render_end();

/**
 * Immediate rendering commands
 */

/**
 * Sets the position component for the next vertex to be drawn
 * @param x The x position
 * @param y The y position
 * @param z The z position
 * @returns A concorde rendering error code for if the draw was successful
 */
concorde_render_error_codes platform_immediate_render_pos(float x, float y,
                                                          float z);

#endif  // !__CONCORDE_INT_RENDER_H__
