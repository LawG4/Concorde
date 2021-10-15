/*
 * Concorde main header file. Defines the all the things you need
 *
 */
#ifndef CONCORDE_MAIN_HEADER
#define CONCORDE_MAIN_HEADER

#include "Concorde_Enums.h"
#include "Concorde_Input_System.h"
#include "Concorde_Render.h"

#include <stdbool.h>
#include <stdint.h>

/**
 * Return states from Concorde functions
 */
#define CONCORDE_SUCCESS 0
#define CONCORDE_VIDEO_INIT_FAILURE 1

/**
 * Defines a structure used to pass paramaters to the init system
 * @param app_name The name of the application
 * @param fb_width The width of the window, ignored on Wii
 * @param fb_height The height of the window, ignored on Wii
 * @param fb_clear_color The clear color for the frame 8 bits for each channel RGBA
 * @param enable_msaa Should the implementation use anti aliasina
 */
typedef struct concorde_init_info {
    char *app_name;
    uint32_t fb_width;
    uint32_t fb_height;
    uint32_t fb_clear_color;
    bool enable_msaa;
} concorde_init_info;

/**
 * A variable containing the default values for concorde initialisation
 */
extern concorde_init_info default_init_info;

/**
 * Initialises the Concorde video system
 * @param p_init_info Pointer to the constructor setting the details
 * @return A failure code. 0 for a success
 */
uint8_t concorde_init(const concorde_init_info *p_init_info);

/**
 * Tells the user if the window has been set to close. For example, pressing x on the window. The user must
 * scan inputs to update this value. The user still maintains control of when they want the program to close
 * @return 0 if the window should close, 1 if concorde hasn't detected an exit command
 */
uint8_t concorde_should_close(void);

/**
 * Scans the inputs and stores the results in a cross platform friendly manner for the user to retrieve later
 */
void concorde_scan_inputs(void);

/**
 * Swaps the framebuffers, displays the next frame
 */
void concorde_swap_buffers(void);

/**
 * Destorys all of the resources created by concorde and exits.
 */
void concorde_deint(void);

/**
 * A simple helper function to help the user pack RGB into one int. 0-255
 * @param R Red
 * @param G Green
 * @param B Blue
 * @param A Alpha Channel
 * @return RGBA packed into a 32bit int
 */
uint32_t concorde_pack_colors(uint8_t R, uint32_t G, uint32_t B, uint32_t A);
#endif
