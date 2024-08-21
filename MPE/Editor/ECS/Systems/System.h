#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/ECS.h"

#include <set>

namespace MPE
{
namespace ECS
{
class MPE_API System
{
  public:
    System() = default;
    ~System() = default;

  public:
    std::set<Entity> m_entities;
};
}
}