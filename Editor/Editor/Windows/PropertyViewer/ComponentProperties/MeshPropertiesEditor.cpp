#include "MeshPropertiesEditor.h"

#include <imgui.h>

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
MeshPropertiesEditor::MeshPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity)
    : m_ECS(ecs),
      m_entity(entity),
      m_mesh(ecs.GetComponent<ECS::MeshComponent>(entity)),
      m_vertices(m_mesh.vertices),
      m_normals(m_mesh.normals),
      m_textureCoords(m_mesh.textureCoords),
      m_indices(m_mesh.indices),
      m_stride(m_mesh.stride),
      m_meshType(m_mesh.meshType)
{
}

void MeshPropertiesEditor::Draw()
{
    ImGui::Text("Mesh Properties");
    // if (ImGui::ColorEdit4("Color", &m_color.r)) m_isModified = true;
    // Display only data for this component
    ImGui::Text("Mesh Type: %s", MeshTypeToString(m_meshType).c_str());
    ImGui::Text("Vertices: %d", m_vertices.size());
    ImGui::Text("Normals: %d", m_normals.size());
    ImGui::Text("Texture Coords: %d", m_textureCoords.size());
    ImGui::Text("Indices: %d", m_indices.size());
    ImGui::Text("Stride: %d", m_stride);
}

bool MeshPropertiesEditor::IsModified() const
{
    return m_isModified;
}

void MeshPropertiesEditor::ApplyChanges()
{
    if (m_isModified) MPE_ASSERT(false, "Modifying mesh properties not implemented yet.");
}
}