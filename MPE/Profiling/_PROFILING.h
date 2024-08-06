#pragma once

#include "MPE/Core/_CORE.h"

/*
TODO: Instead of logging to JSON another approach could be to use UDP and
broadcast to a running Telegraf instance. Store in InfluxDB and explore with
Grafana. Allows for real-time exploration of a running game's timings and are
built for real-time telemetry and used for micro-services all the time, so can
store a long history of a lot of data.
*/

#include <chrono>
#include <fstream>
#include <string>

/**
 * @file _PROFILING.h
 * @brief Profiling system for the MPE engine.
 * @date 2024-05-05
 * @author Sebastian Termen
 */

namespace MPE
{
/**
 * @brief Profile result structure.
 * @date 2024-05-05
 */
struct MPE_API ProfileResult
{
    /**
     * @brief The name of the profile.
     * @date 2024-05-05
     */
    std::string Name;
    /**
     * @brief The start time of the profile.
     * @date 2024-05-05
     */
    long long Start, End;
    /**
     * @brief The thread ID of the profile.
     * @date 2024-05-05
     */
    uint32_t ThreadID;
};

/**
 * @brief Profiler session structure.
 * @date 2024-05-05
 */
struct MPE_API ProfilerSession
{
    /**
     * @brief The name of the session.
     * @date 2024-05-05
     */
    std::string Name;
};

/**
 * @brief Profiler class.
 * @date 2024-05-05
 */
class MPE_API Profiler
{
  public:
    /**
     * @brief Construct a new Profiler object.
     * @date 2024-05-05
     */
    Profiler();

    /**
     * @brief Begin a new profiler session.
     * @param name The name of the session.
     * @param filepath The file path of the session.
     * @date 2024-05-05
     * @note This function should be called at the start of the session.
     */
    void BeginSession(const std::string &name, const std::string &filepath = "results.json");

    /**
     * @brief End the current profiler session.
     * @date 2024-05-05
     * @note This function should be called at the end of the session.
     */
    void EndSession();

    /**
     * @brief Write a profile result.
     * @param result The profile result.
     * @date 2024-05-05
     */
    void WriteProfile(const ProfileResult &result);

    /**
     * @brief Write the header of the profiler session.
     * @date 2024-05-05
     */
    void WriteHeader();

    /**
     * @brief Write the footer of the profiler session.
     * @date 2024-05-05
     */
    void WriteFooter();

    /**
     * @brief Get the profiler instance.
     * @return The profiler instance.
     * @date 2024-05-05
     */
    static Profiler &Get()
    {
        /**
         * @brief The profiler instance.
         * @date 2024-05-05
         */
        static Profiler instance;
        /**
         * @brief The profiler instance.
         * @date 2024-05-05
         */
        return instance;
    }

  private:
    /**
     * @brief The current profiler session.
     * @date 2024-05-05
     */
    ProfilerSession *CURRENT_SESSION;
    /**
     * @brief The output file stream.
     * @date 2024-05-05
     */
    std::ofstream OUTPUT;
    /**
     * @brief The profile count.
     * @date 2024-05-05
     */
    int PROFILE_COUNT;
};

/**
 * @brief Instrumentation timer class.
 * @date 2024-05-05
 */
class MPE_API InstrumentationTimer
{
  public:
    /**
     * @brief Construct a new Instrumentation Timer object.
     * @param name The name of the timer.
     * @date 2024-05-05
     */
    InstrumentationTimer(const char *name);

    /**
     * @brief Destroy the Instrumentation Timer object.
     * @date 2024-05-05
     */
    ~InstrumentationTimer();

    /**
     * @brief Stop the timer.
     * @date 2024-05-05
     */
    void Stop();

  private:
    /**
     * @brief The name of the timer.
     * @date 2024-05-05
     */
    const char *NAME;
    /**
     * @brief The starting point of the timer.
     * @date 2024-05-05
     */
    std::chrono::time_point<std::chrono::high_resolution_clock> START_POINT;
    /**
     * @brief The stopping flag of the timer.
     * @date 2024-05-05
     */
    bool STOPPED;
};
}

#ifdef MPE_DEBUG_PROFILING
#    ifdef MPE_COMPILER_MSVC
#        define MPE_PROFILE_START(name, filepath) ::MPE::Profiler::Get().BeginSession(name, filepath)
#        define MPE_PROFILE_END() ::MPE::Profiler::Get().EndSession()
#        define MPE_PROFILE_SCOPE(name) ::MPE::InstrumentationTimer timer##__LINE__(name);
#        define MPE_PROFILE_FUNCTION() MPE_PROFILE_SCOPE(__FUNCSIG__)

