#include "SceneTest.h"
#include "MPE/MPEPCH.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#ifdef MPE_OPENGL
#    include "MPE/MPEGFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPEGFX_OPEN_GL_ES.h"
#endif

SceneTest::SceneTest() : Layer("Editor")
{
    m_sceneManager = MPE::NEWSCOPE<MPE::SceneManager>();
    m_scene = MPE::NEWREF<MPE::Scene>();
    m_sceneManager->PushScene(m_scene);

    auto &object = m_scene->CreateObject<MPE::Cube>();
    // auto object = MPE::NEWREF<MPE::Cube>(m_scene->GetECS());
    // MPE::Cube *cube = new MPE::Cube(*m_scene->GetECS());
}

void SceneTest::OnUpdate(MPE::Time deltaTime)
{
    // MPE::RenderPrimitive::SetClearColor(glm::vec4(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    // MPE::RenderPrimitive::Clear();
    m_sceneManager->OnUpdate(deltaTime);
    m_sceneManager->OnRender();
}

void SceneTest::OnImGuiRender()
{
    m_sceneManager->OnImGuiRender();
}

void SceneTest::OnEvent(MPE::Event &event)
{
    m_sceneManager->OnEvent(event);
    // MPE::EventDispatcher dispatcher(event);
    // dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(SceneTest::OnKeyPressedEvent));
}

bool SceneTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}