#include "PerspectiveCamera.h"
#include "MPE/MPEPCH.h"

#include "MPE/Log/GlobalLog.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip)
    : m_fov(fov),
      m_aspectRatio(aspectRatio),
      m_near(nearClip),
      m_far(farClip),
      m_projectionMatrix(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip)),
      m_viewMatrix(1.0f)
{
    MPE_INFO("Perspective Camera Projection set: FOV={0}, AspectRatio={1}, Near={2}, Far={3}", fov, aspectRatio, nearClip, farClip);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

PerspectiveCamera::PerspectiveCamera(float fov, float width, float height, float nearClip, float farClip)
    : m_fov(fov),
      m_aspectRatio(width / height),
      m_near(nearClip),
      m_far(farClip),
      m_projectionMatrix(glm::perspective(glm::radians(fov), m_aspectRatio, nearClip, farClip)),
      m_viewMatrix(1.0f)
{
    MPE_INFO("Perspective Camera Projection set: FOV={0}, AspectRatio={1}, Near={2}, Far={3}", fov, m_aspectRatio, nearClip, farClip);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCamera::SetProjection(float fov, float aspectRatio, float nearClip, float farClip)
{
    m_fov = fov;
    m_aspectRatio = aspectRatio;
    m_near = nearClip;
    m_far = farClip;
    MPE_INFO("Perspective Camera Projection set: FOV={0}, AspectRatio={1}, Near={2}, Far={3}", fov, aspectRatio, nearClip, farClip);
    m_projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCamera::SetProjection(float fov, float width, float height, float nearClip, float farClip)
{
    m_fov = fov;
    m_aspectRatio = width / height;
    m_near = nearClip;
    m_far = farClip;
    MPE_INFO("Perspective Camera Projection set: FOV={0}, AspectRatio={1}, Near={2}, Far={3}", fov, m_aspectRatio, nearClip, farClip);
    m_projectionMatrix = glm::perspective(glm::radians(fov), m_aspectRatio, nearClip, farClip);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCamera::ComputeViewMatrix()
{
    glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), m_cameraPosition) * glm::rotate(glm::mat4(1.0f), glm::radians(m_cameraZAxisRotation), glm::vec3(0, 0, 1));

    m_viewMatrix = glm::inverse(transform);

    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCamera::SetPosition(const glm::vec3 &position)
{
    m_cameraPosition = position;
    ComputeViewMatrix();
}
void PerspectiveCamera::SetRotation(float rotation)
{
    m_cameraZAxisRotation = rotation;
    ComputeViewMatrix();
}

void PerspectiveCamera::SetFov(float fov)
{
    m_fov = fov;
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCamera::SetAspectRatio(float aspectRatio)
{
    m_aspectRatio = aspectRatio;
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCamera::SetAspectRatio(float width, float height)
{
    m_aspectRatio = width / height;
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCamera::SetNear(float nearClip)
{
    m_near = nearClip;
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCamera::SetFar(float farClip)
{
    m_far = farClip;
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}
}