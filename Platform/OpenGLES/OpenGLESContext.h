#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/GraphicalContext.h"

#include <GLFW/glfw3.h>
#include <EGL/egl.h>

namespace MPE
{
class MPE_API OpenGLESContext : public GraphicalContext
{
  public:
    OpenGLESContext(GLFWwindow *window);

    virtual void Init() override;
    virtual void SwapBuffers() override;

    EGLDisplay GetEGLDisplay() const { return m_eglDisplay; }

  private:
    GLFWwindow *m_window;
    EGLDisplay m_eglDisplay;
    EGLSurface m_eglSurface;
    EGLContext m_eglContext;
};
}