#pragma once

#include "MPE/Editor/ECS/ECS.h"
#include "MPE/Editor/ECS/Components/Core/TransformComponent.h"

namespace MPE
{
namespace ECS
{
class MPE_API TransformSystem
{
  public:
    TransformSystem(glm::vec3* deltaPosition, glm::vec3* deltaRotationEuler = nullptr, glm::vec3* deltaScale = nullptr);

    void operator()(entt::registry& registry, float deltaTime) const;

  private:
    glm::vec3* m_deltaPosition;
    glm::vec3* m_deltaRotationEuler;
    glm::vec3* m_deltaScale;
};
}
}