#    elif MPE_COMPILER_CLANG or MPE_COMPILER_GNU or MPE_COMPILER_APPLECLANG
#        define MPE_PROFILE_START(name, filepath) ::MPE::Profiler::Get().BeginSession(name, filepath)
#        define MPE_PROFILE_END() ::MPE::Profiler::Get().EndSession()
#        define MPE_PROFILE_SCOPE(name) ::MPE::InstrumentationTimer timer##__LINE__(name);
#        define MPE_PROFILE_FUNCTION() MPE_PROFILE_SCOPE(__PRETTY_FUNCTION__)

#    endif
#else
#    define MPE_PROFILE_START(name, filepath)
#    define MPE_PROFILE_END()
#    define MPE_PROFILE_SCOPE(name)
#    define MPE_PROFILE_FUNCTION()
#endif

#ifdef MPE_CORE_DEBUG_PROFILING
#    ifdef MPE_COMPILER_MSVC
#        define MPE_CORE_PROFILE_START(name, filepath) ::MPE::Profiler::Get().BeginSession(name, filepath)
#        define MPE_CORE_PROFILE_END() ::MPE::Profiler::Get().EndSession()
#        define MPE_CORE_PROFILE_SCOPE(name) ::MPE::InstrumentationTimer timer##__LINE__(name);
#        define MPE_CORE_PROFILE_FUNCTION() MPE_PROFILE_SCOPE(__FUNCSIG__)

#    elif MPE_COMPILER_CLANG or MPE_COMPILER_GNU or MPE_COMPILER_APPLECLANG
#        define MPE_CORE_PROFILE_START(name, filepath) ::MPE::Profiler::Get().BeginSession(name, filepath)
#        define MPE_CORE_PROFILE_END() ::MPE::Profiler::Get().EndSession()
#        define MPE_CORE_PROFILE_SCOPE(name) ::MPE::InstrumentationTimer timer##__LINE__(name);
#        define MPE_CORE_PROFILE_FUNCTION() MPE_PROFILE_SCOPE(__PRETTY_FUNCTION__)

#    endif
#else
#    define MPE_CORE_PROFILE_START(name, filepath)
#    define MPE_CORE_PROFILE_END()
#    define MPE_CORE_PROFILE_SCOPE(name)
#    define MPE_CORE_PROFILE_FUNCTION()
#endif

/**
 * @def MPE_DEBUG_PROFILING
 * @brief Debug profiling flag for the MPE engine.
 * @details This flag is used to enable debug profiling for the MPE engine. This
 * is used to profile more abstracted code.
 * @date 2024-05-05
 * @note This macro is only available in debug builds.
 */

/**
 * @def MPE_PROFILE_START(name, filepath)
 * @brief Start a new profiler session.
 * @details This macro is used to start a new profiler session.
 * @param name The name of the session.
 * @param filepath The file path of the session.
 * @date 2024-05-05
 * @note This macro is only available in debug builds.
 */

/**
 * @def MPE_PROFILE_END()
 * @brief End the current profiler session.
 * @details This macro is used to end the current profiler session.
 * @date 2024-05-05
 * @note This macro is only available in debug builds.
 */

/**
 * @def MPE_PROFILE_SCOPE(name)
 * @brief Profile scope macro for the MPE engine.
 * @details This macro is used to profile a scope in the MPE engine.
 * @param name The name of the scope.
 * @date 2024-05-05
 * @note This macro is only available in debug builds.
 */

/**
 * @def MPE_PROFILE_FUNCTION()
 * @brief Profile function macro for the MPE engine.
 * @details This macro is used to profile a function in the MPE engine.
 * @date 2024-05-05
 * @note This macro is only available in debug builds.
 */

/**
 * @def MPE_CORE_DEBUG_PROFILING
 * @brief Core debug profiling flag for the MPE engine.
 * @details This flag is used to enable core debug profiling for the MPE engine.
 * This is used to profile the core of the engine which can slow down the engine
 * by a lot.
 * @date 2024-05-05
 * @note This macro is only available in debug builds.
 */

/**
 * @def MPE_CORE_PROFILE_START(name, filepath)
 * @brief Start a new profiler session.
 * @details This macro is used to start a new profiler session.
 * @param name The name of the session.
 * @param filepath The file path of the session.
 * @date 2024-05-05
 * @note This macro is only available in debug builds.
 */

/**
 * @def MPE_CORE_PROFILE_END()
 * @brief End the current profiler session.
 * @details This macro is used to end the current profiler session.
 * @date 2024-05-05
 * @note This macro is only available in debug builds.
 */

/**
 * @def MPE_CORE_PROFILE_SCOPE(name)
 * @brief Profile scope macro for the MPE engine.
 * @details This macro is used to profile a scope in the MPE engine.
 * @param name The name of the scope.
 * @date 2024-05-05
 * @note This macro is only available in debug builds.
 */
