#include "SphereTest.h"
#include "MPE/MPEPCH.h"

#include "MPE/Vendor/GLM/GLM.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#endif

SphereTest::SphereTest() : Layer("Test"), m_clearColor{0.5f, 0.25f, 0.5f}
{
    m_ECS = MPE::NEWREF<MPE::ECS::ECS>();
    m_mainCamera = MPE::NEWREF<MPE::OrthographicCameraController>(*m_ECS, 1280.0f / 720.0f);

    m_sphere = MPE::NEWREF<MPE::Sphere>(*m_ECS);
    m_sphereDeltaPosition = new glm::vec3(0.0f);

    m_transformSystem = MPE::NEWREF<MPE::ECS::TransformSystem>(m_sphereDeltaPosition);
    m_ECS->RegisterSystem(*m_transformSystem);

    m_renderSystem = MPE::NEWREF<MPE::ECS::RenderSystem>();
    m_ECS->RegisterSystem(*m_renderSystem, m_mainCamera->GetOrthographicCamera());
}

void SphereTest::OnUpdate(MPE::Time deltaTime)
{
    MPE::RenderPrimitive::SetClearColor(glm::vec4(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    MPE::RenderPrimitive::Clear();

    m_ECS->RunSystems(deltaTime);

    if (m_isTransformSystemActive)
    {
        auto &position = m_sphere->GetTransform().position;
        if (position.x > 2.0f)
        {
            position = glm::vec3(-2.0f, 0.0f, 0.0f);
        }
    }

    m_sphere->OnUpdate(deltaTime);
    // m_sphere->OnRender(m_mainCamera.GetCamera());
    m_ECS->RunSystems(m_mainCamera->GetOrthographicCamera());
}

void SphereTest::OnImGuiRender()
{
    m_sphere->OnImGuiRender();

    ImGui::Begin("Toggle Translation System");

    if (ImGui::Button("Toggle Translation System"))
    {
        ToggleTransformSystem();
    }

    ImGui::End();
}

void SphereTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(SphereTest::OnKeyPressedEvent));
    m_mainCamera->OnEvent(event);
}

bool SphereTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}

void SphereTest::ToggleTransformSystem()
{
    if (!m_isTransformSystemActive)
    {
        m_sphereDeltaPosition->x = 1.0f;
        m_isTransformSystemActive = true;
    }
    else
    {
        m_sphereDeltaPosition->x = 0.0f;
        m_isTransformSystemActive = false;
    }
}