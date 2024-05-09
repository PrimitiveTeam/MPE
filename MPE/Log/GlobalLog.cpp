#include "GlobalLog.h"
#include "MPE/MPEPCH.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace MPE
{
    REF<spdlog::logger> GlobalLog::CoreLogger;

#ifdef MPE_ENABLE_DEBUG_LOG
    REF<spdlog::logger> GlobalLog::DebugLogger;
#endif

    REF<spdlog::logger> GlobalLog::ClientLogger;

    void GlobalLog::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        CoreLogger = spdlog::stdout_color_mt("MPE");
        CoreLogger->set_pattern("%^[%T] %n: %v%$");
        CoreLogger->set_level(spdlog::level::trace);

#ifdef MPE_ENABLE_DEBUG_LOG
        DebugLogger = spdlog::stdout_color_mt("MPE_DEBUG");
        DebugLogger->set_pattern("%^[%T] %n: %v%$");
        DebugLogger->set_level(spdlog::level::trace);
#endif

        ClientLogger = spdlog::stdout_color_mt("APP");
        ClientLogger->set_pattern("%^[%T] %n: %v%$");
        ClientLogger->set_level(spdlog::level::trace);

        MPE_CORE_WARN("ENGINE LOG INITIALIZED.");
#ifdef MPE_ENABLE_DEBUG_LOG
        MPE_DEBUG_WARN("DEBUG LOG INITIALIZED.");
#endif
        MPE_WARN("CLIENT LOG INITIALIZED.");
    }
}