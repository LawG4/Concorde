#include "Concorde.h"
#include "Wii.h"
#include "GX_Render.h"

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
    PAD_Init();

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
    GXColor gxClearColor = {.r = (clearColor >> 24) & 0xFF,
    .g = (clearColor >> 16) & 0xFF,
    .b = (clearColor >> 8) & 0xFF,
    .a = clearColor & 0xFF};
    GX_SetCopyClear(gxClearColor, 0x00FFFFFF);

    /*Tell the GP about the dimensions of the internal framebuffer, including depth buffer*/
    GX_SetViewport(0, 0, videoMode->fbWidth, videoMode->efbHeight, 0, 1);

    /*Get the scale values to go from internal and external framebuffers*/
    float yscale = GX_GetYScaleFactor(videoMode->efbHeight, videoMode->xfbHeight);
    
    /*Tell GX about how we're copying the internal/embedded framebuffer to the external one
    This happens when the frame is finished being rendered to the internal/embedded fb and 
    we want to copy the result to an external fb in main memory so it can be displayed
    in order of the following calls we are:
    *    Setting the horizontal scale value between internal and external
    *    Tell the copy operation the internal framebuffer dimensions
    *    Tell the copy operarion the external fb dimensions *
    *    Tell the copy operation the paramaters for converting subpixels to pixels, like
    defining a sampler in Vulkan
    *    Are we using field rendering, no idea? I yoinked this one from the examples
    *    Set any gamma correction, so maybe efb is linear colour space and efb isnt?*/
    float externalFBHeight = GX_SetDispCopyYScale(yscale);
    GX_SetDispCopySrc(0, 0, videoMode->fbWidth, videoMode->efbHeight);
    GX_SetDispCopyDst(videoMode->fbWidth, externalFBHeight);
    GX_SetCopyFilter(videoMode->aa, videoMode->sample_pattern, GX_TRUE, videoMode->vfilter);
    GX_SetFieldMode(videoMode->field_rendering, (videoMode->viHeight == 2*videoMode->xfbHeight) ? GX_ENABLE: GX_DISABLE);
    GX_SetDispCopyGamma(GX_GM_1_0);

    /*Tell GX how to handle vertex culling, scissor snips verticies after being transfrmed 
    into screen space, to reduce texturing unneccacary vertices.
    *    We can also tell when to kill verticies so that their insides aren't textured, but 
    since we're still in very early debug, default to no vertex culling*/
    GX_SetScissor(0, 0, videoMode->fbWidth, videoMode->efbHeight);
    GX_SetCullMode(GX_FALSE);

    /*Start the renderer*/
    if(init_gx_renderer() != crec_success)
    {
        printf("Failed to init the concorde gx renderer!\n");
        return CONCORDE_VIDEO_INIT_FAILURE;
    }

    /*Run through framebuffers before turning the screen on as GX initialises as green*/
    concorde_swap_buffers();
    concorde_swap_buffers();
    VIDEO_SetBlack(FALSE);

    

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

    return CONCORDE_SUCCESS;
}

void concorde_swap_buffers(void)
{
    /*The GX draw has been complete*/
    GX_DrawDone();

    /*Copy the internal framebuffer (The one in the GPUs ram) into our external framebuffer
    So we can send the contents of that framebuffer to the screen
    Also clear the internal framebuffer while we're at it so that it's fresh*/
    GX_CopyDisp(framebuffers[fbIndex], GX_TRUE);

    /*Tell the video hardware where the next framebuffer is*/
    VIDEO_SetNextFramebuffer(framebuffers[fbIndex]);
    VIDEO_Flush();

    /*Wait for the next frame*/
    VIDEO_WaitVSync();
    fbIndex ^= 1;
}

void concorde_deint(void)
{
    /*Wait for the current frame to end and then make the exit*/
    VIDEO_WaitVSync();
}