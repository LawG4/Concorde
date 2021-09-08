#include "Concorde.h"

/**
 * Define the forward declared variables inside the external concorde headers
 */

concorde_init_info default_init_info = {"Concorde", 640, 480, 0xFF00FFFF, true};

/**
 * Declare some of the very basic concorde functions
 */

uint32_t concorde_pack_colors(uint8_t R, uint32_t G, uint32_t B, uint32_t A)
{
    return (R << 24) | (G << 16) | (B << 8) | A;
}
