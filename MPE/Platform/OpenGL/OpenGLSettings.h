#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/RenderSettings.h"

#include <glm/glm.hpp>

namespace MPE
{
class MPE_API OpenGLSettings : public RenderSettings
{
  public:
    OpenGLSettings();

    // VSYNC
    virtual void ToggleVsync() override;
    virtual bool GetVsync() const override;
    virtual void SetVsync(bool vsync) override;

    // BLEND
    void ToggleBlend();
    bool GetBlend() const;
    void SetBlend(bool blend);

    // DEPTH TEST
    void ToggleDepthTest();
    bool GetDepthTest() const;
    void SetDepthTest(bool depthTest);

    virtual std::string GetSettings() const override;

  private:
    void UpdateSettings();

  private:
    // Store settings in a map. For basic settings that are binary store in a string/bool pair.
    std::map<std::string, std::pair<std::string, bool>> _SETTINGS;

    bool _BLEND;
    bool _DEPTH_TEST;
};
}