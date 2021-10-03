/**
 * GL Rendering initialisation, checks that we have vertex attributes
 * and other things like reading in all the shaders and what have you
 */
#ifndef __GL_RENDER_H__
#define __GL_RENDER_H__

/*Include all the common headers we need*/
#include "Concorde.h"
#include "Concorde_Internal_Render.h"
#include "Concorde_Render.h"

/*Declarations for rendering exclusively on desktop*/
typedef enum { GL_Success = 0, GL_Shader_Not_Found } Concorde_GL_Render;

/*Shader names*/
extern const uint8_t shaderCount;
extern const char* ShaderNames[1];

/**
 * pointer that represents the list of vertices positions we're gonna render
 */
extern float* gl_vertex_pos;

/**
 * Checks that all of the shaders have been found
 * and that yourr gl has enough vertex attributes
 */
Concorde_GL_Render init_gl_rendering(void);

/**
* Takes the current state encapsualted in gl_concorde and calls the gl draw
*/
void gl_immediate_render();

/**
 * Outputs any GL Errors if there are any
 * @param check_point Where the gl check originated from
 */
void gl_debug_out(const char* check_point);
#endif  // !__GL_RENDER_H__
