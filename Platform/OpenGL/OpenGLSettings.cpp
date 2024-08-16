#include "OpenGLSettings.h"
#include "MPEPCH.h"

#include "MPE/App/App.h"
#include "MPE/Events/EventGraphics.h"
#include "Platform/OpenGL/Utilities/OpenGLUtilities.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace MPE
{
OpenGLSettings::OpenGLSettings()
{
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

std::string OpenGLSettings::GetGraphicalContextPropsAsString()
{
    std::string OpenGLInfo = "OpenGL Info:\n";
    OpenGLInfo +=
        "\tVersion: " + std::to_string(m_graphicalContextProps->m_majorVersion) + "." + std::to_string(m_graphicalContextProps->m_minorVersion) + "\n";
    OpenGLInfo += "\tVendor: " + m_graphicalContextProps->m_vendor + "\n";
    OpenGLInfo += "\tRenderer: " + m_graphicalContextProps->m_renderer + "\n";
    OpenGLInfo += "\tHardcode shader type limit: " + std::to_string(m_graphicalContextProps->m_shaderTypeAmount);

    return OpenGLInfo;
}

// VSYNC

void OpenGLSettings::ToggleVsync()
{
    this->SetVsync(!m_vsync);
}

bool OpenGLSettings::GetVsync() const
{
    return m_vsync;
}

void OpenGLSettings::SetVsync(bool vsync)
{
    m_vsync = vsync;

    if (m_vsync)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("VSYNC", m_vsync);
#else
    UpdateSettingsAndSendEvent(m_settings["VSYNC"].first, m_vsync);
#endif
}

// LIMIT FPS

void OpenGLSettings::ToggleLimitFPS()
{
    this->SetLimitFPS(!m_limitFps);
}

bool OpenGLSettings::GetLimitFPS() const
{
    return m_limitFps;
}

void OpenGLSettings::SetLimitFPS(bool limitFPS)
{
    m_limitFps = limitFPS;

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("LIMIT_FPS", m_limitFps);
#else
    UpdateSettingsAndSendEvent(m_settings["LIMIT_FPS"].first, m_limitFps);
#endif
}

// MAX FPS

void OpenGLSettings::SetMaxFPS(uint8_t maxFPS)
{
    m_maxFps = maxFPS;

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("MAX_FPS", m_maxFps);
#else
    UpdateSettingsAndSendEvent(m_settings["MAX_FPS"].first, m_maxFps);
#endif
}

uint8_t OpenGLSettings::GetMaxFPS() const
{
    return m_maxFps;
}

// BLEND

void OpenGLSettings::ToggleBlend()
{
    this->SetBlend(!m_blend);
}

bool OpenGLSettings::GetBlend() const
{
    return m_blend;
}

void OpenGLSettings::SetBlend(bool blend)
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

void OpenGLSettings::ToggleDepthTest()
{
    this->SetDepthTest(!m_blend);
}

bool OpenGLSettings::GetDepthTest() const
{
    return m_blend;
}

void OpenGLSettings::SetDepthTest(bool depthTest)
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

void OpenGLSettings::TogglePolygonMode()
{
    this->SetPolygonMode(!m_polygonMode);
}

bool OpenGLSettings::GetPolygonMode() const
{
    return m_polygonMode;
}

void OpenGLSettings::SetPolygonMode(bool polygonMode)
{
    m_polygonMode = polygonMode;

    if (m_polygonMode)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("POLYGON_MODE", m_polygonMode);
#else
    UpdateSettingsAndSendEvent(m_settings["POLYGON_MODE"].first, m_polygonMode);
#endif
}

// FACE CULLING

void OpenGLSettings::ToggleFaceCulling()
{
    this->SetFaceCulling(!m_faceCulling);
}

bool OpenGLSettings::GetFaceCulling() const
{
    return m_faceCulling;
}

void OpenGLSettings::SetFaceCulling(bool faceCulling)
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

void OpenGLSettings::ToggleDebugOutput()
{
    this->SetDebugOutput(!m_debugOutput);
}

bool OpenGLSettings::GetDebugOutput() const
{
    return m_debugOutput;
}

void OpenGLSettings::SetDebugOutput(bool debugOutput)
{
    // This is not available on OpenGL < 4.3
    if (OpenGLUtilities::IsOpenGLVersionLowerThan(4, 3))
    {
        MPE_CORE_WARN("Debug output is not available on OpenGL version lower than 4.3.");
        return;
    }

    m_debugOutput = debugOutput;

    if (m_debugOutput)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback((GLDEBUGPROC) OpenGLUtilities::LogOpenGLDebugOutput, nullptr);
    }
    else
    {
        glDisable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(nullptr, nullptr);
    }

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("DEBUG_OUTPUT", m_debugOutput);
#else
    UpdateSettingsAndSendEvent(m_settings["DEBUG_OUTPUT"].first, m_debugOutput);
#endif
}

// SETTINGS

std::string OpenGLSettings::GetSettings() const
{
    std::string settings = "";
    for (auto setting : m_settings)
    {
        settings += setting.second.first + ": " + (setting.second.second ? "ON" : "OFF") + "\n";
    }
    return settings;
}

void OpenGLSettings::UpdateSettings()
{
    glCheckError();

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
    if (depthTestIt != m_settings.end()) depthTestIt->second.second = m_blend;

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
    m_settings["DEPTH_TEST"].second = m_blend;
    m_settings["POLYGON_MODE"].second = m_polygonMode;
    m_settings["FACE_CULLING"].second = m_faceCulling;
    m_settings["DEBUG_OUTPUT"].second = m_debugOutput;
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