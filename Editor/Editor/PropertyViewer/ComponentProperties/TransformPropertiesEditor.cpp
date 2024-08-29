#include "TransformPropertiesEditor.h"
#include "Editor/Editor/ECS/Utility/RotationUtilities.h"

#include <imgui.h>

namespace MPE
{
TransformPropertiesEditor::TransformPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity)
    : m_ECS(ecs),
      m_entity(entity),
      m_transform(ecs.GetComponent<ECS::TransformComponent>(entity)),
      m_position(m_transform.position),
      m_rotation(ECS::RotationUtilities::QuaternionToEuler(m_transform.rotation)),
      m_scale(m_transform.scale)
{
}

void TransformPropertiesEditor::Draw()
{
    ImGui::Text("Transform Properties");
    if (ImGui::DragFloat3("Position", &m_position.x, 0.1f)) m_isModified = true;
    if (ImGui::DragFloat3("Rotation", &m_rotation.x, 0.1f)) m_isModified = true;
    if (ImGui::DragFloat3("Scale", &m_scale.x, 0.1f)) m_isModified = true;
}

bool TransformPropertiesEditor::IsModified() const
{
    return m_isModified;
}

void TransformPropertiesEditor::ApplyChanges()
{
    if (m_isModified)
    {
        m_transform.position = m_position;
        m_transform.rotation = ECS::RotationUtilities::EulerToQuaternion(m_rotation);
        m_transform.scale = m_scale;
        // m_ECS.SetComponent<ECS::TransformComponent>(m_entity, m_transform);
        m_isModified = false;
    }
}
}