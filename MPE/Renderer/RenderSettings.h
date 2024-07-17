#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"

#include <glm/glm.hpp>

#include <string>
#include <map>

namespace MPE
{
class MPE_API RenderSettings
{
  protected:
    bool _VSYNC;

  public:
    virtual void ToggleVsync() = 0;
    virtual bool GetVsync() const = 0;
    virtual void SetVsync(bool vsync) = 0;

    virtual std::string GetSettings() const = 0;
};
}