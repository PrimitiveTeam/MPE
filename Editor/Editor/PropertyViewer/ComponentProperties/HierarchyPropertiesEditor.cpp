#include "HierarchyPropertiesEditor.h"

#include "MPE/Log/GlobalLog.h"

#include <imgui.h>

namespace MPE
{
HierarchyPropertiesEditor::HierarchyPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity)
    : m_ECS(ecs), m_entity(entity), m_hierarchy(ecs.GetComponent<ECS::HierarchyComponent>(entity))
{
}

void HierarchyPropertiesEditor::Draw()
{
    ImGui::Text("Hierarchy Properties");

    ImGui::Text("Parent: %s", m_hierarchy.parent.GetTag().name.c_str());
    ImGui::Text("Children: %s", m_hierarchy.child.GetTag().name.c_str());
}

bool HierarchyPropertiesEditor::IsModified() const
{
    return m_isModified;
}

void HierarchyPropertiesEditor::ApplyChanges()
{
    if (m_isModified)
    {
        MPE_CORE_WARN("Hierarchy Component Modified. This is not supported yet!");
        MPE_CORE_ASSERT(false, "Hierarchy Component Modified. This is not supported yet!");
        // m_hierarchy.parent = m_parent;
        // m_hierarchy.child = m_child;
        // m_isModified = false;
    }
}
}