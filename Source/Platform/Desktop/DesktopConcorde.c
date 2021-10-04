#include <stdio.h>

#include "Concorde.h"
#include "Concorde_Internal_Inputs.h"
#include "Desktop.h"
#include "GL_Render.h"

/*Set Default values for the OpenGL version*/
#ifndef CONCORDE_GL_MAJOR_V
#define CONCORDE_GL_MAJOR_V 4
#endif  // !CONCORDE_GL_MAJOR_V
#ifndef CONCORDE_GL_MINOR_V
#define CONCORDE_GL_MINOR_V 4
#endif  // !CONCORDE_GL_MINOR_V

/*Declare the forward declared variables in the desktop header*/
SDL_Window *window;
SDL_GLContext sdl_GL;

/**
 * Initialises SDL2, called from concorde init
 * @param p_init_info Concorde create info passed from concorde init
 */
uint8_t init_sdl(const concorde_init_info *p_init_info) {
  /*Ensure that the pointer is valid*/
  if (!p_init_info) return CONCORDE_VIDEO_INIT_FAILURE;
  concorde_init_info info = *p_init_info;

  /*Init SDL*/
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return CONCORDE_VIDEO_INIT_FAILURE;

  /*Create and launch the window*/
  window = SDL_CreateWindow(
      info.app_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      info.fb_width, info.fb_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (!window) return CONCORDE_VIDEO_INIT_FAILURE;

  return CONCORDE_SUCCESS;
}

/**
 * Initialises OpenGL, called from concorde init
 * @param p_init_info Concorde create info passed from concorde init
 */
uint8_t init_gl(const concorde_init_info *p_init_info) {
  /*Ensure that the pointer is valid*/
  if (!p_init_info) return CONCORDE_VIDEO_INIT_FAILURE;
  concorde_init_info info = *p_init_info;

  /*Set up the context flags that lets gl use debuging*/
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

  /*Set the OpenGL Version we want to use*/
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, CONCORDE_GL_MAJOR_V);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, CONCORDE_GL_MINOR_V);

  /*Set the profile to core*/
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  /*Associate an OpenGL context to the window*/
  sdl_GL = SDL_GL_CreateContext(window);
  if (!sdl_GL) {
    printf("SDL ERROR : %s", SDL_GetError());
    return CONCORDE_VIDEO_INIT_FAILURE;
  }

  /*Init Glew*/
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    printf("GLEW error, what happened? Error code : %i", err);
    return CONCORDE_VIDEO_INIT_FAILURE;
  }

  /*Try and enable one of the debug extensions please*/
  gl_enable_callback();

  /*Try to use VSync*/
  if (SDL_GL_SetSwapInterval(1) < 0) return CONCORDE_VIDEO_INIT_FAILURE;

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  /*Extract the clear colour from the create info*/
  float R = (float)((info.fb_clear_color >> 24) & 0xFF) / (float)0xFF;
  float G = (float)((info.fb_clear_color >> 16) & 0xFF) / (float)0xFF;
  float B = (float)((info.fb_clear_color >> 8) & 0xFF) / (float)0xFF;
  float A = (float)(info.fb_clear_color & 0xFF) / (float)0xFF;

  glClearColor(R, G, B, A);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(window);

  init_gl_rendering();

  if (err = glGetError() != GL_NO_ERROR) {
    printf("GL Error detected : 0x%x \n", err);
    return CONCORDE_VIDEO_INIT_FAILURE;
  }
  return CONCORDE_SUCCESS;
}

uint8_t concorde_init(const concorde_init_info *p_init_info) {
  /*Ensure that the pointer is valid*/
  if (!p_init_info) return CONCORDE_VIDEO_INIT_FAILURE;

  uint8_t conc_err = init_sdl(p_init_info);
  if (conc_err != CONCORDE_SUCCESS) {
    printf("Concorde encountered an error while starting SDL2: \n%s\n",
           SDL_GetError());
    return conc_err;
  }

  conc_err = init_gl(p_init_info);
  if (conc_err != CONCORDE_SUCCESS) {
    printf("Concorde encountered an error while starting OpenGL\n");
    return conc_err;
  }

  return CONCORDE_SUCCESS;
}

void concorde_scan_inputs(void) {
  /*Clear the downed and upped keys from the last scan*/
  buttons_downed_bit_mask = CONCORDE_KEY_NONE;
  buttons_upped_bit_mask = CONCORDE_KEY_NONE;

  /*Get the SDL events that happened*/
  SDL_Event event;

  /*While there are buffered events to process*/
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      /*Some kind of window event*/
      case SDL_WINDOWEVENT:
        switch (event.window.event) {
          case SDL_WINDOWEVENT_CLOSE:
            should_window_close = 1;
            return; /*No need to process other events*/
          default:
            break;
        }

        /*Key down events*/
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case _CONCORDE_DESKTOP_HOME:
            buttons_downed_bit_mask |= CONCORDE_KEY_HOME;
            break;
          default:
            break;
        }
      /*Default case*/
      default:
        break;
    }
  }

  /*Set all the buttons pressed this frame as into a down state*/
  buttons_down_bit_mask |= buttons_downed_bit_mask;
}

void concorde_swap_buffers() {
  /*Swap the buffers, so we display the buffer we were just writing to*/
  SDL_GL_SwapWindow(window);

  /*Clear the buffers we're drawing to so it's fresh*/
  glClear(GL_COLOR_BUFFER_BIT);
}

void concorde_deint(void) {
  SDL_GL_DeleteContext(sdl_GL);
  SDL_DestroyWindow(window);
}
