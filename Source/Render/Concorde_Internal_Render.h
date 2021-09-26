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

#endif  // !__CONCORDE_INT_RENDER_H__
