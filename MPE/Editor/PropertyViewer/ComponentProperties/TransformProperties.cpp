#define GLM_ENABLE_EXPERIMENTAL
#include "TransformProperties.h"
#include "MPE/Editor/ECS/Utility/RotationUtilities.h"

#include <imgui.h>

namespace MPE
{
void TransformProperties::DrawTransformProperties(ECS::ECS& ecs, ECS::Entity entity)
{
    ImGui::Text("Transform Properties");

    auto& transform = ecs.GetComponent<ECS::TransformComponent>(entity);

    ImGui::DragFloat3("Position", &transform.position.x, 0.1f);
    glm::vec3 rotation = ECS::RotationUtilities::QuaternionToEuler(transform.rotation);
    ImGui::DragFloat3("Rotation", &rotation.x, 0.1f);
    transform.rotation = ECS::RotationUtilities::EulerToQuaternion(rotation);
    ImGui::DragFloat3("Scale", &transform.scale.x, 0.1f);
}
}