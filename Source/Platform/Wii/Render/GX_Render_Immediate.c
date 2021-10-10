/**
 * Defines the functions used for platform specific immediate rendering
 * The platform independant code already encapsulate which vertex component
 * we're rendering to.
 */
#include "Concorde_Internal_Render.h"

#include <gccore.h>

#include <stdio.h>

concorde_render_error_codes platform_immediate_render_pos(float x, float y, float z)
{
    GX_Position3f32(x, y, z);
    return crec_success;
}

concorde_render_error_codes platform_immediate_render_col(float R, float G, float B, float A)
{
    GX_Color3f32(R, G, B);
    return crec_success;
}