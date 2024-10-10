#include "RenderPropertiesEditor.h"

#include <imgui.h>

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
RenderPropertiesEditor::RenderPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity)
    : m_ECS(ecs),
      m_entity(entity),
      m_renderComponent(ecs.GetComponent<ECS::RenderComponent>(entity)),
      m_vertexArray(m_renderComponent.vertexArray),
      m_shader(m_renderComponent.shader)
{
}

void RenderPropertiesEditor::Draw()
{
    ImGui::Text("Render Properties");
    // if (ImGui::ColorEdit4("Color", &m_color.r)) m_isModified = true;
    // Display only data for this component
    ImGui::Text("Shader: %s", m_shader->GetName().c_str());
    ImGui::Text("Vertex Array: %s", (m_vertexArray ? "Set" : "Not Set"));
}

bool RenderPropertiesEditor::IsModified() const
{
    return m_isModified;
}

void RenderPropertiesEditor::ApplyChanges()
{
    if (m_isModified) MPE_ASSERT(false, "Modifying render properties not implemented yet.");
}
}