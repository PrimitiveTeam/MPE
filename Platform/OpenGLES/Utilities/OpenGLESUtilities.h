#pragma once

#include "MPE/Core/_CORE.h"

#include <GLES3/gl31.h>

namespace MPE
{
class MPE_API OpenGLESUtilities
{
  public:
    // Not available in OpenGLES 3.1; Should be available in OpenGLES 3.2 but we are not using it
    // static void GLAPIENTRY LogOpenGLDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message);

    static GLenum glCheckError_(const char *file, int line);

    static bool IsOpenGLESVersionHigherThan(int major, int minor);
    static bool IsOpenGLESVersionLowerThan(int major, int minor);
    static bool IsOpenGLESVersionEqualTo(int major, int minor);
    static bool IsOpenGLESVersionHigherOrEqualTo(int major, int minor);
    static bool IsOpenGLESVersionLowerOrEqualTo(int major, int minor);
};
}

#define glCheckError() MPE::OpenGLESUtilities::glCheckError_(__FILE__, __LINE__)