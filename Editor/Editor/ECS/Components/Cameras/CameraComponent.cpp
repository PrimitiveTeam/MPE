#include "CameraComponent.h"

#include "MPE/Vendor/GLM/GLM.h"
#include "MPE/Log/GlobalLog.h"

namespace MPE
{
namespace ECS
{
// CameraComponent::CameraComponent()
// {
// }

void CameraComponent::SetOrthographic(float left, float right, float bottom, float top, float nearClip, float farClip)
{
    MPE_ASSERT(m_mode == CameraMode::Orthographic, "Camera is not in Orthographic mode.");
    m_orthographic.useAspectRatio = false;
    m_orthographic.left = left;
    m_orthographic.right = right;
    m_orthographic.bottom = bottom;
    m_orthographic.top = top;
    m_orthographic.nearClip = nearClip;
    m_orthographic.farClip = farClip;
    m_orthographic.aspectRatio = 0.0f;
    m_orthographic.zoomLevel = 1.0f;
    this->RecalculateProjection();
}

void CameraComponent::SetOrthographic(float aspectRatio, float zoomLevel, float nearClip, float farClip)
{
    MPE_ASSERT(m_mode == CameraMode::Orthographic, "Camera is not in Orthographic mode.");
    m_orthographic.useAspectRatio = true;
    m_orthographic.left = -aspectRatio * zoomLevel;
    m_orthographic.right = aspectRatio * zoomLevel;
    m_orthographic.bottom = -zoomLevel;
    m_orthographic.top = zoomLevel;
    m_orthographic.nearClip = nearClip;
    m_orthographic.farClip = farClip;
    m_orthographic.aspectRatio = aspectRatio;
    m_orthographic.zoomLevel = zoomLevel;
    this->RecalculateProjection();
}

void CameraComponent::SetPerspective(float fov, float aspectRatio, float nearClip, float farClip)
{
    MPE_ASSERT(m_mode == CameraMode::Perspective, "Camera is not in Perspective mode.");
    m_perspective.fov = fov;
    m_perspective.aspectRatio = aspectRatio;
    m_perspective.nearClip = nearClip;
    m_perspective.farClip = farClip;
    this->RecalculateProjection();
}

void CameraComponent::SetMode(CameraMode mode, bool recalculate)
{
    m_mode = mode;

    if (recalculate) RecalculateProjection();
}

// TODO: Potential isDirty flag to save on computation?
void CameraComponent::SetPosition(const glm::vec3& position)
{
    if (m_transform.position == position) return;
    m_transform.position = position;
    this->ComputeViewMatrix();
}

void CameraComponent::SetRotation(float rotation)
{
    if (m_transform.rotation.z == rotation) return;
    m_transform.rotation.z = rotation;
    this->ComputeViewMatrix();
}

glm::vec4 CameraComponent::GetBounds() const
{
    switch (m_mode)
    {
        case CameraMode::Orthographic:
            MPE_ASSERT(m_orthographic.useAspectRatio, "Attempting to get bounds of Orthographic Camera without using aspect ratio.");
            return glm::vec4(-m_orthographic.aspectRatio * m_orthographic.zoomLevel, m_orthographic.aspectRatio * m_orthographic.zoomLevel,
                             -m_orthographic.zoomLevel, m_orthographic.zoomLevel);
        case CameraMode::Perspective:
            MPE_ASSERT(false, "Perspective Camera Bounds not implemented.");
            return glm::vec4(0.0f);
        default:
            MPE_ASSERT(false, "Unknown CameraMode.");
            return glm::vec4(0.0f);
    }
}

// This will be ran regardles what mode the camera is in if we use any of the setters
void CameraComponent::RecalculateProjection()
{
    switch (m_mode)
    {
        case CameraMode::Orthographic:
            if (m_orthographic.left == 0.0f && m_orthographic.right == 0.0f && m_orthographic.bottom == 0.0f && m_orthographic.top == 0.0f)
            {
                MPE_WARN("Orthographic Camera values not set, setting to default values.");
                m_orthographic.useAspectRatio = false;
                m_orthographic.left = -1.0f;
                m_orthographic.right = 1.0f;
                m_orthographic.bottom = -1.0f;
                m_orthographic.top = 1.0f;
                m_orthographic.nearClip = -1.0f;
                m_orthographic.farClip = 1.0f;
                m_orthographic.aspectRatio = 0.0f;
                m_orthographic.zoomLevel = 1.0f;
            }

            if (!m_orthographic.useAspectRatio)
            {
                m_projectionMatrix = glm::ortho(m_orthographic.left, m_orthographic.right, m_orthographic.bottom, m_orthographic.top, m_orthographic.nearClip,
                                                m_orthographic.farClip);
                // m_aspectRatio = (m_orthographic.right - m_orthographic.left) / (m_orthographic.top - m_orthographic.bottom);
            }
            else
            {
                m_projectionMatrix = glm::ortho(-m_orthographic.aspectRatio * m_orthographic.zoomLevel, m_orthographic.aspectRatio * m_orthographic.zoomLevel,
                                                -m_orthographic.zoomLevel, m_orthographic.zoomLevel, m_orthographic.nearClip, m_orthographic.farClip);
            }
            this->ComputeViewMatrix();
            this->ComputeProjectionViewMatrix();

            MPE_INFO("Orthographic Camera Recalculated: {0}, {1}, {2}, {3}, {4}, {5}", m_orthographic.left, m_orthographic.right, m_orthographic.bottom,
                     m_orthographic.top, m_orthographic.nearClip, m_orthographic.farClip);
            break;
        case CameraMode::Perspective:
            if (m_perspective.fov == 0.0f && m_perspective.aspectRatio == 0.0f && m_perspective.nearClip == 0.0f && m_perspective.farClip == 0.0f)
            {
                MPE_WARN("Perspective Camera values not set, setting to default values.");
                m_perspective.fov = 45.0f;
                m_perspective.aspectRatio = 1920.0f / 1080.0f;
                m_perspective.nearClip = 0.1f;
                m_perspective.farClip = 50.0f;
            }

            m_projectionMatrix = glm::perspective(glm::radians(m_perspective.fov), m_perspective.aspectRatio, m_perspective.nearClip, m_perspective.farClip);
            this->ComputeViewMatrix();
            this->ComputeProjectionViewMatrix();

            MPE_INFO("Perspective Camera Projection set: FOV={0}, AspectRatio={1}, Near={2}, Far={3}", m_perspective.fov, m_perspective.aspectRatio,
                     m_perspective.nearClip, m_perspective.farClip);
            break;
    }
}

void CameraComponent::ComputeProjectionViewMatrix()
{
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void CameraComponent::ComputeViewMatrix()
{
    glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), m_transform.position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_transform.rotation.z), glm::vec3(0, 0, 1));

