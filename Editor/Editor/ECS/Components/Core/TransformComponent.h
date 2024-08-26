#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/ECS/ECS.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace MPE
{
namespace ECS
{
struct MPE_EDITOR_API TransformComponent
{
    glm::vec3 position{0.0f};
    glm::quat rotation{glm::vec3(0.0f)};
    glm::vec3 scale{1.0f};
};
}
}