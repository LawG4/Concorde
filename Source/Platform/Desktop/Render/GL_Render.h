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
typedef enum { Success = 0, Shader_Not_Found } Concorde_GL_Render;

#endif  // !__GL_RENDER_H__
