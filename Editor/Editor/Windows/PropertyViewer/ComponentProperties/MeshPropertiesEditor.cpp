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
      m_meshType(m_mesh.meshType),
      m_lineDrawing(m_mesh.lineDrawing)
{
}

void MeshPropertiesEditor::Draw()
{
    ImGui::Text("Mesh Properties");
    // Display only data for this component
    ImGui::Text("Mesh Type: %s", MeshTypeToString(m_meshType).c_str());
    ImGui::Text("Vertices: %d", m_vertices.size());
    ImGui::Text("Normals: %d", m_normals.size());
    ImGui::Text("Texture Coords: %d", m_textureCoords.size());
    ImGui::Text("Indices: %d", m_indices.size());
    ImGui::Text("Stride: %d", m_stride);
    if (ImGui::Checkbox("Line Drawing", &m_lineDrawing))
    {
        m_isModified = true;
    }
}

bool MeshPropertiesEditor::IsModified() const
{
    return m_isModified;
}

void MeshPropertiesEditor::ApplyChanges()
{
    if (m_isModified)
    {
        m_mesh.lineDrawing = m_lineDrawing;
        m_isModified = false;
    }
}
}