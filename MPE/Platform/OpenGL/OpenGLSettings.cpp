#include "OpenGLSettings.h"
#include "MPEPCH.h"

#include "MPE/App/App.h"
#include "MPE/Events/EventGraphics.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace MPE
{
OpenGLSettings::OpenGLSettings()
{
#if MPE_PLATFORM_LINUX
    _SETTINGS.insert(std::make_pair("VSYNC", std::make_pair("VSYNC", _VSYNC)));
    _SETTINGS.insert(std::make_pair("LIMIT_FPS", std::make_pair("LIMIT_FPS", _LIMIT_FPS)));
    _SETTINGS.insert(std::make_pair("MAX_FPS", std::make_pair("MAX_FPS", _MAX_FPS)));
    _SETTINGS.insert(std::make_pair("BLEND", std::make_pair("BLEND", _BLEND)));
    _SETTINGS.insert(std::make_pair("DEPTH_TEST", std::make_pair("DEPTH_TEST", _DEPTH_TEST)));
    _SETTINGS.insert(std::make_pair("POLYGON_MODE", std::make_pair("POLYGON_MODE", _POLYGON_MODE)));
#else
    _SETTINGS["VSYNC"] = std::make_pair("VSYNC", _VSYNC);
    _SETTINGS["LIMIT_FPS"] = std::make_pair("LIMIT_FPS", _LIMIT_FPS);
    _SETTINGS["MAX_FPS"] = std::make_pair("MAX_FPS", _MAX_FPS);
    _SETTINGS["BLEND"] = std::make_pair("BLEND", _BLEND);
    _SETTINGS["DEPTH_TEST"] = std::make_pair("DEPTH_TEST", _DEPTH_TEST);
    _SETTINGS["POLYGON_MODE"] = std::make_pair("POLYGON_MODE", _POLYGON_MODE);
#endif
}

// VSYNC

void OpenGLSettings::ToggleVsync()
{
    _VSYNC = !_VSYNC;

    if (_VSYNC)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("VSYNC", _VSYNC);
#else
    UpdateSettingsAndSendEvent(_SETTINGS["VSYNC"].first, _VSYNC);
#endif
}

bool OpenGLSettings::GetVsync() const
{
    return _VSYNC;
}

void OpenGLSettings::SetVsync(bool vsync)
{
    _VSYNC = vsync;

    if (_VSYNC)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("VSYNC", _VSYNC);
#else
    UpdateSettingsAndSendEvent(_SETTINGS["VSYNC"].first, _VSYNC);
#endif
}

// LIMIT FPS

void OpenGLSettings::ToggleLimitFPS()
{
    _LIMIT_FPS = !_LIMIT_FPS;

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("LIMIT_FPS", _LIMIT_FPS);
#else
    UpdateSettingsAndSendEvent(_SETTINGS["LIMIT_FPS"].first, _LIMIT_FPS);
#endif
}

bool OpenGLSettings::GetLimitFPS() const
{
    return _LIMIT_FPS;
}

void OpenGLSettings::SetLimitFPS(bool limitFPS)
{
    _LIMIT_FPS = limitFPS;

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("LIMIT_FPS", _LIMIT_FPS);
#else
    UpdateSettingsAndSendEvent(_SETTINGS["LIMIT_FPS"].first, _LIMIT_FPS);
#endif
}

// MAX FPS

void OpenGLSettings::SetMaxFPS(uint8_t maxFPS)
{
    _MAX_FPS = maxFPS;

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("MAX_FPS", _MAX_FPS);
#else
    UpdateSettingsAndSendEvent(_SETTINGS["MAX_FPS"].first, _MAX_FPS);
#endif
}

uint8_t OpenGLSettings::GetMaxFPS() const
{
    return _MAX_FPS;
}

// BLEND

void OpenGLSettings::ToggleBlend()
{
    _BLEND = !_BLEND;

    if (_BLEND)
        glEnable(GL_BLEND);
    else
        glDisable(GL_BLEND);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("BLEND", _BLEND);
#else
    UpdateSettingsAndSendEvent(_SETTINGS["BLEND"].first, _BLEND);
#endif
}

bool OpenGLSettings::GetBlend() const
{
    return _BLEND;
}

void OpenGLSettings::SetBlend(bool blend)
{
    _BLEND = blend;

    if (_BLEND)
        glEnable(GL_BLEND);
    else
        glDisable(GL_BLEND);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("BLEND", _BLEND);
#else
    UpdateSettingsAndSendEvent(_SETTINGS["BLEND"].first, _BLEND);
#endif
}

// DEPTH TEST

void OpenGLSettings::ToggleDepthTest()
{
    _DEPTH_TEST = !_DEPTH_TEST;

    if (_DEPTH_TEST)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("DEPTH_TEST", _DEPTH_TEST);
#else
    UpdateSettingsAndSendEvent(_SETTINGS["DEPTH_TEST"].first, _DEPTH_TEST);
#endif
}

bool OpenGLSettings::GetDepthTest() const
{
    return _DEPTH_TEST;
}

void OpenGLSettings::SetDepthTest(bool depthTest)
{
    _DEPTH_TEST = depthTest;

    if (_DEPTH_TEST)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("DEPTH_TEST", _DEPTH_TEST);
#else
    UpdateSettingsAndSendEvent(_SETTINGS["DEPTH_TEST"].first, _DEPTH_TEST);
#endif
}

// POLYGON MODE

void OpenGLSettings::TogglePolygonMode()
{
    _POLYGON_MODE = !_POLYGON_MODE;

    if (_POLYGON_MODE)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("POLYGON_MODE", _POLYGON_MODE);
#else

    UpdateSettingsAndSendEvent(_SETTINGS["POLYGON_MODE"].first, _POLYGON_MODE);
#endif
}

bool OpenGLSettings::GetPolygonMode() const
{
    return _POLYGON_MODE;
}

void OpenGLSettings::SetPolygonMode(bool polygonMode)
{
    _POLYGON_MODE = polygonMode;

    if (_POLYGON_MODE)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("POLYGON_MODE", _POLYGON_MODE);
#else
    UpdateSettingsAndSendEvent(_SETTINGS["POLYGON_MODE"].first, _POLYGON_MODE);
#endif
}

// SETTINGS

std::string OpenGLSettings::GetSettings() const
{
    std::string settings = "";
    for (auto setting : _SETTINGS)
    {
        settings += setting.second.first + ": " + (setting.second.second ? "ON" : "OFF") + "\n";
    }
    return settings;
}

void OpenGLSettings::UpdateSettings()
{
#if MPE_PLATFORM_LINUX
    auto vsyncIt = _SETTINGS.find("VSYNC");
    if (vsyncIt != _SETTINGS.end()) vsyncIt->second.second = _VSYNC;

    auto limitFPSIt = _SETTINGS.find("LIMIT_FPS");
    if (limitFPSIt != _SETTINGS.end()) limitFPSIt->second.second = _LIMIT_FPS;

    auto maxFPSIt = _SETTINGS.find("MAX_FPS");
    if (maxFPSIt != _SETTINGS.end()) maxFPSIt->second.second = _MAX_FPS;

    auto blendIt = _SETTINGS.find("BLEND");
    if (blendIt != _SETTINGS.end()) blendIt->second.second = _BLEND;

    auto depthTestIt = _SETTINGS.find("DEPTH_TEST");
    if (depthTestIt != _SETTINGS.end()) depthTestIt->second.second = _DEPTH_TEST;

    auto polygonModeIt = _SETTINGS.find("POLYGON_MODE");
    if (polygonModeIt != _SETTINGS.end()) polygonModeIt->second.second = _POLYGON_MODE;
#else
    _SETTINGS["VSYNC"].second = _VSYNC;
    _SETTINGS["LIMIT_FPS"].second = _LIMIT_FPS;
    _SETTINGS["MAX_FPS"].second = _MAX_FPS;
    _SETTINGS["BLEND"].second = _BLEND;
    _SETTINGS["DEPTH_TEST"].second = _DEPTH_TEST;
    _SETTINGS["POLYGON_MODE"].second = _POLYGON_MODE;
#endif
}

void OpenGLSettings::UpdateSettingsAndSendEvent(std::string name, int32_t value)
{
    UpdateSettings();
    SendEvent(name, value);
}

void OpenGLSettings::SendEvent(std::string name, int32_t value)
{
    MPE::GraphicsSettingsChangedEvent event(name, value);
    MPE::App::GetApp().OnEvent(event);
}
}