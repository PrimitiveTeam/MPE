#define GLM_ENABLE_EXPERIMENTAL
#include "RotationUtilities.h"

namespace MPE
{
namespace ECS
{
glm::quat RotationUtilities::EulerToQuaternion(const glm::vec3& eulerAngles)
{
    return glm::quat(glm::radians(eulerAngles));
}

glm::vec3 RotationUtilities::QuaternionToEuler(const glm::quat& quaternion)
{
    return glm::degrees(glm::eulerAngles(quaternion));
}

void RotationUtilities::SetRotationFromEuler(TransformComponent& transform, const glm::vec3& eulerAngles)
{
    transform.rotation = EulerToQuaternion(eulerAngles);
}

glm::vec3 RotationUtilities::GetEulerFromRotation(const TransformComponent& transform)
{
    return QuaternionToEuler(transform.rotation);
}
}
}
