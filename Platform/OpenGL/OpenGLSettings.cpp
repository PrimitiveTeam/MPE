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
    m_settings.insert(std::make_pair("DRAW_MODE", std::make_pair("DRAW_MODE", m_drawMode)));
    m_settings.insert(std::make_pair("FACE_CULLING", std::make_pair("FACE_CULLING", m_faceCulling)));
    m_settings.insert(std::make_pair("DEBUG_OUTPUT", std::make_pair("DEBUG_OUTPUT", m_debugOutput)));
#else
    m_settings["VSYNC"] = std::make_pair("VSYNC", m_vsync);
    m_settings["LIMIT_FPS"] = std::make_pair("LIMIT_FPS", m_limitFps);
    m_settings["MAX_FPS"] = std::make_pair("MAX_FPS", m_maxFps);
    m_settings["BLEND"] = std::make_pair("BLEND", m_blend);
    m_settings["DEPTH_TEST"] = std::make_pair("DEPTH_TEST", m_depthTest);
    m_settings["DRAW_MODE"] = std::make_pair("DRAW_MODE", m_drawMode);
    m_settings["FACE_CULLING"] = std::make_pair("FACE_CULLING", m_faceCulling);
    m_settings["DEBUG_OUTPUT"] = std::make_pair("DEBUG_OUTPUT", m_debugOutput);
#endif
}

// GRAPHICAL CONTEXT PROPS

std::string OpenGLSettings::GetGraphicalContextPropsAsString()
{
    std::string OpenGLInfo = "OpenGL Info:\n";
    OpenGLInfo += "\tVersion: " + std::to_string(m_graphicalContextProps->majorVersion) + "." + std::to_string(m_graphicalContextProps->minorVersion) + "\n";
    OpenGLInfo += "\tVendor: " + m_graphicalContextProps->vendor + "\n";
    OpenGLInfo += "\tRenderer: " + m_graphicalContextProps->renderer + "\n";
    OpenGLInfo += "\tHardcode shader type limit: " + std::to_string(m_graphicalContextProps->shaderTypeAmount);

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
    return m_depthTest;
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

void OpenGLSettings::ToggleDrawMode()
{
    this->SetDrawMode(static_cast<DrawMode>((m_drawMode + 1) % 3));
}

DrawMode OpenGLSettings::GetDrawMode() const
{
    return m_drawMode;
}

void OpenGLSettings::SetDrawMode(DrawMode drawMode)
{
    m_drawMode = drawMode;

    switch (m_drawMode)
    {
        case FILL:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case LINE:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case POINT:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            break;
    }

#if MPE_PLATFORM_LINUX
    UpdateSettingsAndSendEvent("DRAW_MODE", m_drawMode);
#else
    UpdateSettingsAndSendEvent(m_settings["DRAW_MODE"].first, m_drawMode);
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

    auto drawModeIt = m_settings.find("DRAW_MODE");
    if (drawModeIt != m_settings.end()) drawModeIt->second.second = m_drawMode;

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
    m_settings["DRAW_MODE"].second = m_drawMode;
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