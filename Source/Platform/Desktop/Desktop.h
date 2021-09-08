/**
 * All of the variables that we need to pass amungst the desktop platforms
 */
#ifndef CONCORDE_DESKTOP_HEADER
#define CONCORDE_DESKTOP_HEADER

/**
 * Temporarily ignore some compiler warnings
 *   4099  : "No PDB linking object" (This is because GLEW is a release library)
 *   4098  : "LIBCMT cinflicts with use of other libs
 *	26812  : "SDL_bool is unscoped prefer class enum over enum" (No classes in C?)
 */
#pragma warning(disable : 4099)
#pragma warning(disable : 4098)
#pragma warning(disable : 26812)
/*Tell Glew we're using the static library*/
#define GLEW_STATIC 1
#include <GL/glew.h>
#include <SDL.h>

/*Return error states*/
#pragma warning(default : 4099)
#pragma warning(default : 4098)
#pragma warning(default : 26812)

/**
 * An opaque handle for the SDL window
 */
extern SDL_Window *window;

/**
 * An opaque handle for the OpenGL context
 */
SDL_GLContext sdl_GL;

#endif // !CONCORDE_DESKTOP_HEADER
