#pragma once

/*
TODO: Instead of logging to JSON another approach could be to use UDP and broadcast to a running Telegraf instance.
Store in InfluxDB and explore with Grafana.
Allows for real-time exploration of a running game's timings and are built for real-time telemetry and used for micro-services all the time,
so can store a long history of a lot of data.
*/

#include <string>
#include <chrono>
#include <fstream>

namespace MPE
{
    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        uint32_t ThreadID;
    };

    struct ProfilerSession
    {
        std::string Name;
    };

    class Profiler
    {
    private:
        ProfilerSession *CURRENT_SESSION;
        std::ofstream OUTPUT;
        int PROFILE_COUNT;

    public:
        Profiler();

        void BeginSession(const std::string &name, const std::string &filepath = "results.json");

        void EndSession();

        void WriteProfile(const ProfileResult &result);

        void WriteHeader();

        void WriteFooter();

        static Profiler &Get()
        {
            static Profiler instance;
            return instance;
        }
    };

    class InstrumentationTimer
    {
    private:
        const char *NAME;
        std::chrono::time_point<std::chrono::high_resolution_clock> START_POINT;
        bool STOPPED;

    public:
        InstrumentationTimer(const char *name);

        ~InstrumentationTimer();

        void Stop();
    };
}

#ifdef MPE_DEBUG_PROFILING
#define MPE_PROFILE_START(name, filepath) ::MPE::Profiler::Get().BeginSession(name, filepath)
#define MPE_PROFILE_END() ::MPE::Profiler::Get().EndSession()
#define MPE_PROFILE_SCOPE(name) ::MPE::InstrumentationTimer timer##__LINE__(name);
#define MPE_PROFILE_FUNCTION() MPE_PROFILE_SCOPE(__FUNCSIG__)
#else
#define MPE_PROFILE_START()
#define MPE_PROFILE_END()
#define MPE_PROFILE_SCOPE()
#define MPE_PROFILE_FUNCTION()
#endif