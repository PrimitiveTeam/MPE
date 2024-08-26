#pragma once

#include "MPE/Core/_CORE.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
class MPE_API PerspectiveCamera
{
  public:
    // float near, float far
    PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip);
    PerspectiveCamera(float fov, float width, float height, float nearClip, float farClip);
    void SetProjection(float fov, float aspectRatio, float nearClip, float farClip);
    void SetProjection(float fov, float width, float height, float nearClip, float farClip);

    void SetPosition(const glm::vec3 &position);
    void SetRotation(float rotation);

    const glm::vec3 &GetPosition() const { return m_cameraPosition; }
    // get position but allow to modify it
    glm::vec3 &ManipulatePosition() { return m_cameraPosition; }
    float GetRotation() const { return m_cameraZAxisRotation; }

    const glm::mat4 &GetProjectionMatrix() const { return m_projectionMatrix; }
    const glm::mat4 &GetViewMatrix() const { return m_viewMatrix; }
    const glm::mat4 &GetProjectionViewMatrix() const { return m_projectionViewMatrix; }

    float GetFov() const { return m_fov; }
    void SetFov(float fov);

    float GetAspectRatio() const { return m_aspectRatio; }
    void SetAspectRatio(float aspectRatio);
    void SetAspectRatio(float width, float height);

    float GetNear() const { return m_near; }
    void SetNear(float nearClip);

    float GetFar() const { return m_far; }
    void SetFar(float farClip);

  private:
    void ComputeViewMatrix();

  private:
    float m_fov;
    float m_aspectRatio;
    float m_near;
    float m_far;

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionViewMatrix;

    glm::vec3 m_cameraPosition = {0.0f, 0.0f, 0.0f};
    float m_cameraZAxisRotation = 0.0f;
};
}