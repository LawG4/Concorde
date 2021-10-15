#include <stdio.h>

#include "Concorde.h"

int main()
{
    /*Initialise concorde with default values*/
    concorde_init_info init = default_init_info;
    init.fb_clear_color = concorde_pack_colors(6, 9, 48, 255);
    concorde_init(&init);

    /*Create one list for each vertex component we'd like to use*/
    float triangle_vert_pos[3][3] = {{-0.5f, -0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {0.0f, 0.9f, 0.0f}};
    float triangle_vert_col[3][3] = {{1.0, 0, 0}, {0, 1.0, 0}, {0, 0, 1.0}};

    /*Create a mask we will use to tell concorde that each vertex is contains only
     * position and colour data*/
    concorde_vertex_mask vertex_mask = cvm_position | cvm_color;

    /*Enter into the windowing loop*/
    while (!concorde_should_close()) {
        /*Process inputs, including should the window close*/
        concorde_scan_inputs();

        /*Detect if the user has pressed the home button and break*/
        if (concorde_buttons_currently_down() & CONCORDE_KEY_HOME) break;

        /*This demo will use immediate rendering, submit one vertex at a time*/
        concorde_render_begin(crm_immediate, 3, vertex_mask, cp_triangle);

        /*Submit the verices one at a time*/
        for (uint8_t i = 0; i < 3; i++) {
            concorde_immediate_vertex(cvm_position, triangle_vert_pos[i][0], triangle_vert_pos[i][1],
                                      triangle_vert_pos[i][2]);
            concorde_immediate_vertex(cvm_color, triangle_vert_col[i][0], triangle_vert_col[i][1],
                                      triangle_vert_col[i][2]);
        }

        /*End the rendering call*/
        concorde_render_error_codes err;
        if (err = concorde_render_end() != cec_success) {
            printf("Something went wrong rendering your triangle :%i\n", err);
            break;
        }

        /*Swap the framebuffers*/
        concorde_swap_buffers();
    }

    /*Clean up concorde*/
    concorde_deint();
}
