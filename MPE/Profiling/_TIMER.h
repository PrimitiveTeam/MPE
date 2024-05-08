#pragma once

#include "MPE/Core/GlobalLog.h"

#include <chrono>
#include <functional>

namespace MPE
{
    template <typename FN = std::function<void(const char *, float)>>
    class _TIMER
    {
    private:
        const char *NAME;
        FN FUNC;
        std::chrono::time_point<std::chrono::high_resolution_clock> START_POINT;
        bool STOPPED;
        bool LOG;

    public:
        // Constructor with only the name - no action after stopping
        _TIMER(const char *name, bool log = false)
            : NAME(name), FUNC(nullptr), STOPPED(false), LOG(log)
        {
            START_POINT = std::chrono::high_resolution_clock::now();
        }

        // Constructor with a name and a function to call on stopping
        _TIMER(const char *name, FN &&func, bool log = false)
            : NAME(name), FUNC(std::move(func)), STOPPED(false), LOG(log)
        {
            START_POINT = std::chrono::high_resolution_clock::now();
        }

        ~_TIMER()
        {
            if (!STOPPED)
            {
                Stop();
            }
        }

        void Stop()
        {
            if (!STOPPED)
            {
                auto END_POINT = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(END_POINT - START_POINT).count() * 0.001f;
                STOPPED = true;

                // Execute the function if provided
                if (FUNC)
                {
                    FUNC(NAME, duration);
                }

                // Log the duration if logging is enabled
                if (LOG)
                {
                    MPE_CORE_INFO("{0} duration: {1} ms", NAME, duration);
                }
            }
        }
    };
}

// #define PROFILE_SCOPE(name) _TIMER timer##__LINE__(name, [&](auto profile){PROFILE.push_back(profile);})

// in used class:
// struct PROFILE{
//     const char* NAME;
//     float TIME;
// };

// std::vector<PROFILE> SYS_PROFILE;

// THEN

// MPE::_TIMER timer("SANDBOX 2D ON UPDATE", [&](PROFILE profile){SYS_PROFILE.push_back(profile);});

// IMGUI:
//     for (auto&& [name, time] : SYS_PROFILE){
//     char label[50];
//     strcpy(label, name);
//     strcat(label, " %.3fms");
//     ImGui::Text(label, time);
// }
// SYS_PROFILE.clear();