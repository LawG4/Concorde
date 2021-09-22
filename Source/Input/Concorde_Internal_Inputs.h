/**
 * Rather than wasting space on the call stack space to set buttons
 * Just expose the variables directly to source files inside concorde
 */
#ifndef __CONCORDE_INT_INPUTS_H__
#define __CONCORDE_INT_INPUTS_H__
#include "Concorde.h"

/*Buttons that have been pressed in the most recent input scan*/
extern uint32_t buttons_downed_bit_mask;

/*Buttons currently held down*/
extern uint32_t buttons_down_bit_mask;

/*Buttons that have been released in the most recent input scan*/
extern uint32_t buttons_upped_bit_mask;

#endif // !__CONCORDE_INT_INPUTS_H__
