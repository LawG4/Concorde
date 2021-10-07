/**
 * Initiates the renders and defines any forward declared internal 
 * render variables devlared in the gx rendering header
*/

#include "Concorde_Internal_Inputs.h"

concorde_render_error_codes platform_render_begin(
    concorde_rendering_mode rendering_mode, concorde_primative primative,
    concorde_vertex_mask vertex_mask, uint32_t vertex_count)
{
    return crec_success;
}

concorde_render_error_codes platform_render_end()
{
    return crec_success;
}