#include "ObjectHierarchy.h"

#include "MPE/Editor/ECS/ECS.h"
// #include "MPE/Editor/Scene/Scene.h"
#include "MPE/Log/GlobalLog.h"

#include <fmt/format.h>

namespace MPE
{
ObjectHierarchy::ObjectHierarchy(const std::vector<REF<Object>>& objects) : m_objects(const_cast<std::vector<REF<Object>>&>(objects))
{
    UpdateHierarchyList();
}

void ObjectHierarchy::OnUpdate(Time deltaTime) {}

void ObjectHierarchy::OnRender(OrthographicCamera& camera) {}

void ObjectHierarchy::OnImGuiRender() {}

void ObjectHierarchy::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
}

void ObjectHierarchy::UpdateHierarchyList()
{
    m_objectList.clear();

    uint32_t count = 0;

    for (auto& object : m_objects)
    {
        // m_objectList += count object->GetTag().name "\n";
        m_objectList += fmt::format("({}) {} (ID: {})\n", count, object->GetTag().name, object->GetEntity());
        count++;
    }
}

}