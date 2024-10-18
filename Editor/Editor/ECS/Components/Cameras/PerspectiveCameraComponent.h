#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/ECS/ECS.h"
#include "MPE/Vendor/GLM/GLM.h"
#include "CameraComponent.h"

namespace MPE
{
namespace ECS
{
class MPE_EDITOR_API PerspectiveCameraComponent : public CameraComponent
{
  public:
    // float near, float far
    PerspectiveCameraComponent(float fov, float aspectRatio, float nearClip, float farClip);
    PerspectiveCameraComponent(float fov, float width, float height, float nearClip, float farClip);

    ~PerspectiveCameraComponent() = default;

    void SetProjection(float fov, float aspectRatio, float nearClip, float farClip);
    void SetProjection(float fov, float width, float height, float nearClip, float farClip);

    virtual void SetAspectRatio(float aspectRatio) override final;

    float GetFov() const { return m_fov; }
    void SetFov(float fov);

    float GetNear() const { return m_near; }
    void SetNear(float nearClip);

    float GetFar() const { return m_far; }
    void SetFar(float farClip);

  private:
    float m_fov;
    float m_near;
    float m_far;
};
}
}