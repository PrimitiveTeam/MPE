#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/ECS.h"

#include <bitset>

namespace MPE
{
namespace ECS
{
class MPE_API EntityManager
{
  public:
    EntityManager();
    ~EntityManager();

    Entity CreateEntity();
    void DestroyEntity(Entity entity);

  private:
    Entity m_nextEntityId = 0;
    std::bitset<MAX_COMPONENTS> m_signatures[MAX_ENTITIES];
    uint32_t m_livingEntityCount = 0;
};
}
}