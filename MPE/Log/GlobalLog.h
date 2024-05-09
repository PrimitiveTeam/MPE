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
    class MPE_API GlobalLog
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
         * @brief Gets the debug logger.
         * @details This function returns the debug logger.
         * @date 2024-05-05
         * @return The debug logger.
         */
        inline static REF<spdlog::logger> &GetDebugLogger() { return DebugLogger; }

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
         * @brief The debug logger.
         * @details This logger is only available in debug builds.
         * @date 2024-05-05
         * @see GetDebugLogger()
         */
        static REF<spdlog::logger> DebugLogger;

        /**
         * @brief The client logger.
         * @date 2024-05-05
         * @see GetClientLogger()
         */
        static REF<spdlog::logger> ClientLogger;
    };
}

// CORE ENGINE LOGS
#define MPE_CORE_TRACE(...) ::MPE::GlobalLog::GetCoreLogger()->trace(__VA_ARGS__)
#define MPE_CORE_INFO(...) ::MPE::GlobalLog::GetCoreLogger()->info(__VA_ARGS__)
#define MPE_CORE_WARN(...) ::MPE::GlobalLog::GetCoreLogger()->warn(__VA_ARGS__)
#define MPE_CORE_ERROR(...) ::MPE::GlobalLog::GetCoreLogger()->error(__VA_ARGS__)
#define MPE_CORE_FATAL(...) ::MPE::GlobalLog::GetCoreLogger()->fatal(__VA_ARGS__)
// DEBUG ENGINE LOGS
#ifdef MPE_ENABLE_DEBUG_LOG
#define MPE_DEBUG_TRACE(...) ::MPE::GlobalLog::GetDebugLogger()->trace(__VA_ARGS__)
#define MPE_DEBUG_INFO(...) ::MPE::GlobalLog::GetDebugLogger()->info(__VA_ARGS__)
#define MPE_DEBUG_WARN(...) ::MPE::GlobalLog::GetDebugLogger()->warn(__VA_ARGS__)
#define MPE_DEBUG_ERROR(...) ::MPE::GlobalLog::GetDebugLogger()->error(__VA_ARGS__)
#define MPE_DEBUG_FATAL(...) ::MPE::GlobalLog::GetDebugLogger()->fatal(__VA_ARGS__)
#endif
// CLIENT MAIN LOGS
#define MPE_TRACE(...) ::MPE::GlobalLog::GetClientLogger()->trace(__VA_ARGS__)
#define MPE_INFO(...) ::MPE::GlobalLog::GetClientLogger()->info(__VA_ARGS__)
#define MPE_WARN(...) ::MPE::GlobalLog::GetClientLogger()->warn(__VA_ARGS__)
#define MPE_ERROR(...) ::MPE::GlobalLog::GetClientLogger()->error(__VA_ARGS__)
#define MPE_FATAL(...) ::MPE::GlobalLog::GetClientLogger()->fatal(__VA_ARGS__)

/**
 * @def MPE_CORE_TRACE(...)
 * @brief Trace logging macro for the MPE engine.
 * @details This macro is used to log a trace message to the core logger.
 * @date 2024-05-05
 * @param ... The trace message to log.
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
 * @def MPE_CORE_WARN(...)
 * @brief Warning logging macro for the MPE engine.
 * @details This macro is used to log a warning message to the core logger.
 * @date 2024-05-05
 * @param ... The warning message to log.
 * @see GetCoreLogger()
 */

/**
 * @def MPE_CORE_ERROR(...)
 * @brief Error logging macro for the MPE engine.
 * @details This macro is used to log an error message to the core logger.
 * @date 2024-05-05
 * @param ... The error message to log.
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
 * @def MPE_DEBUG_TRACE(...)
 * @brief Trace logging macro for the MPE engine.
 * @details This macro is used to log a trace message to the debug logger.
 * @date 2024-05-05
 * @param ... The trace message to log.
 * @see GetDebugLogger()
 * @note This macro is only available in debug builds.
 */

/**
 * @def MPE_DEBUG_INFO(...)
 * @brief Information logging macro for the MPE engine.
 * @details This macro is used to log an information message to the debug logger.
 * @date 2024-05-05
 * @param ... The information message to log.
 * @see GetDebugLogger()
 * @note This macro is only available in debug builds.
 */

/**
 * @def MPE_DEBUG_WARN(...)
 * @brief Warning logging macro for the MPE engine.
 * @details This macro is used to log a warning message to the debug logger.
 * @date 2024-05-05
 * @param ... The warning message to log.
 * @see GetDebugLogger()
 * @note This macro is only available in debug builds.
 */

/**
 * @def MPE_DEBUG_ERROR(...)
 * @brief Error logging macro for the MPE engine.
 * @details This macro is used to log an error message to the debug logger.
 * @date 2024-05-05
 * @param ... The error message to log.
 * @see GetDebugLogger()
 * @note This macro is only available in debug builds.
 */

/**
 * @def MPE_DEBUG_FATAL(...)
 * @brief Fatal logging macro for the MPE engine.
 * @details This macro is used to log a fatal message to the debug logger.
 * @date 2024-05-05
 * @param ... The fatal message to log.
 * @see GetDebugLogger()
 * @note This macro is only available in debug builds.
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
 * @def MPE_INFO(...)
 * @brief Information logging macro for the MPE engine.
 * @details This macro is used to log an information message to the client logger.
 * @date 2024-05-05
 * @param ... The information message to log.
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
 * @def MPE_ERROR(...)
 * @brief Error logging macro for the MPE engine.
 * @details This macro is used to log an error message to the client logger.
 * @date 2024-05-05
 * @param ... The error message to log.
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