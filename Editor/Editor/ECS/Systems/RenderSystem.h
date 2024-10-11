#pragma once

#include "Editor/Editor/ECS/ECS.h"

#include "MPE/Renderer/Cameras/OrthographicCamera.h"

namespace MPE
{
namespace ECS
{
class MPE_EDITOR_API RenderSystem
{
  public:
    void operator()(entt::registry& registry, OrthographicCamera& camera) const;
};
}
}