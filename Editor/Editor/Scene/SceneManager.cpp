#include "SceneManager.h"

namespace MPE
{
SceneManager::SceneManager() : m_scenes() {}

void SceneManager::PushScene(REF<Scene> scene)
{
    m_scenes.push(scene);
}

void SceneManager::PopScene()
{
    m_scenes.pop();
}

void SceneManager::OnUpdate(Time deltaTime)
{
    m_scenes.top()->OnUpdate(deltaTime);
}

void SceneManager::OnRender()
{
    m_scenes.top()->OnRender();
}

void SceneManager::OnImGuiRender()
{
    m_scenes.top()->OnImGuiRender();
}

void SceneManager::OnEvent(Event& event)
{
    m_scenes.top()->OnEvent(event);
}

}