#include "ObjectHierarchy.h"

#include "Editor/Editor/ECS/ECS.h"
// #include "MPE/Editor/Scene/Scene.h"
#include "MPE/Log/GlobalLog.h"
#include "Editor/Editor/Windows/PropertyViewer/PropertyViewer.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <imgui.h>

namespace MPE
{
ObjectHierarchy::ObjectHierarchy(const std::vector<REF<Object>>& objects) : m_objects(const_cast<std::vector<REF<Object>>&>(objects))
{
    UpdateHierarchyList();
}

void ObjectHierarchy::OnUpdate(Time deltaTime) {}

void ObjectHierarchy::OnRender(OrthographicCamera& camera) {}

void ObjectHierarchy::OnImGuiRender()
{
    for (const auto& [entity, name] : m_objectList)
    {
        std::string entityLabel = fmt::format("Entity {}: {}", entity, name);

        if (ImGui::Selectable(entityLabel.c_str()))
        {
            m_selectedEntity = entity;
        }
    }
}

void ObjectHierarchy::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
}

void ObjectHierarchy::UpdateHierarchyList()
{
    m_objectList.clear();

    for (auto& object : m_objects)
    {
        m_objectList[object->GetEntity()] = object->GetTag().name;
    }
}

}