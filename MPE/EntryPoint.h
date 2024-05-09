#pragma once

#ifdef MPE_PLATFORM_WINDOWS

#include "MPE/Core/_CWD.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/App/App.h"

// Create reference to the CreateApp function
extern MPE::REF<MPE::App> MPE::CreateApp();

int main(int argc, char **argv)
{
	MPE::GlobalLog::Init();
	SET_EXECUTABLE_PATH_AS_CWD();

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
#error No entrypoint defined for this platform.

#endif