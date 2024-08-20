#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"

#include <glm/glm.hpp>

#include <string>
#include <map>

namespace MPE
{
struct MPE_API GraphicalContextProps
{
    int majorVersion;
    int minorVersion;

    std::string vendor;
    std::string renderer;
    int shaderTypeAmount;

    // virtual std::string ToString() const;
};

class MPE_API RenderSettings
{
  public:
    // VSYNC
    virtual void ToggleVsync() = 0;
    virtual bool GetVsync() const = 0;
    virtual void SetVsync(bool vsync) = 0;

    // LIMIT FPS
    virtual void ToggleLimitFPS() = 0;
    virtual bool GetLimitFPS() const = 0;
    virtual void SetLimitFPS(bool limitFPS) = 0;

    // MAX FPS
    virtual void SetMaxFPS(uint8_t maxFPS) = 0;
    virtual uint8_t GetMaxFPS() const = 0;

    // BLEND
    virtual void ToggleBlend() = 0;
    virtual bool GetBlend() const = 0;
    virtual void SetBlend(bool blend) = 0;

    // DEPTH TEST
    virtual void ToggleDepthTest() = 0;
    virtual bool GetDepthTest() const = 0;
    virtual void SetDepthTest(bool depthTest) = 0;

    // FACE CULLING
    virtual void ToggleFaceCulling() = 0;
    virtual bool GetFaceCulling() const = 0;
    virtual void SetFaceCulling(bool faceCulling) = 0;

    // DEBUG OUTPUT
    virtual void ToggleDebugOutput() = 0;
    virtual bool GetDebugOutput() const = 0;
    virtual void SetDebugOutput(bool debugOutput) = 0;

    virtual std::string GetSettings() const = 0;

  protected:
    RenderSettings();
    virtual void UpdateSettings() = 0;
    virtual void SendEvent(std::string name, int32_t value) = 0;

  protected:
    GraphicalContextProps* m_graphicalContextProps;
    bool m_vsync;
    bool m_limitFps;
    uint8_t m_maxFps;
    bool m_faceCulling;
    bool m_debugOutput;
};
}