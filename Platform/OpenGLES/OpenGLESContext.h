#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/GraphicalContext.h"
#include "Platform/OpenGLES/OpenGLESContextProps.h"

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

    EGLDisplay GetEGLDisplay() const { return eglDisplay; }

  private:
    GLFWwindow *SYS_Window;
    EGLDisplay eglDisplay;
    EGLSurface eglSurface;
    EGLContext eglContext;
    OpenGLESContextProps SYS_Props;
};
}