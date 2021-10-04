/**
 * File dedicated to figuring out some kind of GL debug output
 */
#include <stdio.h>

#include "../Desktop.h"
#include "GL_Render.h"

/*Basic simple GL debug checker*/
void gl_debug_out(const char* check_point) {
  GLenum err = glGetError();

  /*We've had some kind of error so report it*/
  printf("Error Detected from %s\n", check_point);

  while (err != GL_NO_ERROR) {
    char* type;
    switch (err) {
      case GL_INVALID_ENUM:
        type = "GL_INVALID_ENUM";
        break;
      case GL_INVALID_VALUE:
        type = "GL_INVALID_VALUE";
        break;
      case GL_INVALID_OPERATION:
        type = "GL_INVALID_OPERATION";
        break;
      case GL_STACK_OVERFLOW:
        type = "GL_STACK_OVERFLOW";
        break;
      case GL_STACK_UNDERFLOW:
        type = "GL_STACK_UNDERFLOW";
        break;
      case GL_OUT_OF_MEMORY:
        type = "GL_OUT_OF_MEMORY";
        break;
      default:
        type = "UNKNOWN!!";
        break;
    }
    printf("\t * GL Error Detected : 0x%x\n\t * That means %s\n", err, type);

    err = glGetError();
  }
}

/**
 * All of our debug callbacks
 */
void __stdcall DebugCallbackARB(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar* message, GLvoid* userParam) {
  if (severity >= GL_DEBUG_SEVERITY_MEDIUM_ARB) {
    printf(" * GLARB Has caught an error: \n * %s\n", message);
  }
}

void gl_enable_callback() {
  /*Use GLEW to check which debug output extensions are supported*/
  if (GLEW_ARB_debug_output) {
    printf("Extension supported : GLEW_ARB_debug_output\n");
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallbackARB((GLDEBUGPROCARB)DebugCallbackARB, 0);
  }
}
