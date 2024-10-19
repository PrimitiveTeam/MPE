#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"
#include "MPE/Events/Event.h"
#include "MPE/Events/EventApp.h"
#include "MPE/Events/EventMouse.h"
#include "Editor/Editor/Objects/Base/Object.h"
#include "Editor/Editor/ECS/Components/Cameras/CameraComponent.h"
#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
class MPE_EDITOR_API Camera : public Object
{
  public:
    Camera(ECS::ECS& ecs);
    Camera(ECS::ECS& ecs, const REF<ECS::CameraComponent>& cameraComponent);
    // Camera(ECS::ECS& ecs, const CameraComponent& cameraComponent);
    ~Camera();

    void OnUpdate(Time deltaTime);
    void OnRender(Camera& camera);
    void OnImGuiRender();
    void OnEvent(Event& event);

  private:
    bool OnMouseScrolled(MouseScrolledEvent& e);
    bool OnWindowResized(WindowResizeEvent& e);

  public:
    REF<ECS::CameraComponent> GetCameraComponent() { return m_cameraComponent; }
    const REF<ECS::CameraComponent> GetCameraComponent() const { return m_cameraComponent; }

    glm::mat4 GetProjection() const;
    glm::vec4 GetBounds() const;

    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);

    float GetRotation() const;
    void SetRotation(float rotation);

    float GetFov() const;
    void SetFov(float fov);

    float GetAspectRatio() const;
    void SetAspectRatio(float aspectRatio);
    
    float GetNear() const;
    void SetNear(float nearClip);

    float GetFar() const;
    void SetFar(float farClip);

    float GetZoomLevel() const;
    void SetZoomLevel(float zoom);

    float GetMaxZoomLevel() const { return m_maxZoomInLevel; }
    void SetMaxZoomLevel(float maxZoom) { m_maxZoomInLevel = maxZoom; }

    bool IsRotationEnabled() const { return m_isRotationEnabled; }
    void SetRotationEnabled(bool enabled) { m_isRotationEnabled = enabled; }
    void ToggleRotation() { m_isRotationEnabled = !m_isRotationEnabled; }

    float GetCameraMovementSpeed() const { return m_currentMovementSpeed; }
    void SetCameraMovementSpeed(float speed) { m_currentMovementSpeed = speed; }

    float GetCameraRotationSpeed() const { return m_currentRotationSpeed; }
    void SetCameraRotationSpeed(float speed) { m_currentRotationSpeed = speed; }

    float GetCameraZoomSpeed() const { return m_currentZoomSpeed; }
    void SetCameraZoomSpeed(float speed) { m_currentZoomSpeed = speed; }

    float GetDefaultMovementSpeed() const { return m_defaultMovementSpeed; }
    void SetDefaultMovementSpeed(float speed) { m_defaultMovementSpeed = speed; }

    float GetDefaultRotationSpeed() const { return m_defaultRotationSpeed; }
    void SetDefaultRotationSpeed(float speed) { m_defaultRotationSpeed = speed; }

    float GetDefaultZoomSpeed() const { return m_defaultZoomSpeed; }
    void SetDefaultZoomSpeed(float speed) { m_defaultZoomSpeed = speed; }

  private:
    REF<ECS::CameraComponent> m_cameraComponent = nullptr;

    bool m_isControllerEnabled = true;
    // Controller properties
    float m_maxZoomInLevel = 0.25f;
    bool m_isRotationEnabled = true;
    // Default states
    float m_defaultMovementSpeed = 1.0f;
    float m_defaultRotationSpeed = 30.0f;
    float m_defaultZoomSpeed = 0.25f;
    // Current states
    float m_currentMovementSpeed = 0.0f;
    float m_currentRotationSpeed = 0.0f;
    float m_currentZoomSpeed = 0.0f;
};
}
