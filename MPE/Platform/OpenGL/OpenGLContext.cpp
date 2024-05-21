#include "OpenGLContext.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/MPEPCH.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace MPE
{
OpenGLContext::OpenGLContext(GLFWwindow *window) : SYS_Window(window)
{
    MPE_CORE_ASSERT(SYS_Window, "WINDOW IS NULL.");
}

void OpenGLContext::Init()
{
    glfwMakeContextCurrent(SYS_Window);

    int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    MPE_CORE_ASSERT(status, "FAILED TO INITIALIZE GLAD.")

    std::string OpenGL_INFO = "\nOpenGL Info:\n";

    int OpenGLVersionMajor;
    int OpenGLVersionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersionMinor);

    OpenGL_INFO += "\tOpenGL Version: " + std::to_string(OpenGLVersionMajor) + "." + std::to_string(OpenGLVersionMinor) + "\n";

#ifdef MPE_PLATFORM_WINDOWS
    MPE_CORE_ASSERT(OpenGLVersionMajor > 4 || (OpenGLVersionMajor == 4 && OpenGLVersionMinor >= 6), "MPE REQUIRES OPENGL VERSION 4.6 OR GREATER.");
#elif MPE_PLATFORM_OSX
    MPE_CORE_ASSERT(OpenGLVersionMajor >= 3 || (OpenGLVersionMajor >= 3 && OpenGLVersionMinor >= 2), "MPE REQUIRES OPENGL VERSION 3.2 FOR macOS.");
#else
    MPE_CORE_ASSERT(OpenGLVersionMajor > 4 || (OpenGLVersionMajor == 4 && OpenGLVersionMinor >= 6), "MPE REQUIRES OPENGL VERSION 4.6 OR GREATER.");
#endif

#ifdef MPE_ENABLE_DEBUG_LOG
    OpenGL_INFO += "\tVendor: " + std::string(reinterpret_cast<const char *>(glGetString(GL_VENDOR))) + "\n";
    OpenGL_INFO += "\tRenderer: " + std::string(reinterpret_cast<const char *>(glGetString(GL_RENDERER))) + "\n";
    OpenGL_INFO += "\tVersion: " + std::string(reinterpret_cast<const char *>(glGetString(GL_VERSION))) + "\n";
    OpenGL_INFO += "\tHardcode shader type limit: " + std::to_string(OPENGL_SHADER_TYPE_AMOUNT);
#endif

    MPE_CORE_INFO(OpenGL_INFO);
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(SYS_Window);
}
}