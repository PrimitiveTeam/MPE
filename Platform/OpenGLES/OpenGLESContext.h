#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/GraphicalContext.h"
#include "Platform/OpenGLES/OpenGLESContextProps.h"

struct MPE_API GLFWwindow;
typedef void *EGLDisplay;
typedef void *EGLSurface;
typedef void *EGLContext;
namespace MPE
{
class MPE_API OpenGLESContext : public GraphicalContext
{
  public:
    OpenGLESContext(GLFWwindow *window);

    virtual void Init() override;
    virtual void SwapBuffers() override;

  private:
    GLFWwindow *SYS_Window;
    EGLDisplay eglDisplay;
    EGLSurface eglSurface;
    EGLContext eglContext;
    OpenGLESContextProps SYS_Props;
};
}