#include "Concorde.h"

int main()
{
    /*Initialise concorde with default values*/
    concorde_init_info init = default_init_info;
    concorde_init(&init);

    /*Enter into the windowing loop*/
    while (!concorde_should_close())
    {
        /*Process inputs, including should the window close*/
        concorde_scan_inputs();

        /*Swap the framebuffers*/
        concorde_swap_buffers();
    }
}
