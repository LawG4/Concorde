/**
* File dedicated to figuring out some kind of GL debug output
*/
#include "../Desktop.h"
#include "GL_Render.h"

#include <stdio.h>

/*Basic simple GL debug checker*/
void gl_debug_out(const char* check_point) {
  GLenum err = glGetError();

  /*We've had some kind of error so report it*/
  printf("Error Detected from %s\n", check_point);

  while (err != GL_NO_ERROR) {
    printf("GL Error Detected : 0x%x\n", err);
    err = glGetError();
  }
}
