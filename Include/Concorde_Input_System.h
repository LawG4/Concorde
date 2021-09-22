/**
 * Provides a general abstraction away for handeling all the different input devices
 * This involves an internal state tracking of all the devices plugged in, and
 * abstracting all their different inputs together into one common input presentation
 *	i.e. If a player uses a Gamecube controller, or a nunchuck, moving the joystick
 *	will be presented to users of concorde lib the same.
 *
 *
 * On wii this will be tracking and scanning all the current controllers and ensuring
 * that they have the right connected devices.
 *
 * On Desktop there will be a list of user defines that will map an SDL keyevent onto
 * each type of Wii input. Since we're trying to deply on Wii, we don't need much
 * flexibility for dekstop inputs, and we can ask the user to hardcode them in this
 * header.
 */

#ifndef __CONCORDE_INPUT_SYSTEM_H__
#define __CONCORDE_INPUT_SYSTEM_H__
#include <stdint.h>
/**
 * List the possible Wii mote inputs as SDL desktop keys, these will then get translated
 * inside the desktop concorde system
 *
 * The wiimotes gyroscope will be interpreted as mapping the mouse
 */

/*The key that simulates pressing home on a wii-mote*/
#define _CONCORDE_DESKTOP_HOME SDLK_RETURN

/**
 * Returns the concorde buttons that have been pressed down during the last scanned inputs
 * @return A bitmask of all the buttons put into down in the most recent input scan
 */
uint32_t concorde_buttons_downed();

/**
 * Returns a bitmask of all the buttons that have been pressed and not released
 * @return A bitmask of all the buttons put into down, but not released
 */
uint32_t concorde_buttons_currently_down();

/**
 * Returns all the buttons released in the last scan inputs call
 * @return A bitmask of all buttons released in the last scan
 */
uint32_t concorde_buttons_up();

/**
 * Takes a reference to some floats and fills them with the offset from the centre of
 * the specified joystick. The offset is normalised, [-1 - 0 - 1]
 * @param playerID Which remote the user is reading
 * @param stickID Which joystick the user is reading, 0 for primary 1 for secondary
 * @param x Pointer which is set to the signed offset of the joystick from the centre
 * @param y Pointer which is set to the signed offset of the joystick from the centre
 * @return CONCORDE_SUCCESS if nothing went wrong
 */
uint8_t concorde_joystick_state(uint8_t playerID, uint8_t stickID, float *x, float *y);

/**
 * Define the concorde keykoads for buttons pressed
 */
#define CONCORDE_KEY_NONE (0)
#define CONCORDE_KEY_HOME (1)

#endif // !__CONCORDE_INPUT_SYSTEM_H__
