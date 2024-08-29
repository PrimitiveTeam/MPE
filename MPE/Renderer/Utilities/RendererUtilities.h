#pragma once

#include "MPE/Core/_CORE.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
class MPE_API RendererUtilities
{
  public:
    RendererUtilities(glm::vec4 color = {0.1f, 0.1f, 0.1f, 1.0f});
    ~RendererUtilities();

    void DrawClearColorScene();

  private:
    glm::vec4 SYS_COLOR;
};
}