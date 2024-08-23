#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"
#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Editor/ECS/ECS.h"
#include "MPE/Editor/ECS/Components/Core/TagComponent.h"

namespace MPE
{
class MPE_API Object
{
  public:
    Object(ECS::ECS& ecs);
    virtual ~Object() = default;

    virtual void OnUpdate(Time deltaTime) = 0;
    virtual void OnRender(OrthographicCamera& camera) = 0;
    virtual void OnImGuiRender() = 0;

    ECS::Entity GetEntity() const { return m_entity; }
    ECS::TagComponent& GetTag() const { return *m_tag; }

  protected:
    ECS::ECS& m_ECS;
    ECS::Entity m_entity;
    ECS::TagComponent* m_tag;
};
}