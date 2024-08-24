#include "TagProperties.h"

#include <imgui.h>

namespace MPE
{
void TagProperties::DrawTagProperties(ECS::ECS& ecs, ECS::Entity entity)
{
    ImGui::Text("Tag Properties");

    auto& tag = ecs.GetComponent<ECS::TagComponent>(entity);

    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, tag.tag.c_str());

    if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
    {
        tag.tag = std::string(buffer);
    }
}
}