// #if !defined(MPE_PLATFORM_OSX)
// #    define GLM_ENABLE_EXPERIMENTAL
// #endif

// #include <glm/glm.hpp>
// #include <glm/mat4x4.hpp>
// #include <glm/ext.hpp>

#include "TranslationSystem.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
namespace ECS
{
TranslationSystem::TranslationSystem(glm::vec3 deltaPosition) : m_deltaPosition(deltaPosition) {}

void TranslationSystem::operator()(entt::registry& registry) const
{
    auto view = registry.view<TransformComponent>();

    for (auto entity : view)
    {
        auto& transform = view.get<TransformComponent>(entity);
        transform.position += m_deltaPosition;
        // MPE_INFO("Entity {0} moved to {1}", (unsigned int) entity, glm::to_string(transform.position));
    }
}
}
}