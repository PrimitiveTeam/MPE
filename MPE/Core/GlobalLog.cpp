#include "GlobalLog.h"
#include "MPE/MPEPCH.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace MPE
{
    REF<spdlog::logger> Log::CoreLogger;
    REF<spdlog::logger> Log::ClientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        CoreLogger = spdlog::stdout_color_mt("MPE");
        CoreLogger->set_level(spdlog::level::trace);

        ClientLogger = spdlog::stdout_color_mt("APP");
        ClientLogger->set_level(spdlog::level::trace);

        MPE_CORE_WARN("ENGINE LOG INITIALIZED.");
        MPE_WARN("CLIENT LOG INITIALIZED.");
    }
}