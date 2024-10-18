#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/Objects/Base/Object.h"
#include "Editor/Editor/ECS/Components/Cameras/CameraComponent.h"
#include "Editor/Editor/ECS/Components/Cameras/OrthographicCameraComponent.h"
#include "Editor/Editor/Objects/Cameras/Camera.h"

namespace MPE
{
class MPE_EDITOR_API OrthographicCamera : public Camera
{
  public:
    OrthographicCamera(ECS::ECS& ecs);
    OrthographicCamera(ECS::ECS& ecs, float left, float right, float bottom, float top);

  private:
    virtual void Init() override;

  public:
    virtual void OnUpdate(Time deltaTime) override;
    virtual void OnRender(Camera& camera) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Event& event) override;

    // ECS::OrthographicCameraComponent& GetOrthographicCameraComponent() { return *static_cast<ECS::OrthographicCameraComponent*>(m_cameraComponent); }
    REF<ECS::OrthographicCameraComponent> GetOrthographicCameraComponent()
    {
        return std::dynamic_pointer_cast<ECS::OrthographicCameraComponent>(m_cameraComponent);
    }
};
}