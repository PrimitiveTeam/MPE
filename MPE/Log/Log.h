#pragma once

#include "MPE/Core/_PTRS.h"

#include "spdlog/spdlog.h"

#include <string>

/**
 * @file Log.h
 * @brief Extensible logging system for the engine.
 * @date 2024-05-05
 * @author Sebastian Termen
 */

namespace MPE
{
/**
 * @brief Extensible logging system for the engine.
 * @details This file contains an extensible logging system for the engine. It
 * uses the spdlog library for logging.
 * @date 2024-05-05
 * @author Sebastian Termen
 * @see https://github.com/gabime/spdlog
 */
class MPE_API Log
{
  public:
    enum Option
    {
        // 0b00000001
        CONSOLE = 1 << 0,
        // 0b00000010
        FILE = 1 << 1,
        // 0b00000100
        MEMORY = 1 << 2
    };

    Log(const std::string &name, int options, std::string filename = "");

    static REF<Log> Create(const std::string &name, int options, std::string filename = "");

    // Logging methods
    void trace(const std::string &message);

    void info(const std::string &message);

    void warn(const std::string &message);

    void error(const std::string &message);

    void debug(const std::string &message);

    void critical(const std::string &message);

    /**
     * @brief Gets the output of the memory sink.
     * @date 2024-05-05
     * @return The output of the memory sink.
     * @note This will throw an exception if the memory sink is not enabled.
     */
    std::string getOutput();

  private:
    REF<spdlog::logger> logger;
    std::vector<REF<spdlog::sinks::sink>> sinks;
    // Store options for logic
    int options;
};
}