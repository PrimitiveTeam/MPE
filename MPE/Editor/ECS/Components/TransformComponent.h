#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/ECS.h"

#include <glm/glm.hpp>

namespace MPE
{
namespace ECS
{
struct MPE_API TransformComponent
{
    glm::vec3 position{0.0f};
    glm::vec3 rotation{0.0f};
    glm::vec3 scale{1.0f};
};
}
}