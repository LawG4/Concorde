#include "Concorde.h"
#include "Desktop.h"

SDL_Window *window;

uint8_t concorde_init(const concorde_init_info *p_init_info)
{
    /*Ensure that the pointer is valid*/
    if (!p_init_info)
        return CONCORDE_VIDEO_INIT_FAILURE;
    concorde_init_info info = *p_init_info;

    /*Init SDL*/
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return CONCORDE_VIDEO_INIT_FAILURE;

    /*Create and launch the window*/
    window = SDL_CreateWindow(info.app_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, info.fb_width,
                              info.fb_height, SDL_WINDOW_SHOWN);
    if (!window)
        return CONCORDE_VIDEO_INIT_FAILURE;

    SDL_Delay(600);
    SDL_Quit();

    return CONCORDE_SUCCESS;
}
