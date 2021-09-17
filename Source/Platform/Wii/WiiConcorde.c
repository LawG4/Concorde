#include "Concorde.h"
#include "Wii.h"

#include <gccore.h>
#include <wiiuse/wpad.h>

#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*Define the forward declared variables in the wii header*/
void *gxCommandBuffer = NULL;
GXRModeObj *videoMode = NULL;
void *framebuffers[2] = {NULL, NULL};
uint8_t fbIndex = 0;

/**
 * Initialises the video system on the wii 
 */ 
uint8_t initVideo()
{
    /*Initialise the video system*/
    VIDEO_Init();

    /*Initialise any connected controllers*/
    WPAD_Init();

    /*Obtain the video settings from the Wii, this depends on the Wii's menu settings*/
    videoMode = VIDEO_GetPreferredMode(NULL);

    /*Allocate memory for the command buffer. Commands can be either 8bits or 32 bits long
    but the commands must be padded to 32 bits*/
    gxCommandBuffer = memalign(32, GX_COMMAND_BUFFER_SIZE);
    memset(gxCommandBuffer, 0, GX_COMMAND_BUFFER_SIZE);

    /*Allocate memory for the framebuffers*/
    framebuffers[0] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(videoMode));
    framebuffers[1] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(videoMode));

    /*Set up the video registers to match the current settings*/
    VIDEO_Configure(videoMode);
    /*Tell the video system where the next framebuffer is*/
    VIDEO_SetNextFramebuffer(framebuffers[fbIndex]);
    /*Make the display visible*/
    VIDEO_SetBlack(FALSE);
    /*Send the video settings in RAM to the video hardware*/
    VIDEO_Flush();

    /*Wait for the next vblank period which tells us video set up is done*/
    VIDEO_WaitVSync();
    if(videoMode->viTVMode & VI_NON_INTERLACE) 
        VIDEO_WaitVSync();

    /*We can perform a neat trick to swap the index of the framebuffer index
    And we need to swap the buffers because we just waited for Vsync*/
    fbIndex ^= 1; /*(0 -> 1) and (1 -> 0)*/

    return CONCORDE_SUCCESS;
}

/**
 * Initilises the GPU on the wii
 */ 
uint8_t initGX(const concorde_init_info *p_init_info)
{
    /*Ensure that config pointer is valid*/
    if(!p_init_info)
        return CONCORDE_VIDEO_INIT_FAILURE;

    /*Init the GPU to use our command buffer*/
    GX_Init(gxCommandBuffer, GX_COMMAND_BUFFER_SIZE);

    /*Pass the clear colour onto GX*/
    uint32_t clearColor = p_init_info->fb_clear_color;
    GXColor gxClearColor = {.r = (clearColor & 0xFF000000) >> 24,
    .g = (clearColor & 0x00FF0000) >> 16,
    .b = (clearColor & 0x0000FF00) >> 8,
    .a = clearColor & 0x000000FF};
    GX_SetCopyClear(gxClearColor, 0x00FFFFFF);


    return CONCORDE_SUCCESS;
}

uint8_t concorde_init(const concorde_init_info *p_init_info)
{
    /*initialise the video on the wii*/
    if(initVideo() != CONCORDE_SUCCESS)
        return CONCORDE_VIDEO_INIT_FAILURE;

    /*Initialise the GPU on the wii*/
    if(initGX(p_init_info) != CONCORDE_SUCCESS)
        return CONCORDE_VIDEO_INIT_FAILURE;

    /*Enter into a temp rendering loop*/
    while(1)
    {
        WPAD_ScanPads();

        VIDEO_WaitVSync();
    }

    return CONCORDE_SUCCESS;
}

void concorde_scan_inputs(void)
{

}