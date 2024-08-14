#include "OpenGLESSettings.h"
#include "MPEPCH.h"

#include "MPE/App/App.h"
#include "MPE/Events/EventGraphics.h"
#include "Platform/OpenGLES/OpenGLESContext.h"
#include "Platform/OpenGLES/Utilities/OpenGLESUtilities.h"

#include <GLFW/glfw3.h>
#include <EGL/egl.h>
#include <GLES3/gl31.h>

namespace MPE
{
OpenGLESSettings::OpenGLESSettings()
{
    // Compatibility issues, so setting to false by default to not mislead the users.
    _POLYGON_MODE = false;
    _DEBUG_OUTPUT = false;

#if MPE_PLATFORM_LINUX
    _SETTINGS.insert(std::make_pair("VSYNC", std::make_pair("VSYNC", _VSYNC)));
    _SETTINGS.insert(std::make_pair("LIMIT_FPS", std::make_pair("LIMIT_FPS", _LIMIT_FPS)));
    _SETTINGS.insert(std::make_pair("MAX_FPS", std::make_pair("MAX_FPS", _MAX_FPS)));
    _SETTINGS.insert(std::make_pair("BLEND", std::make_pair("BLEND", _BLEND)));
    _SETTINGS.insert(std::make_pair("DEPTH_TEST", std::make_pair("DEPTH_TEST", _DEPTH_TEST)));
    _SETTINGS.insert(std::make_pair("POLYGON_MODE", std::make_pair("POLYGON_MODE", _POLYGON_MODE)));
    _SETTINGS.insert(std::make_pair("FACE_CULLING", std::make_pair("FACE_CULLING", _FACE_CULLING));
    _SETTINGS.insert(std::make_pair("DEBUG_OUTPUT", std::make_pair("DEBUG_OUTPUT", _DEBUG_OUTPUT));
#else
    _SETTINGS["VSYNC"] = std::make_pair("VSYNC", _VSYNC);
    _SETTINGS["LIMIT_FPS"] = std::make_pair("LIMIT_FPS", _LIMIT_FPS);
    _SETTINGS["MAX_FPS"] = std::make_pair("MAX_FPS", _MAX_FPS);
    _SETTINGS["BLEND"] = std::make_pair("BLEND", _BLEND);
    _SETTINGS["DEPTH_TEST"] = std::make_pair("DEPTH_TEST", _DEPTH_TEST);
    _SETTINGS["POLYGON_MODE"] = std::make_pair("POLYGON_MODE", _POLYGON_MODE);
    _SETTINGS["FACE_CULLING"] = std::make_pair("FACE_CULLING", _FACE_CULLING);
    _SETTINGS["DEBUG_OUTPUT"] = std::make_pair("DEBUG_OUTPUT", _DEBUG_OUTPUT);
#endif
}

// GRAPHICAL CONTEXT PROPS

std::string OpenGLESSettings::GetGraphicalContextPropsAsString()
{
    std::string OpenGLESInfo = "OpenGLES Info:\n";
    OpenGLESInfo +=
        "\tVersion: " + std::to_string(_GRAPHICAL_CONTEXT_PROPS->MajorVersion) + "." + std::to_string(_GRAPHICAL_CONTEXT_PROPS->MinorVersion) + "\n";
    OpenGLESInfo += "\tVendor: " + _GRAPHICAL_CONTEXT_PROPS->Vendor + "\n";
    OpenGLESInfo += "\tRenderer: " + _GRAPHICAL_CONTEXT_PROPS->Renderer + "\n";
    OpenGLESInfo += "\tHardcode shader type limit: " + std::to_string(_GRAPHICAL_CONTEXT_PROPS->ShaderTypeAmount);

    return OpenGLESInfo;
}

// VSYNC

void OpenGLESSettings::ToggleVsync()
{
    this->SetVsync(!_VSYNC);
}

bool OpenGLESSettings::GetVsync() const
{
    return _VSYNC;
}

void OpenGLESSettings::SetVsync(bool vsync)
{
    _VSYNC = vsync;

    auto eglDisplay = reinterpret_cast<OpenGLESContext*>(MPE::App::GetApp().GetWindow()->GetNativeGLESContext())->GetEGLDisplay();

    if (_VSYNC)
        eglSwapInterval(eglDisplay, 1);
    else
        eglSwapInterval(eglDisplay, 0);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("VSYNC", _VSYNC);
#else
    UpdateSettingsAndSendEvent(_SETTINGS["VSYNC"].first, _VSYNC);
#endif
}

// LIMIT FPS

void OpenGLESSettings::ToggleLimitFPS()
{
    this->SetLimitFPS(!_LIMIT_FPS);
}

bool OpenGLESSettings::GetLimitFPS() const
{
    return _LIMIT_FPS;
}

void OpenGLESSettings::SetLimitFPS(bool limitFPS)
{
    _LIMIT_FPS = limitFPS;

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("LIMIT_FPS", _LIMIT_FPS);
#else
    UpdateSettingsAndSendEvent(_SETTINGS["LIMIT_FPS"].first, _LIMIT_FPS);
#endif
}

// MAX FPS

void OpenGLESSettings::SetMaxFPS(uint8_t maxFPS)
{
    _MAX_FPS = maxFPS;

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("MAX_FPS", _MAX_FPS);
#else
    UpdateSettingsAndSendEvent(_SETTINGS["MAX_FPS"].first, _MAX_FPS);
#endif
}

uint8_t OpenGLESSettings::GetMaxFPS() const
{
    return _MAX_FPS;
}

// BLEND

void OpenGLESSettings::ToggleBlend()
{
    this->SetBlend(!_BLEND);
}

bool OpenGLESSettings::GetBlend() const
{
    return _BLEND;
}

void OpenGLESSettings::SetBlend(bool blend)
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

void OpenGLESSettings::ToggleDepthTest()
{
    this->SetDepthTest(!_DEPTH_TEST);
}

bool OpenGLESSettings::GetDepthTest() const
{
    return _DEPTH_TEST;
}

void OpenGLESSettings::SetDepthTest(bool depthTest)
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

void OpenGLESSettings::TogglePolygonMode()
{
    this->SetPolygonMode(!_POLYGON_MODE);
}

bool OpenGLESSettings::GetPolygonMode() const
{
    return _POLYGON_MODE;
}

void OpenGLESSettings::SetPolygonMode(bool polygonMode)
{
    MPE_WARN("'glPolygonMode' NOT AVAILABLE ON OpenGLES.");
    return;

    //     _POLYGON_MODE = polygonMode;

    //     if (_POLYGON_MODE)
    //         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //     else
    //         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // #if MPE_PLATFORM_LINUX
    //     UpdateSettingsAndSendEvent("POLYGON_MODE", _POLYGON_MODE);
    // #else
    //     UpdateSettingsAndSendEvent(_SETTINGS["POLYGON_MODE"].first, _POLYGON_MODE);
    // #endif
}

// FACE CULLING

void OpenGLESSettings::ToggleFaceCulling()
{
    this->SetFaceCulling(!_FACE_CULLING);
}

bool OpenGLESSettings::GetFaceCulling() const
{
    return _FACE_CULLING;
}

void OpenGLESSettings::SetFaceCulling(bool faceCulling)
{
    _FACE_CULLING = faceCulling;

    if (_FACE_CULLING)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("FACE_CULLING", _FACE_CULLING);
#else
    UpdateSettingsAndSendEvent(_SETTINGS["FACE_CULLING"].first, _FACE_CULLING);
#endif
}

// DEBUG OUTPUT

void OpenGLESSettings::ToggleDebugOutput()
{
    this->SetDebugOutput(!_DEBUG_OUTPUT);
}

bool OpenGLESSettings::GetDebugOutput() const
{
    return _DEBUG_OUTPUT;
}

void OpenGLESSettings::SetDebugOutput(bool debugOutput)
{
    // This is not available on OpenGLES < 3.2
    if (OpenGLESUtilities::IsOpenGLESVersionLowerThan(3, 2))
    {
        MPE_CORE_WARN("Debug output is not available on OpenGLES version lower than 3.2.");
        return;
    }

//     _DEBUG_OUTPUT = debugOutput;

//     if (_DEBUG_OUTPUT)
//     {
//         glEnable(GL_DEBUG_OUTPUT);
//         glDebugMessageCallback((GLDEBUGPROC) OpenGLESUtilities::LogOpenGLDebugOutput, nullptr);
//     }
//     else
//     {
//         glDisable(GL_DEBUG_OUTPUT);
//         glDebugMessageCallback(nullptr, nullptr);
//     }

// #if MPE_PLATFORM_LINUX
//     UpdateSettingsAndSendEvent("DEBUG_OUTPUT", _DEBUG_OUTPUT);
// #else
//     UpdateSettingsAndSendEvent(_SETTINGS["DEBUG_OUTPUT"].first, _DEBUG_OUTPUT);
// #endif
}

// SETTINGS

std::string OpenGLESSettings::GetSettings() const
{
    std::string settings = "";
    for (auto setting : _SETTINGS)
    {
        settings += setting.second.first + ": " + (setting.second.second ? "ON" : "OFF") + "\n";
    }
    return settings;
}

void OpenGLESSettings::UpdateSettings()
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

    auto faceCullingIt = _SETTINGS.find("FACE_CULLING");
    if (faceCullingIt != _SETTINGS.end()) faceCullingIt->second.second = _FACE_CULLING;

    auto debugOutputIt = _SETTINGS.find("DEBUG_OUTPUT");
    if (debugOutputIt != _SETTINGS.end()) debugOutputIt->second.second = _DEBUG_OUTPUT;
#else
    _SETTINGS["VSYNC"].second = _VSYNC;
    _SETTINGS["LIMIT_FPS"].second = _LIMIT_FPS;
    _SETTINGS["MAX_FPS"].second = _MAX_FPS;
    _SETTINGS["BLEND"].second = _BLEND;
    _SETTINGS["DEPTH_TEST"].second = _DEPTH_TEST;
    _SETTINGS["POLYGON_MODE"].second = _POLYGON_MODE;
    _SETTINGS["FACE_CULLING"].second = _FACE_CULLING;
    _SETTINGS["DEBUG_OUTPUT"].second = _DEBUG_OUTPUT;
#endif
}

void OpenGLESSettings::UpdateSettingsAndSendEvent(std::string name, int32_t value)
{
    UpdateSettings();
    SendEvent(name, value);
}

void OpenGLESSettings::SendEvent(std::string name, int32_t value)
{
    MPE::GraphicsSettingsChangedEvent event(name, value);
    MPE::App::GetApp().OnEvent(event);
}
}