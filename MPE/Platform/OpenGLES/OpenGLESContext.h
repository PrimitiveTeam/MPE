#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/GraphicalContext.h"
#include "MPE/Platform/OpenGLES/OpenGLESContextProps.h"

struct MPE_API GLFWwindow;

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
    OpenGLESContextProps SYS_Props;
};
}