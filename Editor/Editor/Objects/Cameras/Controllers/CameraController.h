#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"
#include "MPE/Events/EventApp.h"
#include "MPE/Events/EventMouse.h"
#include "MPE/Events/Event.h"
#include "Editor/Editor/Objects/Base/Object.h"
#include "Editor/Editor/ECS/Components/Cameras/Controller/CameraControllerComponent.h"

namespace MPE
{
class MPE_EDITOR_API CameraController : public Object
{
  public:
    CameraController(ECS::ECS& ecs) : Object(ecs) {}
    CameraController(ECS::ECS& ecs, REF<Camera> camera) : Object(ecs), m_camera(camera) {}

    virtual ~CameraController() = default;

    virtual void OnUpdate(Time deltaTime) override = 0;
    virtual void OnRender(Camera& camera) override = 0;
    virtual void OnImGuiRender() override = 0;
    virtual void OnEvent(Event& event) override = 0;

    REF<Camera> GetCamera() { return m_camera; }
    const REF<Camera> GetCamera() const { return m_camera; }

    REF<ECS::CameraControllerComponent> GetCameraControllerComponent() { return m_cameraControllerComponent; }
    const REF<ECS::CameraControllerComponent> GetCameraControllerComponent() const { return m_cameraControllerComponent; }

  private:
    REF<Camera> m_camera = nullptr;
    REF<ECS::CameraControllerComponent> m_cameraControllerComponent = nullptr;
};
}
