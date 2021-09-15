#include "Concorde.h"

#include <gccore.h>
#include <wiiuse/wpad.h>

#include <stdio.h>

uint8_t concorde_init(const concorde_init_info *p_init_info)
{
    /*Ensure that the pointer is valid*/
    if(!p_init_info)
        return CONCORDE_VIDEO_INIT_FAILURE;

    /*Initialise the video system*/
    VIDEO_Init();

    /*Initialise any connected controllers*/
    WPAD_Init();

    /*Obtain the video settings from the Wii, this depends on the Wii's menu settings*/
    GXRModeObj *rmode = VIDEO_GetPreferredMode(NULL);

    /*Allocate memory for the framebuffer*/
    void *fb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

    /*Create a console which is required for printf*/
    console_init(fb, 10, 10, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);

    /*Set up the video registers to match the current settings*/
    VIDEO_Configure(rmode);

    /*Tell the video system where the next framebuffer is*/
    VIDEO_SetNextFramebuffer(fb);

    /*Make the display visible*/
    VIDEO_SetBlack(FALSE);

    /*Send the video settings in RAM to the video hardware*/
    VIDEO_Flush();

    /*Wait for the next vblank period which tells us video set up is done*/
    VIDEO_WaitVSync();
    if(rmode->viTVMode & VI_NON_INTERLACE) 
        VIDEO_WaitVSync();

    printf("Hello Concorde!");

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