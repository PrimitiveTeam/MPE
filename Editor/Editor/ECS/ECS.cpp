#include "ECS.h"

#include "MPE/Log/GlobalLog.h"
#include "MPE/Profiling/_PROFILING.h"

namespace MPE
{
namespace ECS
{
Entity ECS::CreateEntity()
{
    return m_registry.create();
}

void ECS::DestroyEntity(Entity entity)
{
    m_registry.destroy(entity);
}

void ECS::RunSystems(float deltaTime)
{
    MPE_PROFILE_FUNCTION();

    for (auto& system : m_systems)
    {
        system(m_registry, deltaTime);
    }
}
}
}