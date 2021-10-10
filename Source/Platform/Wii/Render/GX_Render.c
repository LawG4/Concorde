/**
 * Initiates the renders and defines any forward declared internal 
 * render variables devlared in the gx rendering header
*/
#include "Wii.h"
#include "Concorde_Internal_Render.h"
#include "GX_Render.h"

#include <gccore.h>

concorde_render_error_codes init_gx_renderer(void)
{
    /*When rendering, the hardware can rasterise up to 2 different render targets 
    That is then fed into the TEV stage, which mixes those colours in some way.
    We initialise the renderer with 1 output target 
    *    In finer detail you can also specify how many texture coordinates are going 
    to be generated, these obviously corrospond to how many textures we're going
    to use.
    *    Set the number of output textures to 1, and number of textures used to 0
    by default*/
    GX_SetNumChans(1);
    GX_SetNumTexGens(0);

    /*After the colours have been rasterised, the gp goes into TEV stage which 
    composites and mixes those targets depending on what settings we put here
    The assumption is that we will only be using the first tev stage for now, 
    and we'll only be using the color output
    *    So we set everything but color to null, and we set the tev operation
    to just pass the color pixel onto the framebuffer*/
    GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    return crec_success;
}

concorde_render_error_codes platform_render_begin(
    concorde_rendering_mode rendering_mode, concorde_primative primative,
    concorde_vertex_mask vertex_mask, uint32_t vertex_count)
{
    /*Start the gx render, this promises to gx the number of vertices we'll be submitting
    If we don't submit enough then GX will hang*/

    return crec_success;
}

concorde_render_error_codes platform_render_end()
{
    return crec_success;
}