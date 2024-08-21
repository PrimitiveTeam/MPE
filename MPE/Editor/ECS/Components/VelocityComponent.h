#pragma once

#include "MPE/Core/_CORE.h"

#include <glm/glm.hpp>

namespace MPE
{
namespace ECS
{
struct MPE_API VelocityComponent
{
    glm::vec3 velocity{0.0f};
};
}
}