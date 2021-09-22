/**
 * Provide functionality for the functions declared in the public concorde_inputs.h
 */
#include "Concorde.h"
#include "Concorde_Internal_Inputs.h"
/*Internal variables that are used for keeping track*/

uint32_t buttons_downed_bit_mask = 0;
uint32_t buttons_down_bit_mask = 0;
uint32_t buttons_up_bit_mask = 0;

uint32_t concorde_buttons_downed()
{
    return CONCORDE_SUCCESS;
}

uint32_t concorde_buttons_currently_down()
{
    return CONCORDE_SUCCESS;
}

uint32_t concorde_buttons_up()
{
    return CONCORDE_SUCCESS;
}

uint8_t concorde_joystick_state(uint8_t playerID, uint8_t stickID, float *x, float *y)
{
    return CONCORDE_SUCCESS;
}
