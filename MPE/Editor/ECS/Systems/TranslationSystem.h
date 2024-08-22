#pragma once

#include "MPE/Editor/ECS/ECS.h"
#include "MPE/Editor/ECS/Components/Core/TransformComponent.h"

namespace MPE
{
namespace ECS
{
class MPE_API TranslationSystem
{
  public:
    TranslationSystem(glm::vec3* deltaPosition);

    void operator()(entt::registry& registry, float deltaTime) const;

  private:
    glm::vec3* m_deltaPosition;
};
}
}