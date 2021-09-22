#ifndef CHECK_GL_ERROR_HPP
#define CHECK_GL_ERROR_HPP

#include "gl_include.hpp"
#include "log_config.hpp"

static void checkGlError(const char* op) {
   static bool first_ = true;
   for (GLint error = glGetError(); error; error
                    = glGetError()) {
      if (first_) {
         LOGE("after %s() glError (0x%x)\n", op, error);
         first_ = false;
      }
   }
}
#endif
