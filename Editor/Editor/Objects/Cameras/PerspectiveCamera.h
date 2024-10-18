#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/Objects/Base/Object.h"
#include "Editor/Editor/ECS/Components/Cameras/CameraComponent.h"
#include "Editor/Editor/ECS/Components/Cameras/PerspectiveCameraComponent.h"
#include "Editor/Editor/Objects/Cameras/Camera.h"

namespace MPE
{
class MPE_EDITOR_API PerspectiveCamera : public Camera
{
  public:
    PerspectiveCamera(ECS::ECS& ecs);
    PerspectiveCamera(ECS::ECS& ecs, float fov, float aspectRatio, float nearClip, float farClip);

  private:
    virtual void Init() override;

  public:
    virtual void OnUpdate(Time deltaTime) override;
    virtual void OnRender(Camera& camera) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Event& event) override;

    // ECS::PerspectiveCameraComponent& GetPerspectiveCameraComponent() { return *static_cast<ECS::PerspectiveCameraComponent*>(m_cameraComponent); }
    REF<ECS::PerspectiveCameraComponent> GetPerspectiveCameraComponent()
    {
        return std::dynamic_pointer_cast<ECS::PerspectiveCameraComponent>(m_cameraComponent);
    };
};
}