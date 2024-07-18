#include "OpenGLContext.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"

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

    // std::string OpenGL_INFO = "\nOpenGL Info:\n";

    int OpenGLVersionMajor;
    int OpenGLVersionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersionMinor);

    // OpenGL_INFO += "\tOpenGL Version: " + std::to_string(OpenGLVersionMajor) + "." + std::to_string(OpenGLVersionMinor) + "\n";
    SYS_Props.MajorVersion = OpenGLVersionMajor;
    SYS_Props.MinorVersion = OpenGLVersionMinor;

#ifdef MPE_PLATFORM_WINDOWS
    MPE_CORE_ASSERT(OpenGLVersionMajor > 4 || (OpenGLVersionMajor == 4 && OpenGLVersionMinor >= 6), "MPE REQUIRES OPENGL VERSION 4.6 OR GREATER.");
#elif MPE_PLATFORM_OSX
    MPE_CORE_ASSERT(OpenGLVersionMajor >= 3 || (OpenGLVersionMajor >= 3 && OpenGLVersionMinor >= 2), "MPE REQUIRES OPENGL VERSION 3.2 FOR macOS.");
#else
    MPE_CORE_ASSERT(OpenGLVersionMajor > 4 || (OpenGLVersionMajor == 4 && OpenGLVersionMinor >= 6), "MPE REQUIRES OPENGL VERSION 4.6 OR GREATER.");
#endif

    SYS_Props.Vendor = std::string(reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
    SYS_Props.Renderer = std::string(reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
    SYS_Props.ShaderTypeAmount = OPENGL_SHADER_TYPE_AMOUNT;

    MPE_CORE_INFO('\n' + SYS_Props.ToString());
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(SYS_Window);
}
}