#pragma once

/**
 * @file _CORE.h
 * @brief The Mere Primitive Engine (MPE) namespace.
 * @date 2024-05-05
 * @author Sebastian Termen
 * @brief Main header file for the MPE engine.
 * @details This file contains the main header file for the MPE engine. It
 * includes all the necessary headers and defines the main macros for the
 * engine.
 * @date 2024-05-05
 */

/**
 * @def MPE_ASSERT(x, ...)
 * @brief Assertion macro for the MPE engine.
 * @details This macro is used to assert a condition and log an error message if
 * the condition is false. for Windows we use __debugbreak() from MSVC
 * intrinsics (intrin.h) to break into the debugger.
 * @date 2024-05-05
 * @param x The condition to assert.
 * @param ... The error message to log if the condition is false.
 * @note This macro is only available in debug builds.
 */

/**
 * @def MPE_CORE_ASSERT(x, ...)
 * @brief Assertion macro for the MPE engine.
 * @details This macro is used to assert a condition and log an error message if
 * the condition is false. for Windows we use __debugbreak() from MSVC
 * intrinsics (intrin.h) to break into the debugger.
 * @date 2024-05-05
 * @param x The condition to assert.
 * @param ... The error message to log if the condition is false.
 * @note This macro is persistent in all builds.
 */

/**
 * @def MPE_BIND_EVENT_FUNCTION(func)
 * @brief Binding macro for event functions.
 * @details This macro is used to bind an event function to a class instance.
 * @date 2024-05-05
 * @param func The event function to bind.
 * @note This macro is used in the Event class.
 */

/**
 * @def BIT(x)
 * @brief Bit shift macro for event enums.
 * @details This macro is used to shift a bit to the left by x amount.
 * @date 2024-05-05
 * @param x The amount to shift the bit.
 * @note This macro is used in the Event class.
 */

/**
 * @def OPENGL_SHADER_TYPE_AMOUNT
 * @brief Amount of shader types in OpenGL.
 * @details This macro is used to define the amount of shader types in OpenGL.
 * @date 2024-05-05
 * @note This macro is used in the OpenGLShader class.
 */

// COMPILER PREPROCESSOR DIRECTIVES
// CMAKE BUILD-SET DEFINITIONS:
// CHECKS IF SYSTEM IS ON WIDOWS
#ifdef MPE_PLATFORM_WINDOWS
// IF A STATIC LIBRARY IS USED THEN DEFINE MPE_API AS NOTHING
#    ifdef MPE_STATIC_LIBRARY
// #        pragma message("MPE_STATIC_LIBRARY - DEFINED")
#        define MPE_API
#    endif
// IF A DYNAMIC LIBRARY IS USED THEN DEFINE MPE_API WITHIN MPE AS DLL EXPORT AND
// MPE_API WITHIN SANDBOX AS DLL IMPORT
#    ifdef MPE_DYNAMIC_LIBRARY
#        ifdef MPE_BUILD_DLL
// #pragma message("Building DLL")
// #pragma warning(disable : 4005)
#            define MPE_API __declspec(dllexport)
#        else
// #pragma message("Using Dynamic Lib")
#            define MPE_API __declspec(dllimport)
// #            pragma message("DYNAMIC LIBRARY IS NOT INTENDED TO BE USED WITH THIS PROJECT AT THE MOMENT.")
#        endif
#    else
// DYNAMIC LIBRARY IS NOT SUPPORTED BY THIS PROJECT, BUT CAN STILL BE ENABLED
#        define MPE_API
#    endif

#elif MPE_PLATFORM_LINUX

#    ifdef MPE_STATIC_LIBRARY
// define as nothing
#        define MPE_API
#    endif

#    ifdef MPE_DYNAMIC_LIBRARY

#        ifdef MPE_BUILD_DLL
// #            warning "Building DLL is not supported on Linux"
#            define MPE_API __attribute__((visibility("default")))
#        else
#            define MPE_API
// #            warning "Using Dynamic Libraries is not supported on Linux"
#        endif

#    endif

#elif MPE_PLATFORM_OSX

#    ifdef MPE_STATIC_LIBRARY
// define as nothing
#        define MPE_API
#    endif

#    ifdef MPE_DYNAMIC_LIBRARY

#        ifdef MPE_BUILD_DLL
// #            warning "Building DLL is not supported on OSX"
#            define MPE_API __attribute__((visibility("default")))
#        else
#            define MPE_API
// #            warning "Using Dynamic Libraries is not supported on OSX"
#        endif

#    endif

#else
#    error "MPE only supports Windows, Linux and OSX."

#endif

// HEADER SET DEFINITIONS:

// RIGHT SHIFT OPERATION FOR EVENT ENUMS
#define BIT(x) (1 << x)

// OPENGL DEFINITIONS:
#define OPENGL_SHADER_TYPE_AMOUNT 2

// BIND FUNCTIONS FOR EVENTS
#ifdef MPE_COMPILER_MSVC
#    define MPE_BIND_EVENT_FUNCTION(func) std::bind(&func, this, std::placeholders::_1)
#elif MPE_COMPILER_CLANG or MPE_COMPILER_GNU or MPE_COMPILER_APPLECLANG
#    define MPE_BIND_EVENT_FUNCTION(func) [this](auto &&...args) -> decltype(auto) { return this->func(std::forward<decltype(args)>(args)...); }
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define MPE_VERSION TOSTRING(MPE_FULL_VERSION)