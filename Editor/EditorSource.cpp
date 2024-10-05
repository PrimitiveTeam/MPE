#include "EditorSource.h"

EditorCoreLayer::EditorCoreLayer() : Layer("EditorCoreLayer")
{
    m_sceneManager = MPE::NEWSCOPE<MPE::SceneManager>();
    m_scene = MPE::NEWREF<MPE::Scene>();
    m_sceneManager->PushScene(m_scene);
}

void EditorCoreLayer::OnAttach() {}

void EditorCoreLayer::OnDetach() {}

void EditorCoreLayer::OnUpdate(MPE::Time deltaTime)
{
    m_sceneManager->OnUpdate(deltaTime);
    m_sceneManager->OnRender();
}

void EditorCoreLayer::OnImGuiRender()
{
    m_sceneManager->OnImGuiRender();
}

void EditorCoreLayer::OnEvent(MPE::Event& event)
{
    m_sceneManager->OnEvent(event);
}