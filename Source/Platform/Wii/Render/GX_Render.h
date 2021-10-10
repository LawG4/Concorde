/**
 * This file handles the definitions for any GX rendering and then also any variables that need to be
 * made availble to the rendering pipeline
 */
#ifndef __GX_RENDER_H__
#define __GX_RENDER_H__

#include "Concorde_Render.h"

/**
 * Initialises the GX rendering pipeline, which is different from just starting GX.
 * Such as staring up the original tev stage and matricies data
 * @returns The success state of initing the renderer.
 */
concorde_render_error_codes init_gx_renderer(void);

#endif