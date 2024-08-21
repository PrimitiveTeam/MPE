#include "CubeAbstractionTest.h"
#include "MPE/MPEPCH.h"

#include <glm/gtc/matrix_transform.hpp>

#ifdef MPE_OPENGL
#    include "MPE/MPEGFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPEGFX_OPEN_GL_ES.h"
#endif

CubeAbstractionTest::CubeAbstractionTest() : Layer("Test"), m_clearColor{0.5f, 0.25f, 0.5f}, m_mainCamera(1280.0f / 720.0f, true)
{
    m_ECS = MPE::NEWREF<MPE::ECS::ECS>();
    m_cube = MPE::NEWREF<MPE::Cube>(*m_ECS, glm::vec3(0.0f), glm::vec3(1.0f));
    m_cubeDeltaPosition = new glm::vec3(0.0f);

    m_translationSystem = MPE::NEWREF<MPE::ECS::TranslationSystem>(m_cubeDeltaPosition);
    m_ECS->RegisterSystem(*m_translationSystem);
}

void CubeAbstractionTest::OnUpdate(MPE::Time deltaTime)
{
    MPE::RenderPrimitive::SetClearColor(glm::vec4(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    MPE::RenderPrimitive::Clear();

    m_ECS->RunSystems();

    if (m_isTranslationSystemActive)
    {
        if (m_cube->GetPosition().x > 2.0f)
        {
            m_cube->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
        }
    }

    m_cube->OnUpdate(deltaTime);
    m_cube->OnRender(m_mainCamera);
}

void CubeAbstractionTest::OnImGuiRender()
{
    m_cube->OnImGuiRender();

    ImGui::Begin("Toggle Translation System");

    if (ImGui::Button("Toggle Translation System"))
    {
        ToggleTranslationSystem();
    }

    ImGui::End();
}

void CubeAbstractionTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(CubeAbstractionTest::OnKeyPressedEvent));
    m_mainCamera.OnEvent(event);
}

bool CubeAbstractionTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}

void CubeAbstractionTest::ToggleTranslationSystem()
{
    if (!m_isTranslationSystemActive)
    {
        m_cubeDeltaPosition->x = 0.0001f;
        m_isTranslationSystemActive = true;
    }
    else
    {
        m_cubeDeltaPosition->x = 0.0f;
        m_isTranslationSystemActive = false;
    }
}