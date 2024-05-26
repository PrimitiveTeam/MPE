#pragma once

// CMAKE BUILD-SET DEFINITIONS:
// MPE ASSERTIONS
#ifdef MPE_ENABLE_ASSERTS
// LOGGING ASSERTIONS FOR DEBUG BUILDS
#    ifdef MPE_PLATFORM_WINDOWS
// WINDOWS ONLY SOLUTION FOR ASSERTIONS

#        define MPE_ASSERT(x, ...)                                   \
            {                                                        \
                if (!(x))                                            \
                {                                                    \
                    MPE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
                    __debugbreak();                                  \
                }                                                    \
            }
#        define MPE_CORE_ASSERT(x, ...)                                   \
            {                                                             \
                if (!(x))                                                 \
                {                                                         \
                    MPE_CORE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
                    __debugbreak();                                       \
                }                                                         \
            }
#    elif MPE_PLATFORM_LINUX or MPE_PLATFORM_OSX
// LINUX ONLY SOLUTION FOR ASSERTIONS
// we should also try to use this if possible defined(SIGTRAP) (i.e., POSIX),
// raise(SIGTRAP)
#        include <signal.h>

#        ifdef SIGTRAP
#            define MPE_ASSERT(x, ...)                                   \
                {                                                        \
                    if (!(x))                                            \
                    {                                                    \
                        MPE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
                        raise(SIGTRAP);                                  \
                    }                                                    \
                }
#            define MPE_CORE_ASSERT(x, ...)                                   \
                {                                                             \
                    if (!(x))                                                 \
                    {                                                         \
                        MPE_CORE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
                        raise(SIGTRAP);                                       \
                    }                                                         \
                }

#        else

#            define MPE_ASSERT(x, ...)                                   \
                {                                                        \
                    if (!(x))                                            \
                    {                                                    \
                        MPE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
                        __builtin_trap();                                \
                    }                                                    \
                }
#            define MPE_CORE_ASSERT(x, ...)                                   \
                {                                                             \
                    if (!(x))                                                 \
                    {                                                         \
                        MPE_CORE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
                        __builtin_trap();                                     \
                    }                                                         \
                }

#        endif
#    endif
#else
// IF NO CMAKE BUILD-SET DEFINITIONS THEN SET AS NOTHING (FOR RELEASE BUILDS).
#    define MPE_ASSERT(x, ...)
#    define MPE_CORE_ASSERT(x, ...)
#endif