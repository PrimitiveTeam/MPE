#include "OpenGLSettings.h"
#include "MPEPCH.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace MPE
{
OpenGLSettings::OpenGLSettings()
{
    _SETTINGS["VSYNC"] = std::make_pair("VSYNC", _VSYNC);
    _SETTINGS["BLEND"] = std::make_pair("BLEND", _BLEND);
    _SETTINGS["DEPTH_TEST"] = std::make_pair("DEPTH_TEST", _DEPTH_TEST);
}

// VSYNC

void OpenGLSettings::ToggleVsync()
{
    _VSYNC = !_VSYNC;

    switch (_VSYNC)
    {
        case true:
            glfwSwapInterval(1);
            break;
        case false:
            glfwSwapInterval(0);
            break;
    }

    UpdateSettings();
}

bool OpenGLSettings::GetVsync() const
{
    return _VSYNC;
}

void OpenGLSettings::SetVsync(bool vsync)
{
    _VSYNC = vsync;

    switch (_VSYNC)
    {
        case true:
            glfwSwapInterval(1);
            break;
        case false:
            glfwSwapInterval(0);
            break;
    }

    UpdateSettings();
}

// BLEND

void OpenGLSettings::ToggleBlend()
{
    _BLEND = !_BLEND;

    switch (_BLEND)
    {
        case true:
            glEnable(GL_BLEND);
            break;
        case false:
            glDisable(GL_BLEND);
            break;
    }

    UpdateSettings();
}

bool OpenGLSettings::GetBlend() const
{
    return _BLEND;
}

void OpenGLSettings::SetBlend(bool blend)
{
    _BLEND = blend;

    switch (_BLEND)
    {
        case true:
            glEnable(GL_BLEND);
            break;
        case false:
            glDisable(GL_BLEND);
            break;
    }

    UpdateSettings();
}

// DEPTH TEST

void OpenGLSettings::ToggleDepthTest()
{
    _DEPTH_TEST = !_DEPTH_TEST;

    switch (_DEPTH_TEST)
    {
        case true:
            glEnable(GL_DEPTH_TEST);
            break;
        case false:
            glDisable(GL_DEPTH_TEST);
            break;
    }

    UpdateSettings();
}

bool OpenGLSettings::GetDepthTest() const
{
    return _DEPTH_TEST;
}

void OpenGLSettings::SetDepthTest(bool depthTest)
{
    _DEPTH_TEST = depthTest;

    switch (_DEPTH_TEST)
    {
        case true:
            glEnable(GL_DEPTH_TEST);
            break;
        case false:
            glDisable(GL_DEPTH_TEST);
            break;
    }

    UpdateSettings();
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
    _SETTINGS["VSYNC"].second = _VSYNC;
    _SETTINGS["BLEND"].second = _BLEND;
    _SETTINGS["DEPTH_TEST"].second = _DEPTH_TEST;
}
}