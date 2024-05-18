#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/GraphicalContext.h"

struct MPE_API GLFWwindow;

namespace MPE
{
class MPE_API OpenGLContext : public GraphicalContext
{
  private:
    GLFWwindow *SYS_Window;

  public:
    OpenGLContext(GLFWwindow *window);

    virtual void Init() override;
    virtual void SwapBuffers() override;
};
}