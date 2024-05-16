#pragma once

// Run this only once from the EntryPoint.h to initialize all the core systems

#include "MPE/Core/_CORE.h"
#include "MPE/Core/_CWD.h"
#include "MPE/Log/GlobalLog.h"

#define MPE_STARTUP() MPE::STARTUP::Init()

namespace MPE
{
namespace STARTUP
{
/**
 * @brief Initializes the core systems.
 * @details This function initializes the core systems for the engine.
 * @date 2024-05-05
 * @note This function should be called at the start of the engine.
 */
static void Init()
{
    GlobalLog::Init();
    SET_EXECUTABLE_PATH_AS_CWD();
}
}
}