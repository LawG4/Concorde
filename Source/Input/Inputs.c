/**
 * Provide functionality for the functions declared in the public concorde_inputs.h
 */
#include "Concorde.h"
#include "Concorde_Internal_Inputs.h"
/*Internal variables that are used for keeping track*/

uint32_t buttons_downed_bit_mask;
uint32_t buttons_down_bit_mask;
uint32_t buttons_upped_bit_mask;

uint32_t concorde_buttons_downed() { return buttons_downed_bit_mask; }

uint32_t concorde_buttons_currently_down() { return buttons_down_bit_mask; }

uint32_t concorde_buttons_up() { return buttons_upped_bit_mask; }

uint8_t concorde_joystick_state(uint8_t playerID, uint8_t stickID, float *x, float *y)
{
    return CONCORDE_SUCCESS;
}
