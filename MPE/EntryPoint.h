#pragma once

/**
 * @file EntryPoint.h
 * @brief Entry point for the MPE engine.
 * @details This file is used to define the entry point for the MPE engine.
 * @date 2024-05-05
 * @author Sebastian Termen
 */

#ifdef MPE_PLATFORM_WINDOWS

#    include "MPE/App/App.h"
#    include "MPE/Core/_INIT.h"

/**
 * @brief Create a new MPE application.
 * @details This function is used to create a new MPE application.
 * @return A reference to the new MPE application.
 * @see MPE::App
 */
extern MPE::REF<MPE::App> MPE::CreateApp();

/**
 * @brief Entry point for the MPE engine.
 * @details This function is the entry point for the MPE engine.
 * @param argc The number of arguments.
 * @param argv The arguments.
 * @return The exit code.
 */
int main(int argc, char **argv)
{
    MPE_STARTUP();

    // Print out argc and argv
    for (int i = 0; i < argc; i++)
    {
        MPE_CORE_TRACE("Argv[{0}]: {1}", i, argv[i]);
    }

    // MPE_PROFILE_START("STARTUP", "MPE-PROFILE-STARTUP.json");
    auto app = MPE::CreateApp();
    // MPE_PROFILE_END();
    // MPE_PROFILE_START("RUNTIME", "MPE-PROFILE-RUNTIME.json");
    app->Run();
    // MPE_PROFILE_END();

    return 0;
}

#elif MPE_PLATFORM_LINUX

#    include "MPE/App/App.h"
#    include "MPE/Core/_INIT.h"

/**
 * @brief Create a new MPE application.
 * @details This function is used to create a new MPE application.
 * @return A reference to the new MPE application.
 * @see MPE::App
 */
extern MPE::REF<MPE::App> MPE::CreateApp();

/**
 * @brief Entry point for the MPE engine.
 * @details This function is the entry point for the MPE engine.
 * @param argc The number of arguments.
 * @param argv The arguments.
 * @return The exit code.
 */
int main(int argc, char **argv)
{
    MPE_STARTUP();

    // Print out argc and argv
    for (int i = 0; i < argc; i++)
    {
        MPE_CORE_TRACE("Argv[{0}]: {1}", i, argv[i]);
    }

    // MPE_PROFILE_START("STARTUP", "MPE-PROFILE-STARTUP.json");
    auto app = MPE::CreateApp();
    // MPE_PROFILE_END();
    // MPE_PROFILE_START("RUNTIME", "MPE-PROFILE-RUNTIME.json");
    app->Run();
    // MPE_PROFILE_END();
}

#elif MPE_PLATFORM_OSX

#    include "MPE/App/App.h"
#    include "MPE/Core/_INIT.h"

/**
 * @brief Create a new MPE application.
 * @details This function is used to create a new MPE application.
 * @return A reference to the new MPE application.
 * @see MPE::App
 */
extern MPE::REF<MPE::App> MPE::CreateApp();

/**
 * @brief Entry point for the MPE engine.
 * @details This function is the entry point for the MPE engine.
 * @param argc The number of arguments.
 * @param argv The arguments.
 * @return The exit code.
 */
int main(int argc, char **argv)
{
    MPE_STARTUP();

    // Print out argc and argv
    for (int i = 0; i < argc; i++)
    {
        MPE_CORE_TRACE("Argv[{0}]: {1}", i, argv[i]);
    }

    // MPE_PROFILE_START("STARTUP", "MPE-PROFILE-STARTUP.json");
    auto app = MPE::CreateApp();
    // MPE_PROFILE_END();
    // MPE_PROFILE_START("RUNTIME", "MPE-PROFILE-RUNTIME.json");
    app->Run();
    // MPE_PROFILE_END();
}

#else

#    error No entrypoint defined for this platform.

#endif