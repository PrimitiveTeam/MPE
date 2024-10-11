#include "SphereMetadataPropertiesEditor.h"

#include <imgui.h>

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
SphereMetadataPropertiesEditor::SphereMetadataPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity)
    : m_ECS(ecs),
      m_entity(entity),
      m_metadata(ecs.GetComponent<ECS::SphereMetadataComponent>(entity)),
      m_radius(m_metadata.GetRadius()),
      m_sectors(m_metadata.GetSectors()),
      m_stacks(m_metadata.GetStacks()),
      m_smooth(m_metadata.GetSmooth()),
      m_upAxis(m_metadata.GetUpAxis())
{
}

void SphereMetadataPropertiesEditor::Draw()
{
    ImGui::Text("Sphere Properties");
    if (ImGui::SliderFloat("Radius", &m_radius, 0.1f, 10.0f))
    {
        m_isModified = true;
    }

    if (ImGui::SliderInt("Sectors", (int*) &m_sectors, ECS::MINIMUM_SECTORS, 100))
    {
        m_isModified = true;
    }

    if (ImGui::SliderInt("Stacks", (int*) &m_stacks, ECS::MINIMUM_STACKS, 100))
    {
        m_isModified = true;
    }

    if (ImGui::Checkbox("Smooth", &m_smooth))
    {
        m_isModified = true;
    }

    if (ImGui::Button("Toggle Up Axis"))
    {
        m_upAxis = (m_upAxis % 3) + 1;
        m_isModified = true;
    }

    if (ImGui::Button("Reverse Normals"))
    {
        m_isModified = true;
    }
}

bool SphereMetadataPropertiesEditor::IsModified() const
{
    return m_isModified;
}

void SphereMetadataPropertiesEditor::ApplyChanges()
{
    if (m_isModified)
    {
        m_metadata.SetRadius(m_radius);
        m_metadata.SetSectors(m_sectors);
        m_metadata.SetStacks(m_stacks);
        m_metadata.SetSmooth(m_smooth);
        m_metadata.SetUpAxis(m_upAxis);
        m_isModified = false;
    }
}
}