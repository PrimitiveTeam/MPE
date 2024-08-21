#include "TranslationSystem.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
namespace ECS
{
TranslationSystem::TranslationSystem(glm::vec3& deltaPosition) : m_deltaPosition(deltaPosition) {}

void TranslationSystem::operator()(entt::registry& registry) const
{
    auto view = registry.view<TransformComponent>();

    for (auto entity : view)
    {
        auto& transform = view.get<TransformComponent>(entity);
        transform.position += m_deltaPosition;
    }
}
}
}