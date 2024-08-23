#include "Scene.h"

#include "MPE/Renderer/RenderPrimitive.h"

namespace MPE
{
Scene::Scene() : m_sceneName("Default Scene"), m_ECS(NEWREF<ECS::ECS>()), m_mainCamera(nullptr), m_objects()
{
    m_mainCamera = NEWREF<StaticOrthographicCamera>(1280.0f / 720.0f, true);
}

Scene::Scene(const std::string& sceneName) : m_sceneName(sceneName), m_ECS(NEWREF<ECS::ECS>()), m_mainCamera(nullptr), m_objects()
{
    m_mainCamera = NEWREF<StaticOrthographicCamera>(1280.0f / 720.0f, true);
}

void Scene::DestroyEntity(ECS::Entity entity)
{
    m_ECS->DestroyEntity(entity);
    auto it = std::partition(m_objects.begin(), m_objects.end(), [entity](REF<Object>& obj) { return obj->GetEntity() != entity; });
    m_objects.erase(it, m_objects.end());
}

void Scene::OnUpdate(Time deltaTime)
{
    MPE::RenderPrimitive::Clear();

    m_ECS->RunSystems(deltaTime);
    for (auto& obj : m_objects)
    {
        obj->OnUpdate(deltaTime);
    }
}

void Scene::OnRender()
{
    for (auto& obj : m_objects)
    {
        obj->OnRender(m_mainCamera->GetCamera());
    }
}

void Scene::OnImGuiRender()
{
    for (auto& obj : m_objects)
    {
        obj->OnImGuiRender();
    }
}

void Scene::OnEvent(Event& event)
{
    for (auto& obj : m_objects)
    {
        obj->OnEvent(event);
    }
}

void Scene::SetMainCamera(REF<StaticOrthographicCamera> camera)
{
    m_mainCamera = camera;
}
}