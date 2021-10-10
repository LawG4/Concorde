/**
 * Abstracts the inputs for wii inputs.
 */
#include "Concorde.h"
#include "Concorde_Internal_Inputs.h"

#include <ogc/pad.h>
#include <wiiuse/wpad.h>


#include <stdio.h>

void concorde_scan_inputs(void)
{
    WPAD_ScanPads();
    PAD_ScanPads();

    /*Check if there was a home button pressed*/
    uint32_t wii_buttonDown = WPAD_ButtonsDown(0);
    uint16_t gc_buttonDown = PAD_ButtonsDown(0);

    buttons_downed_bit_mask |= CONCORDE_KEY_NONE;
    /*Unfortunatley we can't do switch statement, have to do if-else*/
    if (wii_buttonDown & WPAD_BUTTON_HOME || gc_buttonDown & PAD_BUTTON_START) {
        buttons_downed_bit_mask |= CONCORDE_KEY_HOME;
    }

    /*Get to the end of the buttons downed*/
    buttons_down_bit_mask |= buttons_downed_bit_mask;
}
