#include "StaticOrthographicCamera.h"
#include "MPEPCH.h"

#include "MPE/Input/Input.h"
#include "MPE/Log/GlobalLog.h"

namespace MPE
{
StaticOrthographicCamera::StaticOrthographicCamera(float aspectRatio, bool rotation)
    : m_aspectRatio(aspectRatio),
      m_camera(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel),
      m_rotation(rotation),
      m_cameraDefaultSpeed{// CAMERA MOVEMENT SPEED
                           1.0f,
                           // CAMERA ROTATION SPEED
                           30.0f},
      m_cameraMovementSpeed(m_cameraDefaultSpeed[0]),
      m_cameraRotationSpeed(m_cameraDefaultSpeed[1])
{
}

void StaticOrthographicCamera::OnUpdate(Time deltaTime)
{
    // // CAMERA SPEED MULTIPLIER
    // if (Input::IsKeyPressed(MPE_KEY_LEFT_SHIFT))
    // {
    //     m_cameraMovementSpeed = m_cameraDefaultSpeed[0] * 2;
    //     m_cameraRotationSpeed = m_cameraDefaultSpeed[1] * 2;
    // }
    // else
    // {
    //     m_cameraMovementSpeed = m_cameraDefaultSpeed[0];
    //     m_cameraRotationSpeed = m_cameraDefaultSpeed[1];
    // }
    // // CAMERA MOVEMENT
    // if (Input::IsKeyPressed(MPE_KEY_A))
    // {
    //     CAMERA_POSITION.x -= m_cameraMovementSpeed * deltaTime;
    // }
    // if (Input::IsKeyPressed(MPE_KEY_D))
    // {
    //     CAMERA_POSITION.x += m_cameraMovementSpeed * deltaTime;
    // }
    // if (Input::IsKeyPressed(MPE_KEY_S))
    // {
    //     CAMERA_POSITION.y -= m_cameraMovementSpeed * deltaTime;
    // }
    // if (Input::IsKeyPressed(MPE_KEY_W))
    // {
    //     CAMERA_POSITION.y += m_cameraMovementSpeed * deltaTime;
    // }
    // CAMERA.SetPosition(CAMERA_POSITION);
    // // CAMERA ROTATION
    // if (ROTATION)
    // {
    //     if (Input::IsKeyPressed(MPE_KEY_E))
    //     {
    //         CAMERA_ROTATION -= m_cameraRotationSpeed * deltaTime;
    //     }
    //     if (Input::IsKeyPressed(MPE_KEY_Q))
    //     {
    //         CAMERA_ROTATION += m_cameraRotationSpeed * deltaTime;
    //     }
    //     CAMERA.SetRotation(CAMERA_ROTATION);
    // }

    // m_cameraMovementSpeed = ZOOM_LEVEL;
}

void StaticOrthographicCamera::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    // dispatcher.Dispatch<MouseScrolledEvent>(MPE_BIND_EVENT_FUNCTION(StaticOrthographicCamera::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(MPE_BIND_EVENT_FUNCTION(StaticOrthographicCamera::OnWindowResized));
}

bool StaticOrthographicCamera::OnMouseScrolled(MouseScrolledEvent &e)
{
    m_zoomLevel -= e.GetYOffset() * m_cameraZoomSpeed;
    m_zoomLevel = std::max(m_zoomLevel, m_maxZoomLevel);
    m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
    return false;
}

bool StaticOrthographicCamera::OnWindowResized(WindowResizeEvent &e)
{
    m_aspectRatio = (float) e.GetWidth() / (float) e.GetHeight();
    m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
    return false;
}

void StaticOrthographicCamera::SetPosition(float x, float y, float z)
{
    m_cameraPosition = {x, y, z};
    m_camera.SetPosition(m_cameraPosition);
}

void StaticOrthographicCamera::SetRotation(float rad)
{
    m_rotation = rad;
    m_camera.SetRotation(m_rotation);
}

void StaticOrthographicCamera::SetZoomLevel(float zoom)
{
    if (zoom < m_maxZoomLevel)
    {
        MPE_CORE_WARN("ZOOM LEVEL {0}f IS BELOW MAXIMUM ALLOWED {1}", zoom, m_maxZoomLevel);
    }
    else
    {
        m_zoomLevel = zoom;
        m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
    }
}

void StaticOrthographicCamera::Reset(float x, float y, float z, float rad, float zoom)
{
    SetPosition(x, y, z);
    SetRotation(rad);
    SetZoomLevel(zoom);
}
}