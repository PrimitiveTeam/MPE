#include "OpenGLUtilities.h"
#include "MPEPCH.h"

#include "MPE/Log/GlobalLog.h"

#include <GLFW/glfw3.h>

namespace MPE
{
void GLAPIENTRY OpenGLUtilities::LogOpenGLDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message)
{
    std::string sourceString;
    std::string typeString;
    std::string severityString;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:
            sourceString = "API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            sourceString = "Window System";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            sourceString = "Shader Compiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            sourceString = "Third Party";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            sourceString = "Application";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            sourceString = "Other";
            break;
    }

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:
            typeString = "Error";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            typeString = "Deprecated Behavior";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            typeString = "Undefined Behavior";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            typeString = "Portability";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            typeString = "Performance";
            break;
        case GL_DEBUG_TYPE_MARKER:
            typeString = "Marker";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            typeString = "Push Group";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            typeString = "Pop Group";
            break;
        case GL_DEBUG_TYPE_OTHER:
            typeString = "Other";
            break;
    }

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            severityString = "High";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            severityString = "Medium";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            severityString = "Low";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            severityString = "Notification";
            break;
    }

    std::string finalMessage = fmt::format("\n\tOpenGL:\n\t\tSource: {0}\n\t\tType: {1}\n\t\tID: {2}\n\t\tSeverity: {3}\n\t\tMessage: {4}", sourceString,
                                           typeString, id, severityString, message);

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            MPE_CORE_ERROR(finalMessage);
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            MPE_CORE_WARN(finalMessage);
            break;
        case GL_DEBUG_SEVERITY_LOW:
            MPE_CORE_INFO(finalMessage);
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            MPE_CORE_TRACE(finalMessage);
            break;
    }
}

GLenum OpenGLUtilities::glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:
                error = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error = "INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                error = "STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                error = "STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                error = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

bool OpenGLUtilities::IsOpenGLVersionHigherThan(int major, int minor)
{
    int OpenGLVersionMajor;
    int OpenGLVersionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersionMinor);

    return OpenGLVersionMajor > major || (OpenGLVersionMajor == major && OpenGLVersionMinor > minor);
}

bool OpenGLUtilities::IsOpenGLVersionLowerThan(int major, int minor)
{
    int OpenGLVersionMajor;
    int OpenGLVersionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersionMinor);

    return OpenGLVersionMajor < major || (OpenGLVersionMajor == major && OpenGLVersionMinor < minor);
}

bool OpenGLUtilities::IsOpenGLVersionEqualTo(int major, int minor)
{
    int OpenGLVersionMajor;
    int OpenGLVersionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersionMinor);

    return OpenGLVersionMajor == major && OpenGLVersionMinor == minor;
}

bool OpenGLUtilities::IsOpenGLVersionHigherOrEqualTo(int major, int minor)
{
    int OpenGLVersionMajor;
    int OpenGLVersionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersionMinor);

    return OpenGLVersionMajor > major || (OpenGLVersionMajor == major && OpenGLVersionMinor >= minor);
}

bool OpenGLUtilities::IsOpenGLVersionLowerOrEqualTo(int major, int minor)
{
    int OpenGLVersionMajor;
    int OpenGLVersionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersionMinor);

    return OpenGLVersionMajor < major || (OpenGLVersionMajor == major && OpenGLVersionMinor <= minor);
}
}