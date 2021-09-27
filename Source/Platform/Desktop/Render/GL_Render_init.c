/**
 * Set up the GL Rendering
 */
#include "GL_Render.h"

const uint8_t shaderCount = 1;
const char* ShaderNames[1] = {"Test shader.glsl"};

Concorde_GL_Render init_gl_rendering(void) { return GL_Success; }
