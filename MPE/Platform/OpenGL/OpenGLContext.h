#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/GraphicalContext.h"
#include "MPE/Platform/OpenGL/OpenGLContextProps.h"

struct MPE_API GLFWwindow;

namespace MPE
{
class MPE_API OpenGLContext : public GraphicalContext
{
  public:
    OpenGLContext(GLFWwindow *window);

    virtual void Init() override;
    virtual void SwapBuffers() override;

  private:
    GLFWwindow *SYS_Window;
    OpenGLContextProps SYS_Props;
};
}