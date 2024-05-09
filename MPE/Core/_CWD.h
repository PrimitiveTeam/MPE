#pragma once

#include "MPE/Core/_CORE.h"

/**
 * @file _CWD.h
 * @brief Set the current working directory to the executable path.
 * @details This file is used to set the current working directory to the executable path.
 * @date 2024-05-05
 * @author Sebastian Termen
 */

/**
 * @def SET_EXECUTABLE_PATH_AS_CWD()
 * @brief Set the current working directory to the executable path.
 * @details This macro is used to set the current working directory to the executable path.
 * @date 2024-05-05
 * @note This macro is only available on Windows. For now.
 */

// TODO: Add support for Linux and MacOS
#ifdef MPE_PLATFORM_WINDOWS

#include <string>
#include <windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#define SET_EXECUTABLE_PATH_AS_CWD()                              \
    {                                                             \
        char path[MAX_PATH];                                      \
        if (GetModuleFileNameA(NULL, path, MAX_PATH))             \
        {                                                         \
            PathRemoveFileSpecA(path);                            \
            SetCurrentDirectoryA(path);                           \
            MPE_CORE_WARN("Working directory set to: {0}", path); \
        }                                                         \
        else                                                      \
        {                                                         \
            MPE_CORE_ERROR("Cannot set the working directory");   \
        }                                                         \
    }
#else
#error CWD currently supports only Windows.
#endif