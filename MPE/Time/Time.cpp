#include "Time.h"
#include "MPE/MPEPCH.h"

namespace MPE
{
    Time::Time(float time)
        : SYS_TIME(time)
    {
    }
    float Time::GetSeconds() const { return SYS_TIME; }
    float Time::GetMilliSeconds() const { return SYS_TIME * 1000.0f; }

    Time::operator float() const { return SYS_TIME; }
}