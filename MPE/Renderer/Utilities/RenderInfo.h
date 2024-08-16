#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"

namespace MPE
{
struct MPE_API WindowFpsMs
{
    float m_fps;
    float m_ms;

    // Default constructor
    WindowFpsMs() : m_fps(0.0f), m_ms(0.0f) {}

    // Update the FPS and MS
    void Update(Time deltaTime)
    {
        m_fps = 1.0f / (float) deltaTime;
        m_ms = deltaTime.GetMilliSeconds();
    }
};
}