    m_viewMatrix = glm::inverse(transform);

    this->ComputeProjectionViewMatrix();
}

// Perspective

void CameraComponent::Perspective_SetFov(float fov)
{
    if (m_perspective.fov == fov) return;
    m_perspective.fov = fov;
    this->RecalculateProjection();
}

void CameraComponent::Perspective_SetAspectRatio(float aspectRatio)
{
    if (m_perspective.aspectRatio == aspectRatio) return;
    m_perspective.aspectRatio = aspectRatio;
    this->RecalculateProjection();
}

void CameraComponent::Perspective_SetAspectRatio(float width, float height)
{
    auto aspectRatio = width / height;
    if (m_perspective.aspectRatio == aspectRatio) return;
    m_perspective.aspectRatio = aspectRatio;
    this->RecalculateProjection();
}

void CameraComponent::Perspective_SetNear(float nearClip)
{
    if (m_perspective.nearClip == nearClip) return;
    m_perspective.nearClip = nearClip;
    this->RecalculateProjection();
}

void CameraComponent::Perspective_SetFar(float farClip)
{
    if (m_perspective.farClip == farClip) return;
    m_perspective.farClip = farClip;
    this->RecalculateProjection();
}

// Orthographic

void CameraComponent::Orthographic_SetUseAspectRatio(bool useAspectRatio)
{
    if (m_orthographic.useAspectRatio == useAspectRatio) return;
    m_orthographic.useAspectRatio = useAspectRatio;
    this->RecalculateProjection();
}

void CameraComponent::Orthographic_SetLeft(float left)
{
    if (m_orthographic.left == left) return;
    m_orthographic.left = left;
    this->RecalculateProjection();
}

void CameraComponent::Orthographic_SetRight(float right)
{
    if (m_orthographic.right == right) return;
    m_orthographic.right = right;
    this->RecalculateProjection();
}

void CameraComponent::Orthographic_SetBottom(float bottom)
{
    if (m_orthographic.bottom == bottom) return;
    m_orthographic.bottom = bottom;
    this->RecalculateProjection();
}

void CameraComponent::Orthographic_SetTop(float top)
{
    if (m_orthographic.top == top) return;
    m_orthographic.top = top;
    this->RecalculateProjection();
}

void CameraComponent::Orthographic_SetNear(float nearClip)
{
    if (m_orthographic.nearClip == nearClip) return;
    m_orthographic.nearClip = nearClip;
    this->RecalculateProjection();
}

void CameraComponent::Orthographic_SetFar(float farClip)
{
    if (m_orthographic.farClip == farClip) return;
    m_orthographic.farClip = farClip;
    this->RecalculateProjection();
}

void CameraComponent::Orthographic_SetAspectRatio(float aspectRatio)
{
    if (m_orthographic.aspectRatio == aspectRatio) return;
    m_orthographic.aspectRatio = aspectRatio;
    this->RecalculateProjection();
}

void CameraComponent::Orthographic_SetAspectRatio(float width, float height)
{
    if (m_orthographic.aspectRatio == width / height) return;
    m_orthographic.aspectRatio = width / height;
    this->RecalculateProjection();
}

void CameraComponent::Orthographic_SetZoomLevel(float zoomLevel)
{
    if (m_orthographic.zoomLevel == zoomLevel) return;
    m_orthographic.zoomLevel = zoomLevel;
    this->RecalculateProjection();
}

}
}