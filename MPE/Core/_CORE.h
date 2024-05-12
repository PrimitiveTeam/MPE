#pragma once

#include <memory>

/**
 * @file _CORE.h
 * @brief The Mere Primitive Engine (MPE) namespace.
 * @date 2024-05-05
 * @author Sebastian Termen
 * @brief Main header file for the MPE engine.
 * @details This file contains the main header file for the MPE engine. It includes all the necessary headers and defines the main macros for the engine.
 * @date 2024-05-05
 */

/**
 * @def MPE_ASSERT(x, ...)
 * @brief Assertion macro for the MPE engine.
 * @details This macro is used to assert a condition and log an error message if the condition is false.
 * for Windows we use __debugbreak() from MSVC intrinsics (intrin.h) to break into the debugger.
 * @date 2024-05-05
 * @param x The condition to assert.
 * @param ... The error message to log if the condition is false.
 * @note This macro is only available in debug builds.
 */

/**
 * @def MPE_CORE_ASSERT(x, ...)
 * @brief Assertion macro for the MPE engine.
 * @details This macro is used to assert a condition and log an error message if the condition is false.
 * for Windows we use __debugbreak() from MSVC intrinsics (intrin.h) to break into the debugger.
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
#ifdef MPE_STATIC_LIBRARY
#define MPE_API
#endif
// IF A DYNAMIC LIBRARY IS USED THEN DEFINE MPE_API WITHIN MPE AS DLL EXPORT AND MPE_API WITHIN SANDBOX AS DLL IMPORT
#ifdef MPE_DYNAMIC_LIB
#ifdef MPE_BUILD_DLL
// #pragma message("Building DLL")
// #pragma warning(disable : 4005)
#define MPE_API __declspec(dllexport)
#else
// #pragma message("Using Dynamic Lib")
#define MPE_API __declspec(dllimport)
#endif
#else
// DYNAMIC LIBRARY IS NOT SUPPORTED BY THIS PROJECT, BUT CAN STILL BE ENABLED
#pragma message("DYNAMIC LIBRARY IS NOT INTENDED TO BE USED WITH THIS PROJECT AT THE MOMENT.")
#define MPE_API
#endif

#elif MPE_PLATFORM_LINUX

#ifdef MPE_STATIC_LIBRARY
// define as nothing
#define MPE_API
#endif

#ifdef MPE_DYNAMIC_LIB

#ifdef MPE_BUILD_DLL
#error "Building DLL is not supported on Linux"
#define MPE_API __attribute__((visibility("default")))
#else
#error "Using Dynamic Lib is not supported on Linux"
#endif

#endif

#endif

#ifdef MPE_PLATFORM_OSX

#ifdef MPE_STATIC_LIBRARY
// define as nothing
#define MPE_API
#endif

#ifdef MPE_DYNAMIC_LIB

#ifdef MPE_BUILD_DLL
#error "Building DLL is not supported on Linux"
#define MPE_API __attribute__((visibility("default")))
#else
#error "Using Dynamic Lib is not supported on Linux"
#endif

#endif

#else
#error "MPE only supports Windows, Linux and OSX."

#endif

// CMAKE BUILD-SET DEFINITIONS:
// MPE ASSERTIONS
#ifdef MPE_ENABLE_ASSERTS
// LOGGING ASSERTIONS FOR DEBUG BUILDS
#ifdef MPE_PLATFORM_WINDOWS
// WINDOWS ONLY SOLUTION FOR ASSERTIONS

#define MPE_ASSERT(x, ...)                                   \
	{                                                        \
		if (!(x))                                            \
		{                                                    \
			MPE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
			__debugbreak();                                  \
		}                                                    \
	}
#define MPE_CORE_ASSERT(x, ...)                                   \
	{                                                             \
		if (!(x))                                                 \
		{                                                         \
			MPE_CORE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
			__debugbreak();                                       \
		}                                                         \
	}
#elif MPE_PLATFORM_LINUX or MPE_PLATFORM_OSX
// LINUX ONLY SOLUTION FOR ASSERTIONS
// we should also try to use this if possible defined(SIGTRAP) (i.e., POSIX), raise(SIGTRAP)
#include <signal.h>

#ifdef SIGTRAP
#define MPE_ASSERT(x, ...)                                   \
	{                                                        \
		if (!(x))                                            \
		{                                                    \
			MPE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
			raise(SIGTRAP);                                  \
		}                                                    \
	}
#define MPE_CORE_ASSERT(x, ...)                                   \
	{                                                             \
		if (!(x))                                                 \
		{                                                         \
			MPE_CORE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
			raise(SIGTRAP);                                       \
		}                                                         \
	}

#else

#define MPE_ASSERT(x, ...)                                   \
	{                                                        \
		if (!(x))                                            \
		{                                                    \
			MPE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
			__builtin_trap();                                \
		}                                                    \
	}
#define MPE_CORE_ASSERT(x, ...)                                   \
	{                                                             \
		if (!(x))                                                 \
		{                                                         \
			MPE_CORE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
			__builtin_trap();                                     \
		}                                                         \
	}

#endif
#endif
#else
// IF NO CMAKE BUILD-SET DEFINITIONS THEN SET AS NOTHING (FOR RELEASE BUILDS).
#define MPE_ASSERT(x, ...)
#define MPE_CORE_ASSERT(x, ...)
#endif

// HEADER SET DEFINITIONS:

// RIGHT SHIFT OPERATION FOR EVENT ENUMS
#define BIT(x) (1 << x)

// OPENGL DEFINITIONS:
#define OPENGL_SHADER_TYPE_AMOUNT 2

// BIND FUNCTIONS FOR EVENTS
#ifdef MPE_COMPILER_MSVC
#define MPE_BIND_EVENT_FUNCTION(func) std::bind(&func, this, std::placeholders::_1)
#elif MPE_COMPILER_CLANG or MPE_COMPILER_GNU or MPE_COMPILER_APPLECLANG
#define MPE_BIND_EVENT_FUNCTION(func) [this](auto &&...args) -> decltype(auto) { return this->func(std::forward<decltype(args)>(args)...); }
#endif

/**
 * @brief The Mere Primitive Engine (MPE) namespace.
 * @date 2024-05-05
 * @author Sebastian Termen
 */
