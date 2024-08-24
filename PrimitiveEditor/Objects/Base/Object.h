#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"
#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Events/Event.h"
#include "MPE/Editor/ECS/ECS.h"
#include "MPE/Editor/ECS/Components/Core/TagComponent.h"

namespace MPE
{
namespace ECS
{
struct HierarchyComponent;
}
class MPE_API Object
{
  public:
    Object(ECS::ECS& ecs);
    virtual ~Object();

  protected:
    // Force constructors to be less code intensive
    virtual void Init() = 0;

  public:
    virtual void OnUpdate(Time deltaTime) = 0;
    virtual void OnRender(OrthographicCamera& camera) = 0;
    virtual void OnImGuiRender() = 0;
    virtual void OnEvent(Event& event) = 0;

    ECS::Entity GetEntity() const { return m_entity; }
    ECS::HierarchyComponent& GetHierarchy() const { return *m_hierarchy; }
    ECS::TagComponent& GetTag() const { return *m_tag; }

  protected:
    ECS::ECS& m_ECS;
    ECS::Entity m_entity;
    ECS::HierarchyComponent* m_hierarchy;
    ECS::TagComponent* m_tag;
};
}