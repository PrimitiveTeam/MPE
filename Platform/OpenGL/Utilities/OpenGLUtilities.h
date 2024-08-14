#pragma once

#include "MPE/Core/_CORE.h"

#include <glad/glad.h>

namespace MPE
{
class MPE_API OpenGLUtilities
{
  public:
    static void GLAPIENTRY LogOpenGLDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message);

    static GLenum glCheckError_(const char *file, int line);

    static bool IsOpenGLVersionHigherThan(int major, int minor);
    static bool IsOpenGLVersionLowerThan(int major, int minor);
    static bool IsOpenGLVersionEqualTo(int major, int minor);
    static bool IsOpenGLVersionHigherOrEqualTo(int major, int minor);
    static bool IsOpenGLVersionLowerOrEqualTo(int major, int minor);
};
}

#define glCheckError() MPE::OpenGLUtilities::glCheckError_(__FILE__, __LINE__)