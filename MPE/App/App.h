#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Log/Log.h"

namespace MPE
{
	class MPE_API App
	{
	public:
		App();
		virtual ~App();

		virtual void Run() {};

		inline void Shutdown() { SYS_Running = false; }

	private:
		bool SYS_Running = true;
		REF<MPE::Log> SYS_Log;
	};

	App *CreateApp();
}