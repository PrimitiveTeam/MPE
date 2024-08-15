#include "OrthographicCameraController.h"
#include "MPEPCH.h"

#include "MPE/Input/Input.h"
#include "MPE/Log/GlobalLog.h"

namespace MPE
{
OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
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

void OrthographicCameraController::OnUpdate(Time deltaTime)
{
    // CAMERA SPEED MULTIPLIER
    if (Input::IsKeyPressed(MPE_KEY_LEFT_SHIFT))
    {
        m_cameraMovementSpeed = m_cameraDefaultSpeed[0] * 2;
        m_cameraRotationSpeed = m_cameraDefaultSpeed[1] * 2;
    }
    else
    {
        m_cameraMovementSpeed = m_cameraDefaultSpeed[0];
        m_cameraRotationSpeed = m_cameraDefaultSpeed[1];
    }
    // CAMERA MOVEMENT
    if (Input::IsKeyPressed(MPE_KEY_A))
    {
        m_cameraPosition.x -= m_cameraMovementSpeed * deltaTime;
    }
    if (Input::IsKeyPressed(MPE_KEY_D))
    {
        m_cameraPosition.x += m_cameraMovementSpeed * deltaTime;
    }
    if (Input::IsKeyPressed(MPE_KEY_S))
    {
        m_cameraPosition.y -= m_cameraMovementSpeed * deltaTime;
    }
    if (Input::IsKeyPressed(MPE_KEY_W))
    {
        m_cameraPosition.y += m_cameraMovementSpeed * deltaTime;
    }
    m_camera.SetPosition(m_cameraPosition);
    // CAMERA ROTATION
    if (m_rotation)
    {
        if (Input::IsKeyPressed(MPE_KEY_E))
        {
            m_cameraRotation -= m_cameraRotationSpeed * deltaTime;
        }
        if (Input::IsKeyPressed(MPE_KEY_Q))
        {
            m_cameraRotation += m_cameraRotationSpeed * deltaTime;
        }
        m_camera.SetRotation(m_cameraRotation);
    }

    m_cameraMovementSpeed = m_zoomLevel;
}

void OrthographicCameraController::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseScrolledEvent>(MPE_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(MPE_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResized));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e)
{
    m_zoomLevel -= e.GetYOffset() * m_cameraZoomSpeed;
    m_zoomLevel = std::max(m_zoomLevel, m_maxZoomLevel);
    m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
    return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &e)
{
    m_aspectRatio = (float) e.GetWidth() / (float) e.GetHeight();
    m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
    return false;
}

void OrthographicCameraController::SetPosition(float x, float y, float z)
{
    m_cameraPosition = {x, y, z};
    m_camera.SetPosition(m_cameraPosition);
}

void OrthographicCameraController::SetRotation(float rad)
{
    m_cameraRotation = rad;
    m_camera.SetRotation(m_cameraRotation);
}

void OrthographicCameraController::SetZoomLevel(float zoom)
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

void OrthographicCameraController::Reset(float x, float y, float z, float rad, float zoom)
{
    SetPosition(x, y, z);
    SetRotation(rad);
    SetZoomLevel(zoom);
}
}