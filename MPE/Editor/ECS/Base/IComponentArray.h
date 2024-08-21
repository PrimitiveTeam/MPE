#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/ECS.h"

namespace MPE
{
namespace ECS
{
class MPE_API IComponentArray
{
  public:
    IComponentArray() = default;
    virtual ~IComponentArray() = default;
};
}
}