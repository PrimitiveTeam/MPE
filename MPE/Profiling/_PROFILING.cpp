#include "_PROFILING.h"
#include "MPE/MPEPCH.h"

#include <algorithm>
#include <thread>

namespace MPE
{
Profiler::Profiler() : m_currentSession(nullptr), m_profileCount(0) {}

void Profiler::BeginSession(const std::string &name, const std::string &filepath)
{
    m_output.open(filepath);
    WriteHeader();
    m_currentSession = new ProfilerSession{name};
}

void Profiler::EndSession()
{
    WriteFooter();
    m_output.close();
    delete m_currentSession;
    m_currentSession = nullptr;
    m_profileCount = 0;
}

void Profiler::WriteProfile(const ProfileResult &result)
{
    if (m_profileCount++ > 0) m_output << ",\n";

    std::string name = result.m_name;
    std::replace(name.begin(), name.end(), '"', '\'');

    m_output << "\t\t{\n";
    m_output << "\t\t\t\"cat\": \"function\",\n";
    m_output << "\t\t\t\"dur\": " << (result.m_end - result.m_start) << ",\n";
    m_output << "\t\t\t\"name\": \"" << name << "\",\n";
    m_output << "\t\t\t\"ph\": \"X\",\n";
    m_output << "\t\t\t\"pid\": 0,\n";
    m_output << "\t\t\t\"tid\": " << result.m_threadId << ",\n";
    m_output << "\t\t\t\"ts\": " << result.m_start;
    m_output << "\n\t\t}";

    m_output.flush();
}

void Profiler::WriteHeader()
{
    m_output << "{\n\t\"otherData\": {},\n\t\"traceEvents\": [\n";
    m_output.flush();
}

void Profiler::WriteFooter()
{
    m_output << "\n\t]\n}";
    m_output.flush();
}

InstrumentationTimer::InstrumentationTimer(const char *name) : m_name(name), m_isStopped(false)
{
    m_startPoint = std::chrono::high_resolution_clock::now();
}

InstrumentationTimer::~InstrumentationTimer()
{
    if (!m_isStopped) Stop();
}

void InstrumentationTimer::Stop()
{
    auto endPoint = std::chrono::high_resolution_clock::now();

    long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startPoint).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();

    uint32_t threadId = std::hash<std::thread::id>{}(std::this_thread::get_id());
    Profiler::Get().WriteProfile({m_name, start, end, threadId});

    m_isStopped = true;
}
}