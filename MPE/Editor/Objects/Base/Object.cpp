#include "Object.h"

namespace MPE
{
Object::Object(ECS::ECS& ecs) : m_ECS(ecs), m_entity{ecs.CreateEntity()}, m_tag{&ecs.AddComponentToEntity<ECS::TagComponent>(m_entity, "Object")} {}
}