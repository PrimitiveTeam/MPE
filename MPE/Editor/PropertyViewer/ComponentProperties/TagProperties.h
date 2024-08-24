#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/Components/Core/TagComponent.h"
#include "MPE/Editor/ECS/ECS.h"

namespace MPE
{
class MPE_API TagProperties
{
  public:
    static void DrawTagProperties(ECS::ECS& ecs, ECS::Entity entity);
};
}