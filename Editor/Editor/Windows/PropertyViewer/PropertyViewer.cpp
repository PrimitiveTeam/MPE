#include "PropertyViewer.h"

#include "Editor/Editor/ECS/ECS.h"
#include "Editor/Editor/Objects/Cameras/Camera.h"
#include "MPE/Log/GlobalLog.h"
// Properties
#include "Editor/Editor/Windows/PropertyViewer/ComponentProperties/HierarchyPropertiesEditor.h"
#include "Editor/Editor/Windows/PropertyViewer/ComponentProperties/TagPropertiesEditor.h"
#include "Editor/Editor/Windows/PropertyViewer/ComponentProperties/TransformPropertiesEditor.h"
#include "Editor/Editor/Windows/PropertyViewer/ComponentProperties/MeshPropertiesEditor.h"
#include "Editor/Editor/Windows/PropertyViewer/ComponentProperties/SphereMetadataPropertiesEditor.h"
#include "Editor/Editor/Windows/PropertyViewer/ComponentProperties/MaterialPropertiesEditor.h"
#include "Editor/Editor/Windows/PropertyViewer/ComponentProperties/RenderPropertiesEditor.h"

#include <imgui.h>

namespace MPE
{
PropertyViewer::PropertyViewer(ECS::ECS& ecs) : m_ECS(&ecs), m_entity(entt::null), m_propertyFlags(Properties::None) {}

void PropertyViewer::OnUpdate(Time deltaTime) {}
void PropertyViewer::OnRender(Camera& camera) {}
void PropertyViewer::OnImGuiRender()
{
    if (m_entity == entt::null)
    {
        return;
    }

    ImGui::Begin("Properties");
    for (const auto& editor : m_editors)
    {
        editor->Draw();
        if (editor->IsModified())
        {
            editor->ApplyChanges();
            m_entityModified = true;
        }
        ImGui::Separator();
    }
    ImGui::End();
}
void PropertyViewer::OnEvent(Event& event) {}

void PropertyViewer::SetEntity(ECS::Entity entity)
{
    m_entity = entity;
    CheckEntity();
}
void PropertyViewer::UnsetEntity()
{
    m_entity = entt::null;
    CheckEntity();
}

void PropertyViewer::CheckEntity()
{
    m_propertyFlags = Properties::None;
    m_editors.clear();

    if (m_entity == entt::null)
    {
        return;
    }

    // Add flags based on what components the entity has and add corresponding editors
    if (m_ECS->HasComponent<ECS::HierarchyComponent>(m_entity))
    {
        m_propertyFlags |= Properties::Hierarchy;
        m_editors.push_back(NEWREF<HierarchyPropertiesEditor>(*m_ECS, m_entity));
    }
    if (m_ECS->HasComponent<ECS::TagComponent>(m_entity))
    {
        m_propertyFlags |= Properties::Tag;
        m_editors.push_back(NEWREF<TagPropertiesEditor>(*m_ECS, m_entity));
    }
    if (m_ECS->HasComponent<ECS::TransformComponent>(m_entity))
    {
        m_propertyFlags |= Properties::Transform;
        m_editors.push_back(NEWREF<TransformPropertiesEditor>(*m_ECS, m_entity));
    }
    if (m_ECS->HasComponent<ECS::MeshComponent>(m_entity))
    {
        m_propertyFlags |= Properties::Mesh;
        m_editors.push_back(NEWREF<MeshPropertiesEditor>(*m_ECS, m_entity));
    }
    if (m_ECS->HasComponent<ECS::SphereMetadataComponent>(m_entity))
    {
        m_propertyFlags |= Properties::SphereMetadata;
        m_editors.push_back(NEWREF<SphereMetadataPropertiesEditor>(*m_ECS, m_entity));
    }
    if (m_ECS->HasComponent<ECS::MaterialComponent>(m_entity))
    {
        m_propertyFlags |= Properties::Material;
        m_editors.push_back(NEWREF<MaterialPropertiesEditor>(*m_ECS, m_entity));
    }
    if (m_ECS->HasComponent<ECS::RenderComponent>(m_entity))
    {
        m_propertyFlags |= Properties::Render;
        m_editors.push_back(NEWREF<RenderPropertiesEditor>(*m_ECS, m_entity));
    }
    if (m_entity == entt::null)
    {
        m_propertyFlags = Properties::None;
        return;
    }

    // Add flags based on what components the entity has
    // m_ECS->HasComponent<ECS::HierarchyComponent>(m_entity) ? m_propertyFlags |= Properties::Hierarchy : m_propertyFlags &= ~Properties::Hierarchy;
    // m_ECS->HasComponent<ECS::TagComponent>(m_entity) ? m_propertyFlags |= Properties::Tag : m_propertyFlags &= ~Properties::Tag;
    // m_ECS->HasComponent<ECS::TransformComponent>(m_entity) ? m_propertyFlags |= Properties::Transform : m_propertyFlags &= ~Properties::Transform;
}

const bool PropertyViewer::EntityModified()
{
    if (m_entityModified)
    {
        m_entityModified = false;
        return true;
    }

    return false;
}

}