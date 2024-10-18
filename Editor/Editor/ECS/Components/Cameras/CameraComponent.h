#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/ECS/ECS.h"
#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
namespace ECS
{
class MPE_EDITOR_API CameraComponent
{
  public:
    // float near, float far
    CameraComponent() = default;
    virtual ~CameraComponent() = default;

    const glm::vec3 &GetPosition() const { return m_cameraPosition; }
    glm::vec3 &ManipulatePosition() { return m_cameraPosition; }
    void SetPosition(const glm::vec3 &position) { m_cameraPosition = position; }

    float GetRotation() const { return m_cameraZAxisRotation; }
    float &ManipulateRotation() { return m_cameraZAxisRotation; }
    void SetRotation(float rotation) { m_cameraZAxisRotation = rotation; }

    float GetAspectRatio() const { return m_aspectRatio; }
    virtual void SetAspectRatio(float aspectRatio) = 0;

    const glm::mat4 &GetProjectionMatrix() const { return m_projectionMatrix; }
    const glm::mat4 &GetViewMatrix() const { return m_viewMatrix; }
    const glm::mat4 &GetProjectionViewMatrix() const { return m_projectionViewMatrix; }

  protected:
    void ComputeViewMatrix()
    {
        glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), m_cameraPosition) * glm::rotate(glm::mat4(1.0f), glm::radians(m_cameraZAxisRotation), glm::vec3(0, 0, 1));

        m_viewMatrix = glm::inverse(transform);

        m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
    }

  protected:
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionViewMatrix;

    glm::vec3 m_cameraPosition = {0.0f, 0.0f, 0.0f};
    float m_cameraZAxisRotation = 0.0f;
    float m_aspectRatio;
};
}
}