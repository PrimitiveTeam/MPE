#include "MultiCubeTest.h"
#include "MPE/MPEPCH.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#ifdef MPE_OPENGL
#    include "MPE/MPEGFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPEGFX_OPEN_GL_ES.h"
#endif

// void TransformSystemUpdate(MPE::ECS::TransformSystem &system, MPE::ECS::EntityRegistry &registry, float deltaTime)
// {
//     system(registry, deltaTime);
// }

MultiCubeTest::MultiCubeTest() : Layer("Test"), m_clearColor{0.5f, 0.25f, 0.5f}, m_mainCamera(1280.0f / 720.0f, true)
{
    auto& ECS = MPE::ECS::ECS::GetInstance();
    // m_cube = MPE::NEWREF<MPE::Cube>(*ECS, glm::vec3(0.0f), glm::vec3(1.0f));

    float xDiff = 0.00f;
    float yDiff = 0.00f;
    float colorDiff = 0.0005f;
    for (int i = 0; i < 50; i++)
    {
        m_cubes.push_back(MPE::NEWREF<MPE::Cube>(ECS, glm::vec3(0.0f + xDiff, 0.0f + yDiff, 0.0f), glm::vec3(1.0f)));
        xDiff += 0.05f;
        yDiff += 0.001f;
        m_cubes[i]->SetColor(glm::vec4(1.0f - colorDiff, 0.0f + colorDiff, 0.0f + colorDiff / 2.0f, 1.0f));
        colorDiff += 0.03f;
    }

    m_cubeDeltaPosition = new glm::vec3(0.0f);
    m_cubeDeltaRotation = new glm::vec3(0.0f);

    // m_transformSystem = MPE::NEWREF<MPE::ECS::TransformSystem>(m_cubeDeltaPosition, nullptr);
    m_transformSystem = MPE::NEWREF<MPE::ECS::TransformSystem>(m_cubeDeltaPosition, m_cubeDeltaRotation);
    // ECS->RegisterSystem(TransformSystemUpdate, *m_transformSystem);
    ECS.RegisterSystem(*m_transformSystem);

    // m_cubeDeltaRotation->x = 50.0f;
    // m_cubeDeltaRotation->y = 25.0f;
    // m_cubeDeltaRotation->z = 30.0f;
    // m_isTransformSystemActive = true;

    ToggleTransformSystem();
}

void MultiCubeTest::OnUpdate(MPE::Time deltaTime)
{
    MPE::RenderPrimitive::SetClearColor(glm::vec4(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    MPE::RenderPrimitive::Clear();

    MPE::ECS::ECS::GetInstance().RunSystems(deltaTime);

    if (m_isTransformSystemActive)
    {
        for (auto &cube : m_cubes)
        {
            auto &position = cube->GetTransform().position;
            if (position.x > 2.0f)
            {
                position = glm::vec3(-2.0f, 0.0f, 0.0f);
            }
        }
    }

    // IterativeRotate(deltaTime);

    for (auto &cube : m_cubes)
    {
        cube->OnUpdate(deltaTime);
        cube->OnRender(m_mainCamera);
    }
}

void MultiCubeTest::OnImGuiRender()
{
    m_cubes[0]->OnImGuiRender();

    ImGui::Begin("Toggle System");

    if (ImGui::Button("Toggle Translation System"))
    {
        ToggleTransformSystem();
    }

    if (m_isTransformSystemActive)
    {
        ImGui::SliderFloat("Transition X speed", &m_cubeDeltaPosition->x, 0.0f, 1.0f);
        ImGui::SliderFloat("Rotation X speed", &m_cubeDeltaRotation->x, 0.0f, 100.0f);
        ImGui::SliderFloat("Rotation Y speed", &m_cubeDeltaRotation->y, 0.0f, 100.0f);
        ImGui::SliderFloat("Rotation Z speed", &m_cubeDeltaRotation->z, 0.0f, 100.0f);
    }

    if (ImGui::Button("Test Query"))
    {
        auto entities = MPE::ECS::ECS::GetInstance().FindEntityByName("Cube");
        for (auto &entity : entities)
        {
            MPE_INFO("Entity: {0}", entity);
        }
    }

    // rename entity 0
    std::string text = MPE::ECS::ECS::GetInstance().GetComponent<MPE::ECS::TagComponent>(0).name;
    static char buffer[256];
    strncpy(buffer, text.c_str(), sizeof(buffer));
    buffer[sizeof(buffer) - 1] = 0;

    if (ImGui::InputText("Entity 0", buffer, sizeof(buffer)))
    {
        text = std::string(buffer);
        MPE::ECS::ECS::GetInstance().GetComponent<MPE::ECS::TagComponent>(0).name = text;
    }

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

void MultiCubeTest::ToggleTransformSystem()
{
    if (!m_isTransformSystemActive)
    {
        m_cubeDeltaPosition->x = 0.5f;
        m_cubeDeltaRotation->x = 50.0f;
        m_cubeDeltaRotation->y = 25.0f;
        m_cubeDeltaRotation->z = 30.0f;
        m_isTransformSystemActive = true;
    }
    else
    {
        m_cubeDeltaPosition->x = 0.0f;
        m_cubeDeltaRotation->x = 0.0f;
        m_cubeDeltaRotation->y = 0.0f;
        m_cubeDeltaRotation->z = 0.0f;
        m_isTransformSystemActive = false;
    }
}

// For profiling ECS system vs stack run
#include "MPE/Profiling/_PROFILING.h"
void MultiCubeTest::IterativeRotate(MPE::Time deltaTime)
{
    MPE_PROFILE_FUNCTION();

    float deltaSeconds = deltaTime.GetSeconds();

    // rotate all cubes iteratively
    for (auto &cube : m_cubes)
    {
        auto &transform = cube->GetTransform();

        // do the calc
        // MPE_TRACE("[BEFORE] Rotation: {0}", glm::to_string(transform.rotation));
        // MPE_TRACE("CALC: {0}", glm::to_string((*m_cubeDeltaRotation) * (float) deltaTime));
        glm::quat deltaRotationQuat = MPE::ECS::RotationUtilities::EulerToQuaternion((*m_cubeDeltaRotation) * deltaSeconds);
        // MPE_TRACE("DELTA: {0}", glm::to_string(deltaRotationQuat));
        transform.rotation = deltaRotationQuat * transform.rotation;
        transform.rotation = glm::normalize(transform.rotation);
        // MPE_TRACE("[AFTER] Rotation: {0}", glm::to_string(transform.rotation));
    }
}