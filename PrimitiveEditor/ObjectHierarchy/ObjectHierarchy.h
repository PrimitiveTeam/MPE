#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Core/_PTRS.h"
#include "MPE/Time/Time.h"
#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Events/Event.h"
#include "MPE/Editor/Objects/Base/Object.h"

#include <functional>
#include <unordered_map>

namespace MPE
{
class PropertyViewer;

class MPE_API ObjectHierarchy
{
  public:
    // This is directly related to a scene, so we can simply provide a reference to the Ref<Object> vector that is kept in the scene
    ObjectHierarchy(const std::vector<REF<Object>>& objects);
    ~ObjectHierarchy() = default;

    void OnUpdate(Time deltaTime);
    void OnRender(OrthographicCamera& camera);
    void OnImGuiRender();
    void OnEvent(Event& event);

  public:
    const std::unordered_map<ECS::Entity, std::string>& GetObjectList() const { return m_objectList; }
    ECS::Entity GetSelectedEntity() const { return m_selectedEntity; }

    void UpdateHierarchyList();

  private:
    std::vector<REF<Object>>& m_objects;
    std::unordered_map<ECS::Entity, std::string> m_objectList;
    ECS::Entity m_selectedEntity = entt::null;
};
}