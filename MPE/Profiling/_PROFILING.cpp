#include "_PROFILING.h"
#include "MPE/MPEPCH.h"

#include <thread>
#include <algorithm>

namespace MPE
{
    Profiler::Profiler()
        : CURRENT_SESSION(nullptr), PROFILE_COUNT(0)
    {
    }

    void Profiler::BeginSession(const std::string &name, const std::string &filepath)
    {
        OUTPUT.open(filepath);
        WriteHeader();
        CURRENT_SESSION = new ProfilerSession{name};
    }

    void Profiler::EndSession()
    {
        WriteFooter();
        OUTPUT.close();
        delete CURRENT_SESSION;
        CURRENT_SESSION = nullptr;
        PROFILE_COUNT = 0;
    }

    void Profiler::WriteProfile(const ProfileResult &result)
    {
        if (PROFILE_COUNT++ > 0)
            OUTPUT << ",\n";

        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        OUTPUT << "\t\t{\n";
        OUTPUT << "\t\t\t\"cat\": \"function\",\n";
        OUTPUT << "\t\t\t\"dur\": " << (result.End - result.Start) << ",\n";
        OUTPUT << "\t\t\t\"name\": \"" << name << "\",\n";
        OUTPUT << "\t\t\t\"ph\": \"X\",\n";
        OUTPUT << "\t\t\t\"pid\": 0,\n";
        OUTPUT << "\t\t\t\"tid\": " << result.ThreadID << ",\n";
        OUTPUT << "\t\t\t\"ts\": "
               << result.Start;
        OUTPUT << "\n\t\t}";

        OUTPUT.flush();
    }

    void Profiler::WriteHeader()
    {
        OUTPUT << "{\n\t\"otherData\": {},\n\t\"traceEvents\": [\n";
        OUTPUT.flush();
    }

    void Profiler::WriteFooter()
    {
        OUTPUT << "\n\t]\n}";
        OUTPUT.flush();
    }

    InstrumentationTimer::InstrumentationTimer(const char *name)
        : NAME(name), STOPPED(false)
    {
        START_POINT = std::chrono::high_resolution_clock::now();
    }

    InstrumentationTimer::~InstrumentationTimer()
    {
        if (!STOPPED)
            Stop();
    }

    void InstrumentationTimer::Stop()
    {
        auto END_POINT = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(START_POINT).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(END_POINT).time_since_epoch().count();

        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        Profiler::Get().WriteProfile({NAME, start, end, threadID});

        STOPPED = true;
    }
}