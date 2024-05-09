#include "App.h"
#include "MPE/MPEPCH.h"

namespace MPE
{
	App::App()
	{
		SYS_Log = MPE::Log::Create("App", MPE::Log::Option::CONSOLE);
	}

	App::~App() {}

	// void App::Run()
	// {
	// 	while (SYS_Running)
	// 	{
	// 		SYS_Log->info("Running...");
	// 		std::this_thread::sleep_for(std::chrono::seconds(1));
	// 		Shutdown();
	// 	}
	// }
}