#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/RenderSettings.h"

#include <glm/glm.hpp>

namespace MPE
{
class MPE_API OpenGLESSettings : public RenderSettings
{
  public:
    OpenGLESSettings();

    // VSYNC
    virtual void ToggleVsync() override;
    virtual bool GetVsync() const override;
    virtual void SetVsync(bool vsync) override;

    // LIMIT FPS
    virtual void ToggleLimitFPS() override;
    virtual bool GetLimitFPS() const override;
    virtual void SetLimitFPS(bool limitFPS) override;

    // MAX FPS
    virtual void SetMaxFPS(uint8_t maxFPS) override;
    virtual uint8_t GetMaxFPS() const override;

    // BLEND
    virtual void ToggleBlend() override;
    virtual bool GetBlend() const override;
    virtual void SetBlend(bool blend) override;

    // DEPTH TEST
    virtual void ToggleDepthTest() override;
    virtual bool GetDepthTest() const override;
    virtual void SetDepthTest(bool depthTest) override;

    // POLYGON MODE
    void TogglePolygonMode();
    bool GetPolygonMode() const;
    void SetPolygonMode(bool polygonMode);

    virtual std::string GetSettings() const override;

  private:
    void UpdateSettings() override;
    void UpdateSettingsAndSendEvent(std::string name, int32_t value);
    void SendEvent(std::string name, int32_t value) override;

  private:
    // Store settings in a map. For basic settings that are binary store in a string/bool pair.
    std::map<std::string, std::pair<std::string, int>> _SETTINGS;

    bool _BLEND;
    bool _DEPTH_TEST;
    bool _POLYGON_MODE;
};
}