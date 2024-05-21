#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"

namespace MPE
{
struct MPE_API WINDOW_FPS_MS
{
    float FPS;
    float MS;

    // Default constructor
    WINDOW_FPS_MS() : FPS(0.0f), MS(0.0f) {}

    // Update the FPS and MS
    void Update(Time deltaTime)
    {
        FPS = 1.0f / (float) deltaTime;
        MS = deltaTime.GetMilliSeconds();
    }
};
}