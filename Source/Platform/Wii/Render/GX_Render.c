/**
 * Initiates the renders and defines any forward declared internal
 * render variables devlared in the gx rendering header
 */
#include "GX_Render.h"
#include "Concorde_Internal_Render.h"
#include "Wii.h"

#include <gccore.h>

concorde_render_error_codes init_gx_renderer(void)
{
    /*When we start the Concorde renderer, we're assuming that the user will be using direct
    rendering with only colour and position data for each vertex. If they want to change this
    then they will be able to do this, with commands which haven't been defined yet.
    *    We're starting the renderer with the assumption of a simple vertex format so that
    users just trying out concorde can get up and running with less set up.*/
    GX_ClearVtxDesc();
    GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);

    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGB8, 0);

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

    /*Once again the renderer init has some assumptions about the users input
    style for their vertices, we assume that they're just trying to submit
    screenspace coordinates, so we load dummy position and projection mats*/
    Mtx44 projec;
    float aspectRatio = (float)videoMode->viWidth / (float)videoMode->viHeight;
    guPerspective(projec, 45, aspectRatio, 0.1f, 300.0f);
    GX_LoadProjectionMtx(projec, GX_PERSPECTIVE);

    guVector cam = {0.0F, 0.0F, 0.0F}, up = {0.0F, 1.0F, 0.0F}, look = {0.0F, 0.0F, -1.0F};
    Mtx viewMat;
    guLookAt(viewMat, &cam, &up, &look);
    guMtxTransApply(viewMat, viewMat, 0.0f, 0.0f, -2.5f);

    GX_LoadPosMtxImm(viewMat, GX_PNMTX0);

    return cec_success;
}

concorde_render_error_codes platform_render_begin(concorde_rendering_mode rendering_mode,
                                                  concorde_primative primative,
                                                  concorde_vertex_mask vertex_mask, uint32_t vertex_count)
{
    /*TODO: */
    /*We need to implement a system that will switch up the vertex formats depending
    on what information the user is submitting here, right now this only works under
    the assumption that the user is submitting vertices in the default manner*/

    /*Start the gx render, this promises to gx the number of vertices we'll be submitting
    If we don't submit enough then GX will hang*/
    GX_Begin(GX_TRIANGLES, GX_VTXFMT0, vertex_count);

    return cec_success;
}

concorde_render_error_codes platform_render_end()
{
    /*End the GX render cycle, remember if we haven't submitted enough vertices GX will hang*/
    GX_End();
    return cec_success;
}