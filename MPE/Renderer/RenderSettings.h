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
  public:
    // VSYNC
    virtual void ToggleVsync() = 0;
    virtual bool GetVsync() const = 0;
    virtual void SetVsync(bool vsync) = 0;

    // BLEND
    virtual void ToggleBlend() = 0;
    virtual bool GetBlend() const = 0;
    virtual void SetBlend(bool blend) = 0;

    // DEPTH TEST
    virtual void ToggleDepthTest() = 0;
    virtual bool GetDepthTest() const = 0;
    virtual void SetDepthTest(bool depthTest) = 0;

    virtual std::string GetSettings() const = 0;

  protected:
    bool _VSYNC;
};
}