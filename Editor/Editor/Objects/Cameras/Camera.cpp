#include "Camera.h"

#include "MPE/Input/Input.h"
#include "MPE/Log/GlobalLog.h"

namespace MPE
{
Camera::Camera(ECS::ECS& ecs) : Object(ecs)
{
    m_cameraComponent = NEWREF<ECS::CameraComponent>();
    m_cameraComponent = m_ECS.AddComponentToEntity(m_entity, m_cameraComponent);
}

Camera::Camera(ECS::ECS& ecs, const REF<ECS::CameraComponent>& cameraComponent) : Object(ecs)
{
    m_cameraComponent = m_ECS.AddComponentToEntity(m_entity, std::move(cameraComponent));
}

// Camera::Camera(ECS::ECS& ecs, const CameraComponent& cameraComponent) : Object(ecs)
// {
//     m_cameraComponent = m_ECS.AddComponentToEntity<ECS::CameraComponent>(m_entity, std::move(cameraComponent));
// }

// Need to make sure to explicitly remove the CameraComponent from the Entity Manager
Camera::~Camera()
{
    m_ECS.DestroyEntity(m_entity);
}

void Camera::OnUpdate(Time deltaTime)
{
    auto cameraPosition = this->GetPosition();
    auto cameraRotation = this->GetRotation();

    // CAMERA SPEED MULTIPLIER
    if (Input::IsKeyPressed(MPE_KEY_LEFT_SHIFT))
    {
        m_currentMovementSpeed = m_defaultMovementSpeed * 2;
        m_currentRotationSpeed = m_defaultRotationSpeed * 2;
    }
    else
    {
        m_currentMovementSpeed = m_defaultMovementSpeed;
        m_currentRotationSpeed = m_defaultRotationSpeed;
    }
    // CAMERA MOVEMENT
    if (Input::IsKeyPressed(MPE_KEY_A))
    {
        cameraPosition.x -= m_currentMovementSpeed * deltaTime;
    }
    if (Input::IsKeyPressed(MPE_KEY_D))
    {
        cameraPosition.x += m_currentMovementSpeed * deltaTime;
    }
    if (Input::IsKeyPressed(MPE_KEY_S))
    {
        cameraPosition.y -= m_currentMovementSpeed * deltaTime;
    }
    if (Input::IsKeyPressed(MPE_KEY_W))
    {
        cameraPosition.y += m_currentMovementSpeed * deltaTime;
    }
    // CAMERA ROTATION
    if (m_isRotationEnabled)
    {
        if (Input::IsKeyPressed(MPE_KEY_E))
        {
            cameraRotation -= m_currentRotationSpeed * deltaTime;
        }
        if (Input::IsKeyPressed(MPE_KEY_Q))
        {
            cameraRotation += m_currentRotationSpeed * deltaTime;
        }
    }

    // Set position and rotation
    this->SetPosition(cameraPosition);
    this->SetRotation(cameraRotation);
}

void Camera::OnRender(Camera& camera) {}

void Camera::OnImGuiRender() {}

void Camera::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseScrolledEvent>(MPE_BIND_EVENT_FUNCTION(Camera::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(MPE_BIND_EVENT_FUNCTION(Camera::OnWindowResized));
}

bool Camera::OnMouseScrolled(MouseScrolledEvent& e)
{
    float zoomLevel = 0.0f;

    switch (m_cameraComponent->GetMode())
    {
        case CameraMode::Orthographic:
            zoomLevel = m_cameraComponent->Orthographic_GetZoomLevel();
            zoomLevel -= e.GetYOffset() * m_currentZoomSpeed;
            zoomLevel = std::max(zoomLevel, m_maxZoomInLevel);
            m_cameraComponent->Orthographic_SetZoomLevel(zoomLevel);
            break;
        default:
            MPE_CORE_WARN("Camera mode not supported.");
            break;
    }
    return false;
}

bool Camera::OnWindowResized(WindowResizeEvent& e)
{
    float aspectRatio = 0.0f;
    switch (m_cameraComponent->GetMode())
    {
        case CameraMode::Orthographic:
            aspectRatio = (float) e.GetWidth() / (float) e.GetHeight();
            m_cameraComponent->Orthographic_SetAspectRatio(aspectRatio);
            break;
        default:
            MPE_CORE_WARN("Camera mode not supported.");
            break;
    }
    return false;
}

glm::mat4 Camera::GetProjection() const
{
    return m_cameraComponent->GetProjectionMatrix();
}

glm::vec4 Camera::GetBounds() const
{
    return m_cameraComponent->GetBounds();
}

glm::vec3 Camera::GetPosition() const
{
    return m_cameraComponent->GetPosition();
}

void Camera::SetPosition(const glm::vec3& position)
{
    m_cameraComponent->SetPosition(position);
}

float Camera::GetRotation() const
{
    return m_cameraComponent->GetRotation();
}

float Camera::GetFov() const
{
    switch (m_cameraComponent->GetMode())
    {
        case CameraMode::Perspective:
            return m_cameraComponent->Perspective_GetFov();
            break;
        default:
            MPE_CORE_WARN("Camera mode not supported.");
            return 0.0f;
            break;
    }
}

void Camera::SetFov(float fov)
{
    switch (m_cameraComponent->GetMode())
    {
        case CameraMode::Perspective:
            m_cameraComponent->Perspective_SetFov(fov);
            break;
        default:
            MPE_CORE_WARN("Camera mode not supported.");
            break;
    }
}

float Camera::GetAspectRatio() const
{
    switch (m_cameraComponent->GetMode())
    {
        case CameraMode::Perspective:
            return m_cameraComponent->Perspective_GetAspectRatio();
            break;
        case CameraMode::Orthographic:
            return m_cameraComponent->Orthographic_GetAspectRatio();
            break;
        default:
            MPE_CORE_WARN("Camera mode not supported.");
            return 0.0f;
            break;
    }
}

void Camera::SetAspectRatio(float aspectRatio)
{
    switch (m_cameraComponent->GetMode())
    {
        case CameraMode::Perspective:
            m_cameraComponent->Perspective_SetAspectRatio(aspectRatio);
            break;
        case CameraMode::Orthographic:
            m_cameraComponent->Orthographic_SetAspectRatio(aspectRatio);
            break;
        default:
            MPE_CORE_WARN("Camera mode not supported.");
            break;
    }
}

float Camera::GetNear() const
{
    switch (m_cameraComponent->GetMode())
    {
        case CameraMode::Perspective:
            return m_cameraComponent->Perspective_GetNear();
            break;
        case CameraMode::Orthographic:
            return m_cameraComponent->Orthographic_GetNear();
            break;
        default:
            MPE_CORE_WARN("Camera mode not supported.");
            return 0.0f;
            break;
    }
}

void Camera::SetNear(float nearClip)
{
    switch (m_cameraComponent->GetMode())
    {
        case CameraMode::Perspective:
            m_cameraComponent->Perspective_SetNear(nearClip);
            break;
        case CameraMode::Orthographic:
            m_cameraComponent->Orthographic_SetNear(nearClip);
            break;
        default:
            MPE_CORE_WARN("Camera mode not supported.");
            break;
    }
}

float Camera::GetFar() const
{
    switch (m_cameraComponent->GetMode())
    {
        case CameraMode::Perspective:
            return m_cameraComponent->Perspective_GetFar();
            break;
        case CameraMode::Orthographic:
            return m_cameraComponent->Orthographic_GetFar();
            break;
        default:
            MPE_CORE_WARN("Camera mode not supported.");
            return 0.0f;
            break;
    }
}

void Camera::SetFar(float farClip)
{
    switch (m_cameraComponent->GetMode())
    {
        case CameraMode::Perspective:
            m_cameraComponent->Perspective_SetFar(farClip);
            break;
        case CameraMode::Orthographic:
            m_cameraComponent->Orthographic_SetFar(farClip);
            break;
        default:
            MPE_CORE_WARN("Camera mode not supported.");
            break;
    }
}

void Camera::SetRotation(float rotation)
{
    m_cameraComponent->SetRotation(rotation);
}

float Camera::GetZoomLevel() const
{
    switch (m_cameraComponent->GetMode())
    {
        case CameraMode::Orthographic:
            return m_cameraComponent->Orthographic_GetZoomLevel();
            break;
        default:
            MPE_CORE_WARN("Camera mode not supported.");
            return 0.0f;
            break;
    }
}

void Camera::SetZoomLevel(float zoom)
{
    float zoomLevel = 0.0f;
    switch (m_cameraComponent->GetMode())
    {
        case CameraMode::Orthographic:
            zoomLevel = m_cameraComponent->Orthographic_GetZoomLevel();
            if (zoomLevel < m_maxZoomInLevel)
            {
                MPE_CORE_WARN("ZOOM LEVEL {0}f IS BELOW MAXIMUM ALLOWED {1}", zoomLevel, m_maxZoomInLevel);
                return;
            }
            else
            {
                m_cameraComponent->Orthographic_SetZoomLevel(zoomLevel);
            }
            break;
        default:
            MPE_CORE_WARN("Camera mode not supported.");
            break;
    }
}

}
