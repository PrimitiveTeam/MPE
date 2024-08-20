#include "_PROFILING.h"
#include "MPE/MPEPCH.h"

#include <algorithm>
#include <thread>

namespace MPE
{
Profiler::Profiler() : currentSession(nullptr), profileCount(0) {}

void Profiler::BeginSession(const std::string &name, const std::string &filepath)
{
    output.open(filepath);
    WriteHeader();
    currentSession = new ProfilerSession{name};
}

void Profiler::EndSession()
{
    WriteFooter();
    output.close();
    delete currentSession;
    currentSession = nullptr;
    profileCount = 0;
}

void Profiler::WriteProfile(const ProfileResult &result)
{
    if (profileCount++ > 0) output << ",\n";

    std::string name = result.name;
    std::replace(name.begin(), name.end(), '"', '\'');

    output << "\t\t{\n";
    output << "\t\t\t\"cat\": \"function\",\n";
    output << "\t\t\t\"dur\": " << (result.end - result.start) << ",\n";
    output << "\t\t\t\"name\": \"" << name << "\",\n";
    output << "\t\t\t\"ph\": \"X\",\n";
    output << "\t\t\t\"pid\": 0,\n";
    output << "\t\t\t\"tid\": " << result.threadId << ",\n";
    output << "\t\t\t\"ts\": " << result.start;
    output << "\n\t\t}";

    output.flush();
}

void Profiler::WriteHeader()
{
    output << "{\n\t\"otherData\": {},\n\t\"traceEvents\": [\n";
    output.flush();
}

void Profiler::WriteFooter()
{
    output << "\n\t]\n}";
    output.flush();
}

InstrumentationTimer::InstrumentationTimer(const char *name) : name(name), isStopped(false)
{
    startPoint = std::chrono::high_resolution_clock::now();
}

InstrumentationTimer::~InstrumentationTimer()
{
    if (!isStopped) Stop();
}

void InstrumentationTimer::Stop()
{
    auto endPoint = std::chrono::high_resolution_clock::now();

    long long start = std::chrono::time_point_cast<std::chrono::microseconds>(startPoint).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();

    uint32_t threadId = std::hash<std::thread::id>{}(std::this_thread::get_id());
    Profiler::Get().WriteProfile({name, start, end, threadId});

    isStopped = true;
}
}