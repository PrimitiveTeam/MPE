#include "HierarchyProperties.h"

#include <imgui.h>

namespace MPE
{
void HierarchyProperties::DrawHierarchyProperties(ECS::ECS& ecs, ECS::Entity entity)
{
    ImGui::Text("Hierarchy Properties");

    auto& hierarchy = ecs.GetComponent<ECS::HierarchyComponent>(entity);

    ImGui::Text("Parent: %d", hierarchy.parent);
    ImGui::Text("Children: %d", hierarchy.child);
}
}