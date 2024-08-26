#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/ECS/Components/Core/TransformComponent.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
namespace ECS
{
class MPE_EDITOR_API RotationUtilities
{
  public:
    static glm::quat EulerToQuaternion(const glm::vec3& eulerAngles);

    static glm::vec3 QuaternionToEuler(const glm::quat& quaternion);

    static void SetRotationFromEuler(TransformComponent& transform, const glm::vec3& eulerAngles);

    static glm::vec3 GetEulerFromRotation(const TransformComponent& transform);
};
}
}
