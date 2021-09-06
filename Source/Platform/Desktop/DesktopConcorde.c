#include "Concorde.h"
#include <SDL.h>

void initConcorde()
{ /*We know we are currently on desktop*/
    SDL_Window *window;
    SDL_Surface *surface;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return -1;
    }

    window = SDL_CreateWindow("Hello!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 480, SDL_WINDOW_SHOWN);

    SDL_Delay(200);
    SDL_Quit();
}
