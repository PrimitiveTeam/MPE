#include "TagPropertiesEditor.h"

#include <imgui.h>

namespace MPE
{
TagPropertiesEditor::TagPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity) : m_ECS(ecs), m_entity(entity), m_tag(ecs.GetComponent<ECS::TagComponent>(entity))
{
}

void TagPropertiesEditor::Draw()
{
    ImGui::Text("Tag Properties");

    char nameBuffer[256];
    memset(nameBuffer, 0, sizeof(nameBuffer));
    strcpy(nameBuffer, m_tag.name.c_str());

    if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer)))
    {
        m_name = std::string(nameBuffer);
        m_isModified = true;
    }

    ImGui::Text("Tag");

    char tagBuffer[256];
    memset(tagBuffer, 0, sizeof(tagBuffer));
    strcpy(tagBuffer, m_tag.tag.c_str());

    if (ImGui::InputText("Tag", tagBuffer, sizeof(tagBuffer)))
    {
        m_tagName = std::string(tagBuffer);
        m_isModified = true;
    }
}

bool TagPropertiesEditor::IsModified() const
{
    return m_isModified;
}

void TagPropertiesEditor::ApplyChanges()
{
    if (m_isModified)
    {
        m_tag.name = m_name;
        m_tag.tag = m_tagName;
        m_isModified = false;
    }
}
}