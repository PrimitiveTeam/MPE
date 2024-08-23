#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/Components/Core/TransformComponent.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace MPE
{
namespace ECS
{
class MPE_API RotationUtilities
{
  public:
    static glm::quat EulerToQuaternion(const glm::vec3& eulerAngles);

    static glm::vec3 QuaternionToEuler(const glm::quat& quaternion);

    static void SetRotationFromEuler(TransformComponent& transform, const glm::vec3& eulerAngles);

    static glm::vec3 GetEulerFromRotation(const TransformComponent& transform);
};
}
}
