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
    m_polygonMode = false;
    m_debugOutput = false;

#if MPE_PLATFORM_LINUX
    m_settings.insert(std::make_pair("VSYNC", std::make_pair("VSYNC", m_vsync)));
    m_settings.insert(std::make_pair("LIMIT_FPS", std::make_pair("LIMIT_FPS", m_limitFps)));
    m_settings.insert(std::make_pair("MAX_FPS", std::make_pair("MAX_FPS", m_maxFps)));
    m_settings.insert(std::make_pair("BLEND", std::make_pair("BLEND", m_blend)));
    m_settings.insert(std::make_pair("DEPTH_TEST", std::make_pair("DEPTH_TEST", m_depthTest)));
    m_settings.insert(std::make_pair("POLYGON_MODE", std::make_pair("POLYGON_MODE", m_polygonMode)));
    m_settings.insert(std::make_pair("FACE_CULLING", std::make_pair("FACE_CULLING", m_faceCulling)));
    m_settings.insert(std::make_pair("DEBUG_OUTPUT", std::make_pair("DEBUG_OUTPUT", m_debugOutput)));
#else
    m_settings["VSYNC"] = std::make_pair("VSYNC", m_vsync);
    m_settings["LIMIT_FPS"] = std::make_pair("LIMIT_FPS", m_limitFps);
    m_settings["MAX_FPS"] = std::make_pair("MAX_FPS", m_maxFps);
    m_settings["BLEND"] = std::make_pair("BLEND", m_blend);
    m_settings["DEPTH_TEST"] = std::make_pair("DEPTH_TEST", m_depthTest);
    m_settings["POLYGON_MODE"] = std::make_pair("POLYGON_MODE", m_polygonMode);
    m_settings["FACE_CULLING"] = std::make_pair("FACE_CULLING", m_faceCulling);
    m_settings["DEBUG_OUTPUT"] = std::make_pair("DEBUG_OUTPUT", m_debugOutput);
#endif
}

// GRAPHICAL CONTEXT PROPS

std::string OpenGLESSettings::GetGraphicalContextPropsAsString()
{
    std::string OpenGLESInfo = "OpenGLES Info:\n";
    OpenGLESInfo +=
        "\tVersion: " + std::to_string(m_graphicalContextProps->m_majorVersion) + "." + std::to_string(m_graphicalContextProps->m_minorVersion) + "\n";
    OpenGLESInfo += "\tVendor: " + m_graphicalContextProps->m_vendor + "\n";
    OpenGLESInfo += "\tRenderer: " + m_graphicalContextProps->m_renderer + "\n";
    OpenGLESInfo += "\tHardcode shader type limit: " + std::to_string(m_graphicalContextProps->m_shaderTypeAmount);

    return OpenGLESInfo;
}

// VSYNC

void OpenGLESSettings::ToggleVsync()
{
    this->SetVsync(!m_vsync);
}

bool OpenGLESSettings::GetVsync() const
{
    return m_vsync;
}

void OpenGLESSettings::SetVsync(bool vsync)
{
    m_vsync = vsync;

    auto eglDisplay = reinterpret_cast<OpenGLESContext*>(MPE::App::GetApp().GetWindow()->GetNativeGLESContext())->GetEGLDisplay();

    if (m_vsync)
        eglSwapInterval(eglDisplay, 1);
    else
        eglSwapInterval(eglDisplay, 0);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("VSYNC", m_vsync);
#else
    UpdateSettingsAndSendEvent(m_settings["VSYNC"].first, m_vsync);
#endif
}

// LIMIT FPS

void OpenGLESSettings::ToggleLimitFPS()
{
    this->SetLimitFPS(!m_limitFps);
}

bool OpenGLESSettings::GetLimitFPS() const
{
    return m_limitFps;
}

void OpenGLESSettings::SetLimitFPS(bool limitFPS)
{
    m_limitFps = limitFPS;

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("LIMIT_FPS", m_limitFps);
#else
    UpdateSettingsAndSendEvent(m_settings["LIMIT_FPS"].first, m_limitFps);
#endif
}

// MAX FPS

void OpenGLESSettings::SetMaxFPS(uint8_t maxFPS)
{
    m_maxFps = maxFPS;

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("MAX_FPS", m_maxFps);
#else
    UpdateSettingsAndSendEvent(m_settings["MAX_FPS"].first, m_maxFps);
#endif
}

uint8_t OpenGLESSettings::GetMaxFPS() const
{
    return m_maxFps;
}

// BLEND

void OpenGLESSettings::ToggleBlend()
{
    this->SetBlend(!m_blend);
}

bool OpenGLESSettings::GetBlend() const
{
    return m_blend;
}

void OpenGLESSettings::SetBlend(bool blend)
{
    m_blend = blend;

    if (m_blend)
        glEnable(GL_BLEND);
    else
        glDisable(GL_BLEND);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("BLEND", m_blend);
#else
    UpdateSettingsAndSendEvent(m_settings["BLEND"].first, m_blend);
#endif
}

// DEPTH TEST

void OpenGLESSettings::ToggleDepthTest()
{
    this->SetDepthTest(!m_depthTest);
}

bool OpenGLESSettings::GetDepthTest() const
{
    return m_depthTest;
}

