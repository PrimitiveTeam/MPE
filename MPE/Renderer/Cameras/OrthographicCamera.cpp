#include "OrthographicCamera.h"
#include "MPE/MPEPCH.h"

#include "MPE/Log/GlobalLog.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_viewMatrix(1.0f)
{
    MPE_INFO("Orthographic Camera Created: {0}, {1}, {2}, {3}, {4}, {5}", left, right, bottom, top, -1.0f, 1.0f);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
    MPE_INFO("Orthographic Camera Projection set: {0}, {1}, {2}, {3}", left, right, bottom, top);
    m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void OrthographicCamera::ComputeViewMatrix()
{
    glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), m_cameraPosition) * glm::rotate(glm::mat4(1.0f), glm::radians(m_cameraZAxisRotation), glm::vec3(0, 0, 1));

    m_viewMatrix = glm::inverse(transform);

    m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

void OrthographicCamera::SetPosition(const glm::vec3 &position)
{
    m_cameraPosition = position;
    ComputeViewMatrix();
}
void OrthographicCamera::SetRotation(float rotation)
{
    m_cameraZAxisRotation = rotation;
    ComputeViewMatrix();
}
}