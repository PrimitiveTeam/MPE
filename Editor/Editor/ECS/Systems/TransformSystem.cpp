#include "TransformSystem.h"

#include "MPE/Log/GlobalLog.h"
#include "Editor/Editor/ECS/Utility/RotationUtilities.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
namespace ECS
{
TransformSystem::TransformSystem(glm::vec3* deltaPosition, glm::vec3* deltaRotationEuler, glm::vec3* deltaScale)
    : m_deltaPosition(deltaPosition), m_deltaRotationEuler(deltaRotationEuler), m_deltaScale(deltaScale)
{
}

void TransformSystem::operator()(entt::registry& registry, float deltaTime) const
{
    auto view = registry.view<TransformComponent>();

    for (auto entity : view)
    {
        auto& transform = view.get<TransformComponent>(entity);

        if (m_deltaPosition)
        {
            transform.position += *m_deltaPosition * deltaTime;
        }

        if (m_deltaRotationEuler)
        {
            glm::quat deltaRotationQuat = RotationUtilities::EulerToQuaternion(*m_deltaRotationEuler * deltaTime);

            transform.rotation = deltaRotationQuat * transform.rotation;
            // Normalize the quaternion to prevent drift
            transform.rotation = glm::normalize(transform.rotation);
        }

        if (m_deltaScale)
        {
            transform.scale += *m_deltaScale * deltaTime;
        }

        // MPE_INFO("Entity {0} moved to {1}, rotated to {2}, scaled to {3}", static_cast<unsigned int>(entity), glm::to_string(transform.position),
        //          glm::to_string(transform.rotation), glm::to_string(transform.scale));
    }
}
}
}