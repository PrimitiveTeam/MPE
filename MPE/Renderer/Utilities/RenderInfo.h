#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"

namespace MPE
{
struct MPE_API WindowFpsMs
{
    float FPS;
    float MS;

    // Default constructor
    WindowFpsMs() : FPS(0.0f), MS(0.0f) {}

    // Update the FPS and MS
    void Update(Time deltaTime)
    {
        FPS = 1.0f / (float) deltaTime;
        MS = deltaTime.GetMilliSeconds();
    }
};
}