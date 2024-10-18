#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"
#include "MPE/Events/EventApp.h"
#include "MPE/Events/EventMouse.h"
#include "MPE/Events/Event.h"
#include "Editor/Editor/Objects/Base/Object.h"
#include "Editor/Editor/ECS/Components/Cameras/Controller/CameraControllerComponent.h"
#include "Editor/Editor/ECS/Components/Cameras/Controller/OrthographicCameraControllerComponent.h"
#include "Editor/Editor/Objects/Cameras/Controllers/CameraController.h"
#include "Editor/Editor/Objects/Cameras/OrthographicCamera.h"

namespace MPE
{
class MPE_EDITOR_API OrthographicCameraController : public CameraController
{
  public:
    OrthographicCameraController(ECS::ECS& ecs);
    OrthographicCameraController(ECS::ECS& ecs, float aspectRatio);
    OrthographicCameraController(ECS::ECS& ecs, REF<OrthographicCamera> camera);
    OrthographicCameraController(ECS::ECS& ecs, REF<OrthographicCamera> camera, float aspectRatio);

    ~OrthographicCameraController() = default;

    virtual void OnUpdate(Time deltaTime) override final;
    virtual void OnRender(Camera& camera) override final;
    virtual void OnImGuiRender() override final;
    virtual void OnEvent(Event& event) override final;

    REF<OrthographicCamera> GetOrthographicCamera() { return m_orthographicaCamera; }
    const REF<OrthographicCamera> GetOrthographicCamera() const { return m_orthographicaCamera; }

    REF<ECS::OrthographicCameraControllerComponent> GetOrthographicCameraControllerComponent() { return m_orthographicCameraControllerComponent; }
    const REF<ECS::OrthographicCameraControllerComponent> GetOrthographiCameraControllerComponent() const { return m_orthographicCameraControllerComponent; }

  private:
    bool OnMouseScrolled(MouseScrolledEvent& e);
    bool OnWindowResized(WindowResizeEvent& e);

  private:
    REF<OrthographicCamera> m_orthographicaCamera = nullptr;
    REF<ECS::OrthographicCameraControllerComponent> m_orthographicCameraControllerComponent = nullptr;
};
}
