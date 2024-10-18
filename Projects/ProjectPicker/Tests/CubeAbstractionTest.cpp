#include "CubeAbstractionTest.h"
#include "MPE/MPEPCH.h"

#include "MPE/Vendor/GLM/GLM.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#endif

CubeAbstractionTest::CubeAbstractionTest() : Layer("Test"), m_clearColor{0.5f, 0.25f, 0.5f}
{
    m_ECS = MPE::NEWREF<MPE::ECS::ECS>();

    MPE::REF<MPE::ECS::CameraComponent> cameraComponent = MPE::NEWREF<MPE::ECS::CameraComponent>();
    cameraComponent->SetMode(MPE::CameraMode::Orthographic, false);
    cameraComponent->SetOrthographic(1280.0f / 720.0f, 1.0f, -1.0f, 1.0f);
    m_mainCamera = MPE::NEWREF<MPE::Camera>(*m_ECS, cameraComponent);

    m_cube = MPE::NEWREF<MPE::Cube>(*m_ECS, glm::vec3(0.0f), glm::vec3(1.0f));
    m_cubeDeltaPosition = new glm::vec3(0.0f);

    m_transformSystem = MPE::NEWREF<MPE::ECS::TransformSystem>(m_cubeDeltaPosition);
    m_ECS->RegisterSystem(*m_transformSystem);

    m_renderSystem = MPE::NEWREF<MPE::ECS::RenderSystem>();
    m_ECS->RegisterSystem(*m_renderSystem, m_mainCamera);
}

void CubeAbstractionTest::OnUpdate(MPE::Time deltaTime)
{
    MPE::RenderPrimitive::SetClearColor(glm::vec4(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    MPE::RenderPrimitive::Clear();

    m_ECS->RunSystems(deltaTime);

    if (m_isTransformSystemActive)
    {
        auto &position = m_cube->GetTransform().position;
        if (position.x > 2.0f)
        {
            position = glm::vec3(-2.0f, 0.0f, 0.0f);
        }
    }

    m_cube->OnUpdate(deltaTime);
    // m_cube->OnRender(m_mainCamera.GetCamera());
    m_ECS->RunSystems(m_mainCamera);
}

void CubeAbstractionTest::OnImGuiRender()
{
    m_cube->OnImGuiRender();

    ImGui::Begin("Toggle Translation System");

    if (ImGui::Button("Toggle Translation System"))
    {
        ToggleTransformSystem();
    }

    ImGui::End();
}

void CubeAbstractionTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(CubeAbstractionTest::OnKeyPressedEvent));
    m_mainCamera->OnEvent(event);
}

bool CubeAbstractionTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}

void CubeAbstractionTest::ToggleTransformSystem()
{
    if (!m_isTransformSystemActive)
    {
        m_cubeDeltaPosition->x = 1.0f;
        m_isTransformSystemActive = true;
    }
    else
    {
        m_cubeDeltaPosition->x = 0.0f;
        m_isTransformSystemActive = false;
    }
}