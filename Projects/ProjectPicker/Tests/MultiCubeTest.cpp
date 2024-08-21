#include "MultiCubeTest.h"
#include "MPE/MPEPCH.h"

#include <glm/gtc/matrix_transform.hpp>

#ifdef MPE_OPENGL
#    include "MPE/MPEGFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPEGFX_OPEN_GL_ES.h"
#endif

MultiCubeTest::MultiCubeTest() : Layer("Test"), m_clearColor{0.5f, 0.25f, 0.5f}, m_mainCamera(1280.0f / 720.0f, true)
{
    m_ECS = MPE::NEWREF<MPE::ECS::ECS>();
    // m_cube = MPE::NEWREF<MPE::Cube>(*m_ECS, glm::vec3(0.0f), glm::vec3(1.0f));

    float xDiff = 0.00f;
    float yDiff = 0.00f;
    float colorDiff = 0.0005f;
    for (int i = 0; i < 50; i++)
    {
        m_cubes.push_back(MPE::NEWREF<MPE::Cube>(*m_ECS, glm::vec3(0.0f + xDiff, 0.0f + yDiff, 0.0f), glm::vec3(1.0f)));
        xDiff += 0.05f;
        yDiff += 0.001f;
        m_cubes[i]->SetColor(glm::vec4(1.0f - colorDiff, 0.0f + colorDiff, 0.0f + colorDiff / 2.0f, 1.0f));
        colorDiff += 0.05f;
    }

    m_cubeDeltaPosition = new glm::vec3(0.0f);

    m_translationSystem = MPE::NEWREF<MPE::ECS::TranslationSystem>(m_cubeDeltaPosition);
    m_ECS->RegisterSystem(*m_translationSystem);
}

void MultiCubeTest::OnUpdate(MPE::Time deltaTime)
{
    MPE::RenderPrimitive::SetClearColor(glm::vec4(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    MPE::RenderPrimitive::Clear();

    m_ECS->RunSystems(deltaTime);

    if (m_isTranslationSystemActive)
    {
        for (auto &cube : m_cubes)
        {
            if (cube->GetPosition().x > 2.0f)
            {
                cube->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
            }
        }
    }

    for (auto &cube : m_cubes)
    {
        cube->OnUpdate(deltaTime);
        cube->OnRender(m_mainCamera);
    }
}

void MultiCubeTest::OnImGuiRender()
{
    for (auto &cube : m_cubes)
    {
        cube->OnImGuiRender();
    }

    ImGui::Begin("Toggle System");

    if (ImGui::Button("Toggle Translation System"))
    {
        ToggleTranslationSystem();
    }

    ImGui::SliderFloat("Transition X speed", &m_cubeDeltaPosition->x, 0.0f, 1.0f);

    ImGui::End();
}

void MultiCubeTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(MultiCubeTest::OnKeyPressedEvent));
    m_mainCamera.OnEvent(event);
}

bool MultiCubeTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}

void MultiCubeTest::ToggleTranslationSystem()
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