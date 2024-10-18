#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"
#include "MPE/Events/Event.h"
#include "Editor/Editor/Objects/Base/Object.h"
#include "Editor/Editor/ECS/Components/Cameras/CameraComponent.h"

namespace MPE
{
class MPE_EDITOR_API Camera : public Object
{
  public:
    Camera(ECS::ECS& ecs) : Object(ecs) {}
    virtual ~Camera() = default;

    virtual void OnUpdate(Time deltaTime) override = 0;
    virtual void OnRender(Camera& camera) override = 0;
    virtual void OnImGuiRender() override = 0;
    virtual void OnEvent(Event& event) override = 0;

    REF<ECS::CameraComponent> GetCameraComponent() { return m_cameraComponent; }
    const REF<ECS::CameraComponent> GetCameraComponent() const { return m_cameraComponent; }
    // ECS::CameraComponent* GetCameraComponent() { return m_cameraComponent; }
    // const ECS::CameraComponent* GetCameraComponent() const { return m_cameraComponent; }

  protected:
    REF<ECS::CameraComponent> m_cameraComponent = nullptr;
    // ECS::CameraComponent* m_cameraComponent = nullptr;
};
}
