#include "Concorde.h"

int main()
{
    /*Initialise concorde with default values*/
    concorde_init_info init = default_init_info;
    concorde_init(&init);

    /*Enter into the windowing loop*/
    while (!concorde_should_close()) {
        /*Process inputs, including should the window close*/
        concorde_scan_inputs();

        /*Detect if the user has pressed the home button and break*/
        if (concorde_buttons_currently_down() & CONCORDE_KEY_HOME) break;

        /*Swap the framebuffers*/
        concorde_swap_buffers();
    }

    /*Clean up concorde*/
    concorde_deint();
}
