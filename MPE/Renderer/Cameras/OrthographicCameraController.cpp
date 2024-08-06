#include "OrthographicCameraController.h"
#include "MPEPCH.h"

#include "MPE/Input/Input.h"
#include "MPE/Log/GlobalLog.h"

namespace MPE
{
OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
    : ASPECT_RATIO(aspectRatio),
      CAMERA(-ASPECT_RATIO * ZOOM_LEVEL, ASPECT_RATIO * ZOOM_LEVEL, -ZOOM_LEVEL, ZOOM_LEVEL),
      ROTATION(rotation),
      CAMERA_DEFAULT_SPEEDS{// CAMERA MOVEMENT SPEED
                            1.0f,
                            // CAMERA ROTATION SPEED
                            30.0f},
      CAMERA_MOVEMENT_SPEED(CAMERA_DEFAULT_SPEEDS[0]),
      CAMERA_ROTATION_SPEED(CAMERA_DEFAULT_SPEEDS[1])
{
}

void OrthographicCameraController::OnUpdate(Time deltatime)
{
    // CAMERA SPEED MULTIPLIER
    if (Input::IsKeyPressed(MPE_KEY_LEFT_SHIFT))
    {
        CAMERA_MOVEMENT_SPEED = CAMERA_DEFAULT_SPEEDS[0] * 2;
        CAMERA_ROTATION_SPEED = CAMERA_DEFAULT_SPEEDS[1] * 2;
    }
    else
    {
        CAMERA_MOVEMENT_SPEED = CAMERA_DEFAULT_SPEEDS[0];
        CAMERA_ROTATION_SPEED = CAMERA_DEFAULT_SPEEDS[1];
    }
    // CAMERA MOVEMENT
    if (Input::IsKeyPressed(MPE_KEY_A))
    {
        CAMERA_POSITION.x -= CAMERA_MOVEMENT_SPEED * deltatime;
    }
    if (Input::IsKeyPressed(MPE_KEY_D))
    {
        CAMERA_POSITION.x += CAMERA_MOVEMENT_SPEED * deltatime;
    }
    if (Input::IsKeyPressed(MPE_KEY_S))
    {
        CAMERA_POSITION.y -= CAMERA_MOVEMENT_SPEED * deltatime;
    }
    if (Input::IsKeyPressed(MPE_KEY_W))
    {
        CAMERA_POSITION.y += CAMERA_MOVEMENT_SPEED * deltatime;
    }
    CAMERA.SetPosition(CAMERA_POSITION);
    // CAMERA ROTATION
    if (ROTATION)
    {
        if (Input::IsKeyPressed(MPE_KEY_E))
        {
            CAMERA_ROTATION -= CAMERA_ROTATION_SPEED * deltatime;
        }
        if (Input::IsKeyPressed(MPE_KEY_Q))
        {
            CAMERA_ROTATION += CAMERA_ROTATION_SPEED * deltatime;
        }
        CAMERA.SetRotation(CAMERA_ROTATION);
    }

    CAMERA_MOVEMENT_SPEED = ZOOM_LEVEL;
}

void OrthographicCameraController::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseScrolledEvent>(MPE_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(MPE_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResized));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e)
{
    ZOOM_LEVEL -= e.GetYOffset() * CAMERA_ZOOM_SPEED;
    ZOOM_LEVEL = std::max(ZOOM_LEVEL, MAX_ZOOM_LEVEL);
    CAMERA.SetProjection(-ASPECT_RATIO * ZOOM_LEVEL, ASPECT_RATIO * ZOOM_LEVEL, -ZOOM_LEVEL, ZOOM_LEVEL);
    return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &e)
{
    ASPECT_RATIO = (float) e.GetWidth() / (float) e.GetHeight();
    CAMERA.SetProjection(-ASPECT_RATIO * ZOOM_LEVEL, ASPECT_RATIO * ZOOM_LEVEL, -ZOOM_LEVEL, ZOOM_LEVEL);
    return false;
}

void OrthographicCameraController::SetPosition(float x, float y, float z)
{
    CAMERA_POSITION = {x, y, z};
    CAMERA.SetPosition(CAMERA_POSITION);
}

void OrthographicCameraController::SetRotation(float rad)
{
    CAMERA_ROTATION = rad;
    CAMERA.SetRotation(CAMERA_ROTATION);
}

void OrthographicCameraController::SetZoomLevel(float zoom)
{
    if (zoom < MAX_ZOOM_LEVEL)
    {
        MPE_CORE_WARN("ZOOM LEVEL {0}f IS BELOW MAXIMUM ALLOWED {1}", zoom, MAX_ZOOM_LEVEL);
    }
    else
    {
        ZOOM_LEVEL = zoom;
        CAMERA.SetProjection(-ASPECT_RATIO * ZOOM_LEVEL, ASPECT_RATIO * ZOOM_LEVEL, -ZOOM_LEVEL, ZOOM_LEVEL);
    }
}

void OrthographicCameraController::Reset(float x, float y, float z, float rad, float zoom)
{
    SetPosition(x, y, z);
    SetRotation(rad);
    SetZoomLevel(zoom);
}
}