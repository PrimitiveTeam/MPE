#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Log/Log.h"

/**
 * @file App.h
 * @brief App class for the MPE engine.
 * @date 2024-05-05
 * @author Sebastian Termen
 */

namespace MPE
{
/**
 * @brief App class for the MPE engine.
 * @details This class is used to define the application for the MPE engine.
 * @date 2024-05-05
 * @see EntryPoint.h
 */
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

static REF<App> CreateApp();
}