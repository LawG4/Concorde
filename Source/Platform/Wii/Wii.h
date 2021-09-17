/**
 * All of the variables that we need to pass across the wii files
 */
#ifndef __CONCORDE_WII_HEADER__
#define __CONCORDE_WII_HEADER__

#include <gccore.h>

/**
 * Define the size of the GPUs command buffer
 */ 
#define GX_COMMAND_BUFFER_SIZE (256*1024)

/**
 * Allocate memory for the command buffer to send instructions to the GPU
 */ 
extern void *gxCommandBuffer;

/**
 * The video mode for wii, that's resolution, refresh rate etc...
 * This comes from the Wii settings menu and the device connected
 */ 
extern GXRModeObj *videoMode;

/**
 * Allocate memory for the framebuffers. Have two to swap between, one to draw to and one to display 
 */ 
extern void *framebuffers[2];

/**
 * Which framebuffer we are currently drawing to
 */ 
extern uint8_t fbIndex;

#endif