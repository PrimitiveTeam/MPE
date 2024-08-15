#include "GlobalLog.h"
#include "MPE/MPEPCH.h"

#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace MPE
{
REF<spdlog::logger> GlobalLog::m_coreLogger;

#ifdef MPE_ENABLE_DEBUG_LOG
REF<spdlog::logger> GlobalLog::m_debugLogger;
#endif

REF<spdlog::logger> GlobalLog::m_clientLogger;

void GlobalLog::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    m_coreLogger = spdlog::stdout_color_mt("MPE");
    m_coreLogger->set_pattern("%^[%T] %n: %v%$");
    m_coreLogger->set_level(spdlog::level::trace);

#ifdef MPE_ENABLE_DEBUG_LOG
    m_debugLogger = spdlog::stdout_color_mt("MPE_DEBUG");
    m_debugLogger->set_pattern("%^[%T] %n: %v%$");
    m_debugLogger->set_level(spdlog::level::trace);
#endif

    m_clientLogger = spdlog::stdout_color_mt("APP");
    m_clientLogger->set_pattern("%^[%T] %n: %v%$");
    m_clientLogger->set_level(spdlog::level::trace);

    MPE_CORE_WARN("ENGINE LOG INITIALIZED.");
#ifdef MPE_ENABLE_DEBUG_LOG
    MPE_DEBUG_WARN("DEBUG LOG INITIALIZED.");
#endif
    MPE_WARN("CLIENT LOG INITIALIZED.");
}
}