/**
 * Set up the GL Rendering
 */
#include "GL_Render.h"

const uint8_t shaderCount = 1;
const char* ShaderNames[1] = {"Test shader.glsl"};

Concorde_GL_Render init_gl_rendering(void) { return GL_Success; }

/*When we init a render we always need to allocate enough memory from the
 * vertices*/
concorde_render_error_codes platform_render_begin(
    concorde_rendering_mode rendering_mode, concorde_primative primative,
    concorde_vertex_mask vertex_mask, uint32_t vertex_count) {
  return crec_success;
}
