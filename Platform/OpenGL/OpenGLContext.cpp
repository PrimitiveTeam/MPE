#include "OpenGLContext.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace MPE
{
OpenGLContext::OpenGLContext(GLFWwindow *window) : m_window(window)
{
    MPE_CORE_ASSERT(m_window, "WINDOW IS NULL.");
}

void OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_window);

    int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    MPE_CORE_ASSERT(status, "FAILED TO INITIALIZE GLAD.");
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}
}