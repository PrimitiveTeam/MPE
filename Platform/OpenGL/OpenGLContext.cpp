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
    MPE_CORE_ASSERT(status, "FAILED TO INITIALIZE GLAD.");
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(SYS_Window);
}
}