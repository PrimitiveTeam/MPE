#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"

namespace MPE
{
struct MPE_API WindowFpsMs
{
    float fps;
    float ms;

    // Default constructor
    WindowFpsMs() : fps(0.0f), ms(0.0f) {}

    // Update the FPS and MS
    void Update(Time deltaTime)
    {
        fps = 1.0f / (float) deltaTime;
        ms = deltaTime.GetMilliSeconds();
    }
};
}