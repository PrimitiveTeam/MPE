#include "Object.h"

#include "Editor/Editor/ECS/Components/Core/HierarchyComponent.h"
#include "Editor/Editor/Objects/Cameras/Camera.h"

namespace MPE
{
Object::Object(ECS::ECS& ecs)
    : m_ECS(ecs),
      m_entity{ecs.CreateEntity()},
      m_hierarchy{&ecs.AddComponentToEntity<ECS::HierarchyComponent>(m_entity, *this, *this)},
      m_tag{&ecs.AddComponentToEntity<ECS::TagComponent>(m_entity, "Object")}
{
    // MPE_CORE_INFO("Created entity with ID: {}", m_entity);
}

Object::~Object()
{
    // MPE_CORE_INFO("Destroyed entity with ID: {}", m_entity);
    m_ECS.DestroyEntity(m_entity);
}
}