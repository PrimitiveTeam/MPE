#pragma once

#include "MPE/Core/_CORE.h"
#include "spdlog/spdlog.h"

/**
 * @file GlobalLog.h
 * @brief Main logging system for the engine.
 * @details This is meant for a global logging system for the engine.
 * @date 2024-05-05
 * @author Sebastian Termen
 */

namespace MPE
{
    /**
     * @brief Main logging system for the engine.
     * @details This file contains the main logging system for the engine. It uses the spdlog library for logging.
     * @date 2024-05-05
     * @author Sebastian Termen
     * @see https://github.com/gabime/spdlog
     */
    class MPE_API Log
    {
    public:
        /**
         * @brief Initializes the logging system.
         * @details This function initializes the logging system for the engine.
         * @date 2024-05-05
         * @note This function should be called at the start of the engine.
         */
        static void Init();

        /**
         * @brief Gets the core logger.
         * @details This function returns the core logger.
         * @date 2024-05-05
         * @return The core logger.
         */
        inline static REF<spdlog::logger> &GetCoreLogger() { return CoreLogger; }

        /**
         * @brief Gets the client logger.
         * @details This function returns the client logger.
         * @date 2024-05-05
         * @return The client logger.
         */
        inline static REF<spdlog::logger> &GetClientLogger() { return ClientLogger; }

    private:
        /**
         * @brief The core logger.
         * @date 2024-05-05
         * @see GetCoreLogger()
         */
        static REF<spdlog::logger> CoreLogger;
        /**
         * @brief The client logger.
         * @date 2024-05-05
         * @see GetClientLogger()
         */
        static REF<spdlog::logger> ClientLogger;
    };
}

// ENGINE SIDE LOGS
#define MPE_CORE_ERROR(...) ::MPE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MPE_CORE_WARN(...) ::MPE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MPE_CORE_INFO(...) ::MPE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MPE_CORE_TRACE(...) ::MPE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MPE_CORE_FATAL(...) ::MPE::Log::GetCoreLogger()->fatal(__VA_ARGS__)
// CLIENT SIDE LOGS
#define MPE_ERROR(...) ::MPE::Log::GetClientLogger()->error(__VA_ARGS__)
#define MPE_WARN(...) ::MPE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MPE_INFO(...) ::MPE::Log::GetClientLogger()->info(__VA_ARGS__)
#define MPE_TRACE(...) ::MPE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MPE_FATAL(...) ::MPE::Log::GetClientLogger()->fatal(__VA_ARGS__)

/**
 * @def MPE_CORE_ERROR(...)
 * @brief Error logging macro for the MPE engine.
 * @details This macro is used to log an error message to the core logger.
 * @date 2024-05-05
 * @param ... The error message to log.
 * @see GetCoreLogger()
 */

/**
 * @def MPE_CORE_WARN(...)
 * @brief Warning logging macro for the MPE engine.
 * @details This macro is used to log a warning message to the core logger.
 * @date 2024-05-05
 * @param ... The warning message to log.
 * @see GetCoreLogger()
 */

/**
 * @def MPE_CORE_INFO(...)
 * @brief Information logging macro for the MPE engine.
 * @details This macro is used to log an information message to the core logger.
 * @date 2024-05-05
 * @param ... The information message to log.
 * @see GetCoreLogger()
 */

/**
 * @def MPE_CORE_TRACE(...)
 * @brief Trace logging macro for the MPE engine.
 * @details This macro is used to log a trace message to the core logger.
 * @date 2024-05-05
 * @param ... The trace message to log.
 * @see GetCoreLogger()
 */

/**
 * @def MPE_CORE_FATAL(...)
 * @brief Fatal logging macro for the MPE engine.
 * @details This macro is used to log a fatal message to the core logger.
 * @date 2024-05-05
 * @param ... The fatal message to log.
 * @see GetCoreLogger()
 */

/**
 * @def MPE_ERROR(...)
 * @brief Error logging macro for the MPE engine.
 * @details This macro is used to log an error message to the client logger.
 * @date 2024-05-05
 * @param ... The error message to log.
 * @see GetClientLogger()
 */

/**
 * @def MPE_WARN(...)
 * @brief Warning logging macro for the MPE engine.
 * @details This macro is used to log a warning message to the client logger.
 * @date 2024-05-05
 * @param ... The warning message to log.
 * @see GetClientLogger()
 */

/**
 * @def MPE_INFO(...)
 * @brief Information logging macro for the MPE engine.
 * @details This macro is used to log an information message to the client logger.
 * @date 2024-05-05
 * @param ... The information message to log.
 * @see GetClientLogger()
 */

/**
 * @def MPE_TRACE(...)
 * @brief Trace logging macro for the MPE engine.
 * @details This macro is used to log a trace message to the client logger.
 * @date 2024-05-05
 * @param ... The trace message to log.
 * @see GetClientLogger()
 */

/**
 * @def MPE_FATAL(...)
 * @brief Fatal logging macro for the MPE engine.
 * @details This macro is used to log a fatal message to the client logger.
 * @date 2024-05-05
 * @param ... The fatal message to log.
 * @see GetClientLogger()
 */