#pragma once

#include "Editor/Editor/ECS/ECS.h"

namespace MPE
{
class Camera;
namespace ECS
{
class MPE_EDITOR_API RenderSystem
{
  public:
    void operator()(entt::registry& registry, Camera& camera) const;
};
}
}