namespace MPE
{
	/**
	 * @brief Alias template for std::unique_ptr to manage the lifecycle of individual objects.
	 * @details SCOPE automatically deletes the object it points to when the SCOPE variable goes out of scope.
	 * @date 2024-05-05
	 * @author Sebastian Termen
	 */
	template <typename T>
	using SCOPE = std::unique_ptr<T>;

	/**
	 * @brief Factory function to create a SCOPE smart pointer instance.
	 * @details This function simplifies the creation of unique_ptr instances with automatic type deduction and argument forwarding.
	 * @date 2024-05-05
	 * @author Sebastian Termen
	 */
	template <typename T, typename... Args>
	constexpr SCOPE<T> NEWSCOPE(Args &&...args)
	{
		/**
		 * @brief std::make_unique is used to construct an object and wrap it in a std::unique_ptr (SCOPE).
		 * @details It provides exception safety by ensuring that memory allocation and object construction are atomic operations.
		 * @see https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
		 */
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	/**
	 * @brief Alias template for std::shared_ptr to manage shared ownership of objects.
	 * @details REF allows multiple pointers to the same object, with the object being destroyed once the last REF is destroyed or reset.
	 * @date 2024-05-05
	 * @author Sebastian Termen
	 */
	template <typename T>
	using REF = std::shared_ptr<T>;

	/**
	 * @brief Factory function to create a REF smart pointer instance.
	 * @details This function simplifies the creation of shared_ptr instances with automatic type deduction and argument forwarding.
	 * @date 2024-05-05
	 * @author Sebastian Termen
	 */
	template <typename T, typename... Args>
	constexpr REF<T> NEWREF(Args &&...args)
	{
		/**
		 * @brief std::make_shared is used to construct an object and wrap it in a std::shared_ptr (REF).
		 * @details It is more efficient than using std::shared_ptr directly as it allocates memory for the object
		 * and the control block in a single memory block.
		 * @see https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared
		 */
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}