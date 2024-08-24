#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/Components/Core/TransformComponent.h"
#include "MPE/Editor/ECS/ECS.h"

#include <glm/glm.hpp>

namespace MPE
{
class MPE_API TransformProperties
{
  public:
    static void DrawTransformProperties(ECS::ECS& ecs, ECS::Entity entity);
};
}