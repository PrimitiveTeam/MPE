#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Core/_PTRS.h"
#include "MPE/Time/Time.h"
#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Events/Event.h"
#include "Editor/Editor/Objects/Base/Object.h"
#include "Editor/Editor/Windows/PropertyViewer/Properties.h"
#include "Editor/Editor/Windows/PropertyViewer/ComponentProperties/IComponentPropertyEditor.h"

#include <functional>

namespace MPE
{
class MPE_EDITOR_API PropertyViewer
{
  public:
    // This is directly related to a scene, so we can simply provide a reference to the Ref<Object> vector that is kept in the scene
    PropertyViewer(ECS::ECS& ecs);
    ~PropertyViewer() = default;

    void OnUpdate(Time deltaTime);
    void OnRender(OrthographicCamera& camera);
    void OnImGuiRender();
    void OnEvent(Event& event);

    void SetEntity(ECS::Entity entity);
    void UnsetEntity();

  public:
    const bool EntityModified();

  private:
    void CheckEntity();

  private:
    ECS::ECS* m_ECS;
    ECS::Entity m_entity;
    Properties m_propertyFlags;
    std::vector<REF<IComponentPropertyEditor>> m_editors;
    bool m_entityModified = false;
};
}