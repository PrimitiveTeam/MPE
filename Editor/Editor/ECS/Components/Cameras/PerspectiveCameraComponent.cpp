#include "PerspectiveCameraComponent.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
namespace ECS
{
PerspectiveCameraComponent::PerspectiveCameraComponent(float fov, float aspectRatio, float nearClip, float farClip)
{
    m_fov = fov;
    m_aspectRatio = aspectRatio;
    m_near = nearClip;
    m_far = farClip;
    m_projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
    m_viewMatrix = glm::mat4(1.0f);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
    MPE_INFO("Perspective Camera Projection set: FOV={0}, AspectRatio={1}, Near={2}, Far={3}", fov, aspectRatio, nearClip, farClip);
}

PerspectiveCameraComponent::PerspectiveCameraComponent(float fov, float width, float height, float nearClip, float farClip)
{
    m_fov = fov;
    m_aspectRatio = width / height;
    m_near = nearClip;
    m_far = farClip;
    m_projectionMatrix = glm::perspective(glm::radians(fov), m_aspectRatio, nearClip, farClip);
    m_viewMatrix = glm::mat4(1.0f);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
    MPE_INFO("Perspective Camera Projection set: FOV={0}, AspectRatio={1}, Near={2}, Far={3}", fov, m_aspectRatio, nearClip, farClip);
}

void PerspectiveCameraComponent::SetProjection(float fov, float aspectRatio, float nearClip, float farClip)
{
    m_fov = fov;
    m_aspectRatio = aspectRatio;
    m_near = nearClip;
    m_far = farClip;
    MPE_INFO("Perspective Camera Projection set: FOV={0}, AspectRatio={1}, Near={2}, Far={3}", fov, aspectRatio, nearClip, farClip);
    m_projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCameraComponent::SetProjection(float fov, float width, float height, float nearClip, float farClip)
{
    m_fov = fov;
    m_aspectRatio = width / height;
    m_near = nearClip;
    m_far = farClip;
    MPE_INFO("Perspective Camera Projection set: FOV={0}, AspectRatio={1}, Near={2}, Far={3}", fov, m_aspectRatio, nearClip, farClip);
    m_projectionMatrix = glm::perspective(glm::radians(fov), m_aspectRatio, nearClip, farClip);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCameraComponent::SetAspectRatio(float aspectRatio)
{
    m_aspectRatio = aspectRatio;
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCameraComponent::SetFov(float fov)
{
    m_fov = fov;
    m_projectionMatrix = glm::perspective(glm::radians(fov), m_aspectRatio, m_near, m_far);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCameraComponent::SetNear(float nearClip)
{
    m_near = nearClip;
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, nearClip, m_far);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCameraComponent::SetFar(float farClip)
{
    m_far = farClip;
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, farClip);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

}
}