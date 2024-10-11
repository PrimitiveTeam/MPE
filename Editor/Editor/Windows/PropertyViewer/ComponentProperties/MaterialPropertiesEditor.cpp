#include "MaterialPropertiesEditor.h"

#include <imgui.h>

namespace MPE
{
MaterialPropertiesEditor::MaterialPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity)
    : m_ECS(ecs), m_entity(entity), m_material(ecs.GetComponent<ECS::MaterialComponent>(entity)), m_color(m_material.color)
{
}

void MaterialPropertiesEditor::Draw()
{
    ImGui::Text("Material Properties");
    if (ImGui::ColorEdit4("Color", &m_color.r)) m_isModified = true;
}

bool MaterialPropertiesEditor::IsModified() const
{
    return m_isModified;
}

void MaterialPropertiesEditor::ApplyChanges()
{
    if (m_isModified)
    {
        m_material.color = m_color;
        m_isModified = false;
    }
}
}