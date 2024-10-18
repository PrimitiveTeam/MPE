#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/ECS/ECS.h"
#include "MPE/Vendor/GLM/GLM.h"
#include "Editor/Editor/ECS/Components/Cameras/CameraComponent.h"

#include <array>

namespace MPE
{
namespace ECS
{
class MPE_EDITOR_API CameraControllerComponent
{
  public:
    CameraControllerComponent(REF<CameraComponent> cameraComponent) : m_cameraComponent(cameraComponent) {}

    virtual ~CameraControllerComponent() = default;

    // virtual void OnEvent(Event &e) = 0;

    glm::vec4 GetBounds() const
    {
        auto aspectRatio = m_cameraComponent->GetAspectRatio();
        return glm::vec4(-aspectRatio * m_zoomLevel, aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
    }

    float GetZoomLevel() const { return m_zoomLevel; }
    virtual void SetZoomLevel(float zoom) = 0;

    float GetMaxZoomLevel() const { return m_maxZoomLevel; }
    virtual void SetMaxZoomLevel(float maxZoom) { m_maxZoomLevel = maxZoom; }

    bool IsRotationEnabled() const { return m_isRotationEnabled; }
    virtual void SetRotationEnabled(bool enabled) { m_isRotationEnabled = enabled; }

    std::array<float, 2> GetCameraDefaultSpeed() const { return {m_cameraDefaultSpeed[0], m_cameraDefaultSpeed[1]}; }
    virtual void SetCameraDefaultSpeed(float movementSpeed, float rotationSpeed)
    {
        m_cameraDefaultSpeed[0] = movementSpeed;
        m_cameraDefaultSpeed[1] = rotationSpeed;
    }

    float GetCameraMovementSpeed() const { return m_cameraMovementSpeed; }
    virtual void SetCameraMovementSpeed(float speed) { m_cameraMovementSpeed = speed; }

    float GetCameraRotationSpeed() const { return m_cameraRotationSpeed; }
    virtual void SetCameraRotationSpeed(float speed) { m_cameraRotationSpeed = speed; }

    float GetCameraZoomSpeed() const { return m_cameraZoomSpeed; }
    virtual void SetCameraZoomSpeed(float speed) { m_cameraZoomSpeed = speed; }

  protected:
    // virtual bool OnMouseScrolled(MouseScrolledEvent &e) = 0;
    // virtual bool OnWindowResized(WindowResizeEvent &e) = 0;

  protected:
    REF<CameraComponent> m_cameraComponent = nullptr;

    // Controller settings
    float m_zoomLevel = 1.0f;
    float m_maxZoomLevel = 0.25f;
    bool m_isRotationEnabled = true;
    // Speed settings
    float m_cameraDefaultSpeed[2] = {
        // CAMERA MOVEMENT SPEED
        1.0f,
        // CAMERA ROTATION SPEED
        30.0f};
    float m_cameraMovementSpeed = 0.0f;
    float m_cameraRotationSpeed = 0.0f;
    float m_cameraZoomSpeed = 0.25f;
};
}
}