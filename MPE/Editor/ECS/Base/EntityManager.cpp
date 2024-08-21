#include "EntityManager.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
namespace ECS
{
EntityManager::EntityManager() {}

EntityManager::~EntityManager() {}

Entity EntityManager::CreateEntity()
{
    MPE_ASSERT(m_livingEntityCount < MAX_ENTITIES, "Too many entities exist");

    Entity id = m_nextEntityId++;
    m_livingEntityCount++;

    return id;
}

void EntityManager::DestroyEntity(Entity entity)
{
    MPE_ASSERT(entity < MAX_ENTITIES, "Entity out of range");

    m_signatures[entity].reset();
    m_livingEntityCount--;
}
}
}