#include "Concorde.h"
#include "ConcordeInternal.h"

/**
 * Define the forward declared variables inside the external concorde headers
 */

concorde_init_info default_init_info = {"Concorde", 640, 480, 0xFF00FFFF, true};

uint8_t should_window_close = 0;

/**
 * Declare some of the very basic concorde functions
 */

uint8_t concorde_should_close(void) { return should_window_close; }

uint32_t concorde_pack_colors(uint8_t R, uint32_t G, uint32_t B, uint32_t A)
{
    return (R << 24) | (G << 16) | (B << 8) | A;
}
