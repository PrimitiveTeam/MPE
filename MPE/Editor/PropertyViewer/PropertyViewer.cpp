#include "PropertyViewer.h"

#include "MPE/Editor/ECS/ECS.h"
#include "MPE/Log/GlobalLog.h"
// Properties
#include "MPE/Editor/PropertyViewer/ComponentProperties/HierarchyProperties.h"
#include "MPE/Editor/PropertyViewer/ComponentProperties/TagProperties.h"
#include "MPE/Editor/PropertyViewer/ComponentProperties/TransformProperties.h"

#include <imgui.h>

namespace MPE
{
PropertyViewer::PropertyViewer(ECS::ECS& ecs) : m_ECS(&ecs), m_entity(entt::null), m_propertyFlags(Properties::None) {}

void PropertyViewer::OnUpdate(Time deltaTime) {}
void PropertyViewer::OnRender(OrthographicCamera& camera) {}
void PropertyViewer::OnImGuiRender()
{
    if (m_entity == entt::null)
    {
        return;
    }

    ImGui::Begin("Properties");
    if ((m_propertyFlags & Properties::Tag) != Properties::None)
    {
        TagProperties::DrawTagProperties(*m_ECS, m_entity);
        ImGui::Separator();
    }
    if ((m_propertyFlags & Properties::Hierarchy) != Properties::None)
    {
        HierarchyProperties::DrawHierarchyProperties(*m_ECS, m_entity);
        ImGui::Separator();
    }
    if ((m_propertyFlags & Properties::Transform) != Properties::None)
    {
        TransformProperties::DrawTransformProperties(*m_ECS, m_entity);
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
    if (m_entity == entt::null)
    {
        m_propertyFlags = Properties::None;
        return;
    }

    // Add flags based on what components the entity has
    m_ECS->HasComponent<ECS::HierarchyComponent>(m_entity) ? m_propertyFlags |= Properties::Hierarchy : m_propertyFlags &= ~Properties::Hierarchy;
    m_ECS->HasComponent<ECS::TagComponent>(m_entity) ? m_propertyFlags |= Properties::Tag : m_propertyFlags &= ~Properties::Tag;
    m_ECS->HasComponent<ECS::TransformComponent>(m_entity) ? m_propertyFlags |= Properties::Transform : m_propertyFlags &= ~Properties::Transform;
}

}