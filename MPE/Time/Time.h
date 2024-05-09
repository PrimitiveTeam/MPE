#pragma once

#include "MPE/Core/_CORE.h"

namespace MPE
{
    class MPE_API Time
    {
    public:
        Time(float time = 0.0f);

        float GetSeconds() const;
        float GetMilliSeconds() const;

        operator float() const;

    private:
        float SYS_TIME;
    };
}