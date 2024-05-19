#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Time/Time.h"
#include "MPE/Events/EventApp.h"
#include "MPE/Events/EventMouse.h"

namespace MPE
{
class MPE_API OrthographicCameraController
{
  private:
    float ASPECT_RATIO;
    float ZOOM_LEVEL = 1.0f;
    float MAX_ZOOM_LEVEL = 0.25f;
    OrthographicCamera CAMERA;
    bool ROTATION;

    glm::vec3 CAMERA_POSITION = {0.0f, 0.0f, 0.0f};
    float CAMERA_ROTATION = 0.0f;

    float CAMERA_DEFAULT_SPEEDS[2] = {
        // CAMERA MOVEMENT SPEED
        1.0f,
        // CAMERA ROTATION SPEED
        30.0f};
    float CAMERA_MOVEMENT_SPEED = 0.0f;
    float CAMERA_ROTATION_SPEED = 0.0f;
    float CAMERA_ZOOM_SPEED = 0.25f;

    bool OnMouseScrolled(MouseScrolledEvent &e);
    bool OnWindowResized(WindowResizeEvent &e);

  public:
    OrthographicCameraController(float aspectRatio, bool rotation = false);

    void OnUpdate(Time deltatime);
    void OnEvent(Event &e);

    OrthographicCamera &GetCamera() { return CAMERA; }
    const OrthographicCamera &GetCamera() const { return CAMERA; }

    void SetPosition(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void SetRotation(float rad = 0.0f);
    void SetZoomLevel(float zoom);
    void Reset(float x = 0.0f, float y = 0.0f, float z = 0.0f, float rad = 0.0f, float zoom = 1.0f);

    float GetZoomLevel() const { return ZOOM_LEVEL; }
    glm::vec4 GetBounds() const { return glm::vec4(-ASPECT_RATIO * ZOOM_LEVEL, ASPECT_RATIO * ZOOM_LEVEL, -ZOOM_LEVEL, ZOOM_LEVEL); }
};
}