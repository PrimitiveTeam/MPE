#include "Scene.h"

#include "MPE/Renderer/RenderPrimitive.h"

#include "Editor/Editor/ECS/Components/Meshes/MeshRegenerator.h"
#include "Editor/Editor/ECS/Components/Meshes/MeshComponent.h"
#include "Editor/Editor/ECS/Components/Meshes/Metadata/SphereMetadataComponent.h"
#include "Editor/Editor/ECS/Components/Graphical/RenderComponent.h"

namespace MPE
{
Scene::Scene() : m_sceneName("Default Scene"), m_ECS(NEWREF<ECS::ECS>()), m_mainCamera(nullptr), m_objects(NEWREF<std::vector<REF<Object>>>())
{
    m_mainCamera = NEWREF<StaticOrthographicCamera>(1280.0f / 720.0f, true);

    m_renderSystem = MPE::NEWREF<MPE::ECS::RenderSystem>();
    m_ECS->RegisterSystem(*m_renderSystem, m_mainCamera->GetCamera());
}

Scene::Scene(const std::string& sceneName)
    : m_sceneName(sceneName), m_ECS(NEWREF<ECS::ECS>()), m_mainCamera(nullptr), m_objects(NEWREF<std::vector<REF<Object>>>())
{
    m_mainCamera = NEWREF<StaticOrthographicCamera>(1280.0f / 720.0f, true);

    m_renderSystem = MPE::NEWREF<MPE::ECS::RenderSystem>();
    m_ECS->RegisterSystem(*m_renderSystem, m_mainCamera->GetCamera());
}

void Scene::DestroyEntity(ECS::Entity entity)
{
    m_ECS->DestroyEntity(entity);
    auto it = std::partition(m_objects->begin(), m_objects->end(), [entity](REF<Object>& obj) { return obj->GetEntity() != entity; });
    m_objects->erase(it, m_objects->end());
}

void Scene::OnUpdate(Time deltaTime)
{
    CheckIfEntitiesAreDirty();
    MPE::RenderPrimitive::Clear();

    m_ECS->RunSystems(deltaTime);
    for (auto& obj : *m_objects)
    {
        obj->OnUpdate(deltaTime);
    }
}

void Scene::OnRender()
{
    m_ECS->RunSystems(m_mainCamera->GetCamera());
    for (auto& obj : *m_objects)
    {
        obj->OnRender(m_mainCamera->GetCamera());
    }
}

void Scene::OnImGuiRender()
{
    for (auto& obj : *m_objects)
    {
        obj->OnImGuiRender();
    }
}

void Scene::OnEvent(Event& event)
{
    for (auto& obj : *m_objects)
    {
        obj->OnEvent(event);
    }
}

void Scene::CheckIfEntitiesAreDirty()
{
    for (auto& obj : *m_objects)
    {
        auto entity = obj->GetEntity();

        // Check if the entity has the required components
        if (m_ECS->HasComponent<ECS::MeshComponent>(entity) && m_ECS->HasComponent<ECS::RenderComponent>(entity) &&
            m_ECS->HasComponent<ECS::SphereMetadataComponent>(entity))
        {
            auto& mesh = m_ECS->GetComponent<ECS::MeshComponent>(entity);
            auto& renderComp = m_ECS->GetComponent<ECS::RenderComponent>(entity);
            auto& metadata = m_ECS->GetComponent<ECS::SphereMetadataComponent>(entity);

            MPE::ECS::RegenerateMeshIfDirty(mesh, metadata, renderComp);
        }
    }
}
}