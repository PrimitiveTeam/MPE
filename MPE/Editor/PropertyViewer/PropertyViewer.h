#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Core/_PTRS.h"
#include "MPE/Time/Time.h"
#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Events/Event.h"
#include "MPE/Editor/Objects/Base/Object.h"
#include "MPE/Editor/PropertyViewer/Properties.h"

#include <functional>

namespace MPE
{
class MPE_API PropertyViewer
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

  private:
    void CheckEntity();

  private:
    ECS::ECS* m_ECS;
    ECS::Entity m_entity;
    Properties m_propertyFlags;
};
}