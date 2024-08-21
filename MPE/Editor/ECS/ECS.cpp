#include "ECS.h"

#include "MPE/Log/GlobalLog.h"

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

void ECS::RunSystems()
{
    // MPE_INFO("Running systems...");

    for (auto& system : m_systems)
    {
        system(m_registry);
    }
}
}
}