#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/Components/Core/HierarchyComponent.h"
#include "MPE/Editor/ECS/ECS.h"

namespace MPE
{
class MPE_API HierarchyProperties
{
  public:
    static void DrawHierarchyProperties(ECS::ECS& ecs, ECS::Entity entity);
};
}