void OpenGLESSettings::SetDepthTest(bool depthTest)
{
    m_depthTest = depthTest;

    if (m_depthTest)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("DEPTH_TEST", m_depthTest);
#else
    UpdateSettingsAndSendEvent(m_settings["DEPTH_TEST"].first, m_depthTest);
#endif
}

// POLYGON MODE

void OpenGLESSettings::TogglePolygonMode()
{
    this->SetPolygonMode(!m_polygonMode);
}

bool OpenGLESSettings::GetPolygonMode() const
{
    return m_polygonMode;
}

void OpenGLESSettings::SetPolygonMode(bool polygonMode)
{
    MPE_WARN("'glPolygonMode' NOT AVAILABLE ON OpenGLES.");
    return;

    //     m_polygonMode = polygonMode;

    //     if (m_polygonMode)
    //         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //     else
    //         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // #if MPE_PLATFORM_LINUX
    //     UpdateSettingsAndSendEvent("POLYGON_MODE", m_polygonMode);
    // #else
    //     UpdateSettingsAndSendEvent(m_settings["POLYGON_MODE"].first, m_polygonMode);
    // #endif
}

// FACE CULLING

void OpenGLESSettings::ToggleFaceCulling()
{
    this->SetFaceCulling(!m_faceCulling);
}

bool OpenGLESSettings::GetFaceCulling() const
{
    return m_faceCulling;
}

void OpenGLESSettings::SetFaceCulling(bool faceCulling)
{
    m_faceCulling = faceCulling;

    if (m_faceCulling)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("FACE_CULLING", m_faceCulling);
#else
    UpdateSettingsAndSendEvent(m_settings["FACE_CULLING"].first, m_faceCulling);
#endif
}

// DEBUG OUTPUT

void OpenGLESSettings::ToggleDebugOutput()
{
    this->SetDebugOutput(!m_debugOutput);
}

bool OpenGLESSettings::GetDebugOutput() const
{
    return m_debugOutput;
}

void OpenGLESSettings::SetDebugOutput(bool debugOutput)
{
    // This is not available on OpenGLES < 3.2
    if (OpenGLESUtilities::IsOpenGLESVersionLowerThan(3, 2))
    {
        MPE_CORE_WARN("Debug output is not available on OpenGLES version lower than 3.2.");
        return;
    }

    //     m_debugOutput = debugOutput;

    //     if (m_debugOutput)
    //     {
    //         glEnable(GLm_debugOutput);
    //         glDebugMessageCallback((GLDEBUGPROC) OpenGLESUtilities::LogOpenGLDebugOutput, nullptr);
    //     }
    //     else
    //     {
    //         glDisable(GLm_debugOutput);
    //         glDebugMessageCallback(nullptr, nullptr);
    //     }

    // #if MPE_PLATFORM_LINUX
    //     UpdateSettingsAndSendEvent("DEBUG_OUTPUT", m_debugOutput);
    // #else
    //     UpdateSettingsAndSendEvent(m_settings["DEBUG_OUTPUT"].first, m_debugOutput);
    // #endif
}

// SETTINGS

std::string OpenGLESSettings::GetSettings() const
{
    std::string settings = "";
    for (auto setting : m_settings)
    {
        settings += setting.second.first + ": " + (setting.second.second ? "ON" : "OFF") + "\n";
    }
    return settings;
}

void OpenGLESSettings::UpdateSettings()
{
#if MPE_PLATFORM_LINUX
    auto vsyncIt = m_settings.find("VSYNC");
    if (vsyncIt != m_settings.end()) vsyncIt->second.second = m_vsync;

    auto limitFPSIt = m_settings.find("LIMIT_FPS");
    if (limitFPSIt != m_settings.end()) limitFPSIt->second.second = m_limitFps;

    auto maxFPSIt = m_settings.find("MAX_FPS");
    if (maxFPSIt != m_settings.end()) maxFPSIt->second.second = m_maxFps;

    auto blendIt = m_settings.find("BLEND");
    if (blendIt != m_settings.end()) blendIt->second.second = m_blend;

    auto depthTestIt = m_settings.find("DEPTH_TEST");
    if (depthTestIt != m_settings.end()) depthTestIt->second.second = m_depthTest;

    auto polygonModeIt = m_settings.find("POLYGON_MODE");
    if (polygonModeIt != m_settings.end()) polygonModeIt->second.second = m_polygonMode;

    auto faceCullingIt = m_settings.find("FACE_CULLING");
    if (faceCullingIt != m_settings.end()) faceCullingIt->second.second = m_faceCulling;

    auto debugOutputIt = m_settings.find("DEBUG_OUTPUT");
    if (debugOutputIt != m_settings.end()) debugOutputIt->second.second = m_debugOutput;
#else
    m_settings["VSYNC"].second = m_vsync;
    m_settings["LIMIT_FPS"].second = m_limitFps;
    m_settings["MAX_FPS"].second = m_maxFps;
    m_settings["BLEND"].second = m_blend;
    m_settings["DEPTH_TEST"].second = m_depthTest;
    m_settings["POLYGON_MODE"].second = m_polygonMode;
    m_settings["FACE_CULLING"].second = m_faceCulling;
    m_settings["DEBUG_OUTPUT"].second = m_debugOutput;
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