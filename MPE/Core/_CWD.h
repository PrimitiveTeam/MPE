#pragma once

#include "MPE/Core/_CORE.h"

#include <string>
#include <windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

// TODO: Add support for Linux and MacOS
#ifdef MPE_PLATFORM_WINDOWS
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