#include "ECS.h"

#include "MPE/Log/GlobalLog.h"
#include "MPE/Profiling/_PROFILING.h"
#include "Editor/Editor/Objects/Cameras/Camera.h"

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
    for (auto& system : m_deltaTimeSystems)
    {
        system(m_registry, deltaTime);
    }
}

void ECS::RunSystems(Camera& camera)
{
    for (auto& system : m_cameraSystems)
    {
        system(m_registry, camera);
    }
}

void ECS::RunSystems(REF<Camera> camera)
{
    for (auto& system : m_cameraSystems)
    {
        system(m_registry, *camera);
    }
}
}
}