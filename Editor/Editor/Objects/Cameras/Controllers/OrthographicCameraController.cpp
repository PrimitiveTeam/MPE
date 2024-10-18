#include "OrthographicCameraController.h"

#include "MPE/Input/Input.h"

namespace MPE
{
OrthographicCameraController::OrthographicCameraController(ECS::ECS& ecs) : CameraController(ecs)
{
    m_orthographicaCamera = NEWREF<OrthographicCamera>(ecs, -1.0f, 1.0f, -1.0f, 1.0f);
    m_orthographicCameraControllerComponent =
        m_ECS.AddComponentToEntity(m_entity, NEWREF<ECS::OrthographicCameraControllerComponent>(m_orthographicaCamera->GetOrthographicCameraComponent()));
}

OrthographicCameraController::OrthographicCameraController(ECS::ECS& ecs, float aspectRatio) : CameraController(ecs)
{
    m_orthographicaCamera = NEWREF<OrthographicCamera>(ecs, -1.0f, 1.0f, -1.0f, 1.0f);
    m_orthographicCameraControllerComponent =
        m_ECS.AddComponentToEntity(m_entity, NEWREF<ECS::OrthographicCameraControllerComponent>(m_orthographicaCamera->GetOrthographicCameraComponent()));

    m_orthographicaCamera->GetOrthographicCameraComponent()->SetAspectRatio(aspectRatio);
    // set projection
    auto zoomLevel = m_orthographicCameraControllerComponent->GetZoomLevel();
    m_orthographicaCamera->GetOrthographicCameraComponent()->SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
}

OrthographicCameraController::OrthographicCameraController(ECS::ECS& ecs, REF<OrthographicCamera> camera) : CameraController(ecs, camera)
{
    m_orthographicaCamera = camera;
    m_orthographicCameraControllerComponent =
        m_ECS.AddComponentToEntity(m_entity, NEWREF<ECS::OrthographicCameraControllerComponent>(m_orthographicaCamera->GetOrthographicCameraComponent()));
}

OrthographicCameraController::OrthographicCameraController(ECS::ECS& ecs, REF<OrthographicCamera> camera, float aspectRatio) : CameraController(ecs, camera)
{
    m_orthographicaCamera = camera;
    m_orthographicCameraControllerComponent =
        m_ECS.AddComponentToEntity(m_entity, NEWREF<ECS::OrthographicCameraControllerComponent>(m_orthographicaCamera->GetOrthographicCameraComponent()));

    m_orthographicaCamera->GetOrthographicCameraComponent()->SetAspectRatio(aspectRatio);
    // set projection
    auto zoomLevel = m_orthographicCameraControllerComponent->GetZoomLevel();
    m_orthographicaCamera->GetOrthographicCameraComponent()->SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
}

void OrthographicCameraController::OnUpdate(Time deltaTime)
{
    const auto& cameraComponent = m_orthographicaCamera->GetOrthographicCameraComponent();
    // CAMERA SPEED MULTIPLIER
    if (Input::IsKeyPressed(MPE_KEY_LEFT_SHIFT))
    {
        const auto& defaultSpeed = m_orthographicCameraControllerComponent->GetCameraDefaultSpeed();
        m_orthographicCameraControllerComponent->SetCameraMovementSpeed(defaultSpeed[0] * 2);
        m_orthographicCameraControllerComponent->SetCameraRotationSpeed(defaultSpeed[1] * 2);
        // m_cameraMovementSpeed = m_cameraDefaultSpeed[0] * 2;
        // m_cameraRotationSpeed = m_cameraDefaultSpeed[1] * 2;
    }
    else
    {
        const auto& defaultSpeed = m_orthographicCameraControllerComponent->GetCameraDefaultSpeed();
        m_orthographicCameraControllerComponent->SetCameraMovementSpeed(defaultSpeed[0]);
        m_orthographicCameraControllerComponent->SetCameraRotationSpeed(defaultSpeed[1]);
        // m_cameraMovementSpeed = m_cameraDefaultSpeed[0];
        // m_cameraRotationSpeed = m_cameraDefaultSpeed[1];
    }
    // CAMERA MOVEMENT
    if (Input::IsKeyPressed(MPE_KEY_A))
    {
        auto cameraSpeed = m_orthographicCameraControllerComponent->GetCameraMovementSpeed();
        cameraComponent->ManipulatePosition().x -= cameraSpeed * deltaTime;
        // m_cameraPosition.x -= m_cameraMovementSpeed * deltaTime;
    }
    if (Input::IsKeyPressed(MPE_KEY_D))
    {
        auto cameraSpeed = m_orthographicCameraControllerComponent->GetCameraMovementSpeed();
        cameraComponent->ManipulatePosition().x += cameraSpeed * deltaTime;
        // m_cameraPosition.x += m_cameraMovementSpeed * deltaTime;
    }
    if (Input::IsKeyPressed(MPE_KEY_S))
    {
        auto cameraSpeed = m_orthographicCameraControllerComponent->GetCameraMovementSpeed();
        cameraComponent->ManipulatePosition().y -= cameraSpeed * deltaTime;
        // m_cameraPosition.y -= m_cameraMovementSpeed * deltaTime;
    }
    if (Input::IsKeyPressed(MPE_KEY_W))
    {
        auto cameraSpeed = m_orthographicCameraControllerComponent->GetCameraMovementSpeed();
        cameraComponent->ManipulatePosition().y += cameraSpeed * deltaTime;
        // m_cameraPosition.y += m_cameraMovementSpeed * deltaTime;
    }
    // m_camera.SetPosition(m_cameraPosition);
    // CAMERA ROTATION
    if (m_orthographicCameraControllerComponent->IsRotationEnabled())
    {
        if (Input::IsKeyPressed(MPE_KEY_E))
        {
            auto cameraRotationSpeed = m_orthographicCameraControllerComponent->GetCameraRotationSpeed();
            cameraComponent->ManipulateRotation() -= cameraRotationSpeed * deltaTime;
            // m_cameraRotation -= m_cameraRotationSpeed * deltaTime;
        }
        if (Input::IsKeyPressed(MPE_KEY_Q))
        {
            auto cameraRotationSpeed = m_orthographicCameraControllerComponent->GetCameraRotationSpeed();
            cameraComponent->ManipulateRotation() += cameraRotationSpeed * deltaTime;
            // m_cameraRotation += m_cameraRotationSpeed * deltaTime;
        }
        // m_camera.SetRotation(m_cameraRotation);
    }

    // m_orthographicCameraControllerComponent->SetCameraMovementSpeed(m_zoomLevel);
    // m_cameraMovementSpeed = m_zoomLevel;
};

void OrthographicCameraController::OnRender(Camera& camera) {};

void OrthographicCameraController::OnImGuiRender() {};

void OrthographicCameraController::OnEvent(Event& event)
{
    // m_orthographicCameraControllerComponent->OnEvent(event);
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseScrolledEvent>(MPE_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(MPE_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResized));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
    auto zoomLevel = m_orthographicCameraControllerComponent->GetZoomLevel();
    auto cameraZoomSpeed = m_orthographicCameraControllerComponent->GetCameraZoomSpeed();
    auto maxZoomLevel = m_orthographicCameraControllerComponent->GetMaxZoomLevel();
    zoomLevel -= e.GetYOffset() * cameraZoomSpeed;
    zoomLevel = std::max(zoomLevel, maxZoomLevel);
    m_orthographicCameraControllerComponent->SetZoomLevel(zoomLevel);

    auto cameraComponent = m_orthographicaCamera->GetOrthographicCameraComponent();

    auto aspectRatio = cameraComponent->GetAspectRatio();
    cameraComponent->SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);

    // m_zoomLevel -= e.GetYOffset() * m_cameraZoomSpeed;
    // m_zoomLevel = std::max(m_zoomLevel, m_maxZoomLevel);
    // auto aspectRation = m_orthographicCameraComponent->GetAspectRatio();
    // m_orthographicCameraComponent->SetProjection(-aspectRation * m_zoomLevel, aspectRation * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
    return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
{
    float aspectRatio = (float) e.GetWidth() / (float) e.GetHeight();
    auto cameraComponent = m_orthographicaCamera->GetOrthographicCameraComponent();
    auto zoomLevel = m_orthographicCameraControllerComponent->GetZoomLevel();

    cameraComponent->SetAspectRatio(aspectRatio);
    cameraComponent->SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);

    // m_orthographicCameraComponent->SetAspectRatio(aspectRatio);
    // m_orthographicCameraComponent->SetProjection(-aspectRatio * m_zoomLevel, aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
    return false;
}
}
