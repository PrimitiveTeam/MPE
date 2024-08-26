#pragma once

#include "MPE/Core/_CORE.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
class MPE_API OrthographicCamera
{
  public:
    // float near, float far
    OrthographicCamera(float left, float right, float bottom, float top);
    void SetProjection(float left, float right, float bottom, float top);

    void SetPosition(const glm::vec3 &position);
    void SetRotation(float rotation);

    const glm::vec3 &GetPosition() const { return m_cameraPosition; }
    // get position but allow to modify it
    glm::vec3 &ManipulatePosition() { return m_cameraPosition; }
    float GetRotation() const { return m_cameraZAxisRotation; }

    const glm::mat4 &GetProjectionMatrix() const { return m_projectionMatrix; }
    const glm::mat4 &GetViewMatrix() const { return m_viewMatrix; }
    const glm::mat4 &GetProjectionViewMatrix() const { return m_projectionViewMatrix; }

  private:
    void ComputeViewMatrix();

  private:
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionViewMatrix;

    glm::vec3 m_cameraPosition = {0.0f, 0.0f, 0.0f};
    float m_cameraZAxisRotation = 0.0f;
};
}