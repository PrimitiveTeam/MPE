#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Time/Time.h"
#include "MPE/Events/EventApp.h"
#include "MPE/Events/EventMouse.h"

namespace MPE
{
class MPE_API StaticOrthographicCamera
{
  public:
    StaticOrthographicCamera(float aspectRatio, bool rotation = false);

    void OnUpdate(Time deltaTime);
    void OnEvent(Event &e);

    OrthographicCamera &GetCamera() { return m_camera; }
    const OrthographicCamera &GetCamera() const { return m_camera; }

    void SetPosition(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void SetRotation(float rad = 0.0f);
    void SetZoomLevel(float zoom);
    void Reset(float x = 0.0f, float y = 0.0f, float z = 0.0f, float rad = 0.0f, float zoom = 1.0f);

    float GetZoomLevel() const { return m_zoomLevel; }
    glm::vec4 GetBounds() const { return glm::vec4(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel); }

  private:
    float m_aspectRatio;
    float m_zoomLevel = 1.0f;
    float m_maxZoomLevel = 0.25f;
    OrthographicCamera m_camera;
    bool m_rotation;

    glm::vec3 m_cameraPosition = {0.0f, 0.0f, 0.0f};
    float m_cameraRotation = 0.0f;

    float m_cameraDefaultSpeed[2] = {
        // CAMERA MOVEMENT SPEED
        1.0f,
        // CAMERA ROTATION SPEED
        30.0f};
    float m_cameraMovementSpeed = 0.0f;
    float m_cameraRotationSpeed = 0.0f;
    float m_cameraZoomSpeed = 0.25f;

    bool OnMouseScrolled(MouseScrolledEvent &e);
    bool OnWindowResized(WindowResizeEvent &e);
};
}