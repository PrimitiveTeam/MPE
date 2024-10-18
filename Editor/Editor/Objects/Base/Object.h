#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"
#include "MPE/Events/Event.h"
#include "Editor/Editor/ECS/ECS.h"
#include "Editor/Editor/ECS/Components/Core/TagComponent.h"

namespace MPE
{
class Camera;
namespace ECS
{
struct HierarchyComponent;
}
class MPE_EDITOR_API Object
{
  public:
    Object(ECS::ECS& ecs);
    virtual ~Object();

  protected:
    // Force constructors to be less code intensive
    virtual void Init() {}

  public:
    virtual void OnUpdate(Time deltaTime) = 0;
    virtual void OnRender(Camera& camera) = 0;
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