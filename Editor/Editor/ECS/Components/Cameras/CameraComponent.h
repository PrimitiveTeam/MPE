#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/ECS/ECS.h"
#include "Editor/Editor/ECS/Components/Core/TransformComponent.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
enum class CameraMode
{
    NotSet,
    Orthographic,
    Perspective
};

namespace ECS
{
class MPE_EDITOR_API CameraComponent
{
  public:
    CameraComponent() = default;
    ~CameraComponent() = default;

    void SetOrthographic(float left, float right, float bottom, float top, float nearClip, float farClip);
    void SetOrthographic(float aspectRatio, float zoomLevel, float nearClip, float farClip);
    void SetPerspective(float fov, float aspectRatio, float nearClip, float farClip);

    CameraMode GetMode() const { return m_mode; }
    void SetMode(CameraMode mode, bool recalculate = true);

    const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
    const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
    const glm::mat4& GetProjectionViewMatrix() const { return m_projectionViewMatrix; }

    // Since we must recalculate the projection matrix when we change the position, we cannot allow the user to change the position and rotation directly
    glm::vec3 GetPosition() const { return m_transform.position; }
    void SetPosition(const glm::vec3& position);

    float GetRotation() const { return m_transform.rotation.z; }
    void SetRotation(float rotation);

    glm::vec4 GetBounds() const;

  private:
    void RecalculateProjection();
    void ComputeProjectionViewMatrix();
    void ComputeViewMatrix();

  public:
    // Perspective

    float Perspective_GetFov() const { return m_perspective.fov; }
    void Perspective_SetFov(float fov);

    float Perspective_GetAspectRatio() const { return m_perspective.aspectRatio; }
    void Perspective_SetAspectRatio(float aspectRatio);
    void Perspective_SetAspectRatio(float width, float height);

    float Perspective_GetNear() const { return m_perspective.nearClip; }
    void Perspective_SetNear(float nearClip);

    float Perspective_GetFar() const { return m_perspective.farClip; }
    void Perspective_SetFar(float farClip);

    // Orthographic

    bool Orthographic_GetUseAspectRatio() const { return m_orthographic.useAspectRatio; }
    void Orthographic_SetUseAspectRatio(bool useAspectRatio);

    float Orthographic_GetLeft() const { return m_orthographic.left; }
    void Orthographic_SetLeft(float left);

    float Orthographic_GetRight() const { return m_orthographic.right; }
    void Orthographic_SetRight(float right);

    float Orthographic_GetBottom() const { return m_orthographic.bottom; }
    void Orthographic_SetBottom(float bottom);

    float Orthographic_GetTop() const { return m_orthographic.top; }
    void Orthographic_SetTop(float top);

    float Orthographic_GetNear() const { return m_orthographic.nearClip; }
    void Orthographic_SetNear(float nearClip);

    float Orthographic_GetFar() const { return m_orthographic.farClip; }
    void Orthographic_SetFar(float farClip);

    float Orthographic_GetAspectRatio() const { return m_orthographic.aspectRatio; }
    void Orthographic_SetAspectRatio(float aspectRatio);
    void Orthographic_SetAspectRatio(float width, float height);

    float Orthographic_GetZoomLevel() const { return m_orthographic.zoomLevel; }
    void Orthographic_SetZoomLevel(float zoomLevel);

  private:
    CameraMode m_mode = CameraMode::NotSet;

    TransformComponent m_transform;

    // transform component

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionViewMatrix;

    struct PerspectiveSettings
    {
        float fov = 45.0f;
        float aspectRatio = 1920.0f / 1080.0f;
        float nearClip = 0.1f;
        float farClip = 50.0f;
    } m_perspective;

    struct OrthographicSettings
    {
        bool useAspectRatio = false;
        float left = -1.0f;
        float right = 1.0f;
        float bottom = -1.0f;
        float top = 1.0f;
        float nearClip = -1.0f;
        float farClip = 1.0f;
        float aspectRatio = 0.0f;
        float zoomLevel = 1.0f;
    } m_orthographic;
};
}
}