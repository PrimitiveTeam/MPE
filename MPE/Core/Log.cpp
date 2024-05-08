#include "Log.h"
#include "MPE/MPEPCH.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/fmt/ostr.h"

namespace MPE
{
    Log::Log(const std::string &name, int options, std::string filename)
    {
        if (options & CONSOLE)
        {
            auto console_sink = NEWREF<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_pattern("[%H:%M:%S] [%^%L%$] [%n]: %v");
            sinks.push_back(console_sink);
        }
        if (options & FILE)
        {
            if (filename.empty())
            {
                throw std::runtime_error("Filename must be provided for file logging.");
            }
            // Append .log extension if not provided
            if (filename.find(".log") == std::string::npos)
            {
                filename.append(".log");
            }

            auto file_sink = NEWREF<spdlog::sinks::basic_file_sink_mt>(filename, true);
            file_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%L] [%n]: %v");
            sinks.push_back(file_sink);
        }

        logger = NEWREF<spdlog::logger>(name, begin(sinks), end(sinks));
        logger->set_level(spdlog::level::trace);
    }

    // Logging methods
    void Log::trace(const std::string &message)
    {
        logger->trace(message);
    }

    void Log::info(const std::string &message)
    {
        logger->info(message);
    }

    void Log::warn(const std::string &message)
    {
        logger->warn(message);
    }

    void Log::error(const std::string &message)
    {
        logger->error(message);
    }

    void Log::debug(const std::string &message)
    {
        logger->debug(message);
    }

    void Log::critical(const std::string &message)
    {
        logger->critical(message);
    }
}