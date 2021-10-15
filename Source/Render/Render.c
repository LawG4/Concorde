/**
 * Writes the common code for the rendering systems
 */
#include <stdarg.h>

#include "Concorde.h"
#include "Concorde_Internal_Render.h"
#include "Concorde_Render.h"

/*Define the forward declared render state tracking variables*/
bool Concorde_Rendering = false;
concorde_rendering_mode Concorde_current_mode = 0;
concorde_vertex_mask Concorde_current_vm = 0;
uint32_t Concorde_Vert_Remaining = 0;
uint32_t Concorde_vert_comps = 0;
uint32_t Concorde_immediate_index = 0;

/*Provide a wrapper for the external rendering functions*/

concorde_render_error_codes concorde_render_begin(concorde_rendering_mode rendering_mode,
                                                  concorde_primative primative,
                                                  concorde_vertex_mask vertex_mask, uint32_t vertex_count)
{
    /*Check concorde isn't already rendering something else*/
    if (Concorde_Rendering) {
        return cec_already_rendering;
    }
    Concorde_Rendering = true;

    /*Keep track of which type of rendering we're doing*/
    Concorde_current_mode = rendering_mode;
    Concorde_current_vm = vertex_mask;

    /*We need to see how many bits are set in the vertex mask so we can count how
     * many vertex components remain*/
    Concorde_vert_comps = 0;
    concorde_vertex_mask vm = vertex_mask;
    while (vm) {
        Concorde_vert_comps += 1 & vm;
        vm >>= 1;
    }
    Concorde_Vert_Remaining = vertex_count * Concorde_vert_comps;
    Concorde_immediate_index = 0;

    /*Call into the platform specific rendering function*/
    concorde_render_error_codes err =
      platform_render_begin(rendering_mode, primative, vertex_mask, vertex_count);
    return err;
}

concorde_render_error_codes concorde_render_end(void)
{
    /*Is concorde even rendering?*/
    if (!Concorde_Rendering) {
        return cec_already_rendering;
    }
    /*Assume the user has done this correctly until proven otherwise*/
    concorde_render_error_codes err = cec_success;

    /*Has the user submitted enough vertices?*/
    if (Concorde_Vert_Remaining != 0) {
        err = cec_not_finished_rendering;
        /*Somehow recover from this?*/
    }

    /*Call the platform specific end rendering function*/
    err = platform_render_end();
    /*Exit out*/
    Concorde_Rendering = false;
    Concorde_Vert_Remaining = 0;
    return err;
}

concorde_render_error_codes concorde_immediate_vertex(concorde_vertex_mask vertex_component, float x, float y,
                                                      ...)
{
    /*Are we currently rendering?*/
    if (!Concorde_Rendering || Concorde_Vert_Remaining == 0) return cec_success;

    /*Start the indefinite length variable list*/
    float z;
    float w;
    va_list vl;
    va_start(vl, y);

    /*Depending on the vertex component passed, call into a different type of
     * platform dependant rendering command*/
    concorde_render_error_codes err = cec_success;
    switch (vertex_component) {
        case cvm_position:
            /*Use variable arguments to get the third component*/
            z = (float)va_arg(vl, double);
            err = platform_immediate_render_pos(x, y, z);
            break;

        case cvm_color:
            /*Get the colour components*/
            z = (float)va_arg(vl, double);
            w = (float)va_arg(vl, double);
            err = platform_immediate_render_col(x, y, z, w);

        default:
            /*Invalid vertex mask*/
            err = cec_invalid_vertex_mask;
            break;
    }

    /*Reduce the current number of vertices left to count*/
    Concorde_Vert_Remaining--;

    /*Advance the vertex index if we've added enough components for this vertex*/
    if ((Concorde_Vert_Remaining % Concorde_vert_comps) == 0) {
        Concorde_immediate_index++;
    }

    return err;
}
