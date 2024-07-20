#pragma once

#include "MPE/Core/_CORE.h"

namespace MPE
{
class MPE_API GraphicalContext
{
  public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
};
}