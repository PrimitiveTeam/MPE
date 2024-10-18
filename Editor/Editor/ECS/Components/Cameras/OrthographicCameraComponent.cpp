#include "OrthographicCameraComponent.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
namespace ECS
{
OrthographicCameraComponent::OrthographicCameraComponent(float left, float right, float bottom, float top)
{
    m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_viewMatrix = glm::mat4(1.0f);
    m_aspectRatio = (right - left) / (top - bottom);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
    MPE_INFO("Orthographic Camera Created: {0}, {1}, {2}, {3}, {4}, {5}, {6}", left, right, bottom, top, -1.0f, 1.0f, m_aspectRatio);
}

void OrthographicCameraComponent::SetProjection(float left, float right, float bottom, float top)
{
    m_aspectRatio = (right - left) / (top - bottom);
    m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
    MPE_INFO("Orthographic Camera Projection set: {0}, {1}, {2}, {3}, {4}, {5}, {6}", left, right, bottom, top, -1.0f, 1.0f, m_aspectRatio);
}

void OrthographicCameraComponent::SetAspectRatio(float aspectRatio)
{
    m_aspectRatio = aspectRatio;
    MPE_WARN("Orthographic Camera Aspect Ratio is not currently supported.");
}
}
}