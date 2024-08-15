#pragma once

#include "MPE/Log/GlobalLog.h"

#include <chrono>
#include <functional>

/**
 * @file _TIMER.h
 * @brief Timer class for profiling.
 * @date 2024-05-05
 * @author Sebastian Termen
 */

namespace MPE
{
/**
 * @brief Timer class for profiling.
 * @details This class is used to profile code execution time.
 * @tparam FN The function type to call on stopping the timer.
 * @date 2024-05-05
 * @see _PROFILING
 */

// Can't use MPE_API as this is a header-only file (because of the template)
template <typename FN = std::function<void(const char *, float)>>
class _TIMER
{
  public:
    /**
     * @brief Construct a new _TIMER object.
     * @details This constructor is used to create a new _TIMER object with only
     * the name.
     * @param name The name of the timer.
     * @param log The logging flag of the timer.
     * @date 2024-05-05
     */
    _TIMER(const char *name, bool log = false) : m_name(name), m_func(nullptr), m_isStopped(false), m_log(log)
    {
        m_startPoint = std::chrono::high_resolution_clock::now();
    }

    /**
     * @brief Construct a new _TIMER object.
     * @details This constructor is used to create a new _TIMER object with the
     * name and a function to call on stopping.
     * @param name The name of the timer.
     * @param func The function to call on stopping the timer.
     * @param log The logging flag of the timer.
     * @date 2024-05-05
     */
    _TIMER(const char *name, FN &&func, bool log = false) : m_name(name), m_func(std::move(func)), m_isStopped(false), m_log(log)
    {
        m_startPoint = std::chrono::high_resolution_clock::now();
    }

    /**
     * @brief Destroy the _TIMER object.
     * @date 2024-05-05
     * @note If the timer is not stopped, it will stop it.
     * @see Stop()
     */
    ~_TIMER()
    {
        if (!m_isStopped)
        {
            Stop();
        }
    }

    /**
     * @brief Stop the timer.
     * @details This function is used to stop the timer and execute the function
     * if provided.
     * @date 2024-05-05
     * @note If the timer is already stopped, it will not stop it again.
     * @see FUNC
     */
    void Stop()
    {
        if (!m_isStopped)
        {
            auto END_POINT = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(END_POINT - m_startPoint).count() * 0.001f;
            m_isStopped = true;

            // Execute the function if provided
            if (m_func)
            {
                m_func(m_name, duration);
            }

            // Log the duration if logging is enabled
            if (m_log)
            {
                MPE_CORE_INFO("{0} duration: {1} ms", m_name, duration);
            }
        }
    }

  private:
    /**
     * @brief The name of the timer.
     * @date 2024-05-05
     */
    const char *m_name;
    /**
     * @brief The function to call on stopping the timer.
     * @date 2024-05-05
     */
    FN m_func;
    /**
     * @brief The starting point of the timer.
     * @date 2024-05-05
     */
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startPoint;
    /**
     * @brief The stopping flag of the timer.
     * @date 2024-05-05
     */
    bool m_isStopped;
    /**
     * @brief The logging flag of the timer.
     * @date 2024-05-05
     */
    bool m_log;
};
}

// #define PROFILE_SCOPE(name) _TIMER timer##__LINE__(name, [&](auto
// profile){PROFILE.push_back(profile);})

// in used class:
// struct PROFILE{
//     const char* NAME;
//     float TIME;
// };

// std::vector<PROFILE> SYS_PROFILE;

// THEN

// MPE::_TIMER timer("SANDBOX 2D ON UPDATE", [&](PROFILE
// profile){SYS_PROFILE.push_back(profile);});

// IMGUI:
//     for (auto&& [name, time] : SYS_PROFILE){
//     char label[50];
//     strcpy(label, name);
//     strcat(label, " %.3fms");
//     ImGui::Text(label, time);
// }
// SYS_PROFILE.clear();