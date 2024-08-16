#include "Log.h"
#include "MPE/MPEPCH.h"

#include "MPE/Log/CustomSinks/MemorySink.h"

#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace MPE
{
Log::Log(const std::string &name, int options, std::string filename) : m_options(options)
{
    if (options & CONSOLE)
    {
        auto console_sink = NEWREF<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("[%H:%M:%S] [%^%L%$] [%n]: %v");
        m_sinks.push_back(console_sink);
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
        m_sinks.push_back(file_sink);
    }
    if (options & MEMORY)
    {
        auto memory_sink = std::make_shared<MPE::MemorySink<std::mutex>>();
        m_sinks.push_back(memory_sink);
    }

    m_logger = NEWREF<spdlog::logger>(name, begin(m_sinks), end(m_sinks));
    m_logger->set_level(spdlog::level::trace);
}

REF<Log> Log::Create(const std::string &name, int options, std::string filename)
{
    return NEWREF<Log>(name, options, filename);
}

// Logging methods
void Log::trace(const std::string &message)
{
    m_logger->trace(message);
}

void Log::info(const std::string &message)
{
    m_logger->info(message);
}

void Log::warn(const std::string &message)
{
    m_logger->warn(message);
}

void Log::error(const std::string &message)
{
    m_logger->error(message);
}

void Log::debug(const std::string &message)
{
    m_logger->debug(message);
}

void Log::critical(const std::string &message)
{
    m_logger->critical(message);
}

std::string Log::getOutput()
{
    // Check if memory sink is enabled
    if (!(m_options & MEMORY))
    {
        throw std::runtime_error("Memory logging is not enabled.");
    }
    // This does not check type of sink, it assumes the last sink is MemorySink
    auto memory_sink = std::dynamic_pointer_cast<MPE::MemorySink<std::mutex>>(m_sinks.back());
    return memory_sink->get_contents_and_clear();
}
}