#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Core/_PTRS.h"
#include "MPE/Renderer/Cameras/StaticOrthographicCamera.h"
#include "MPE/App/Layers/Layer.h"
#include "Editor/Editor/ECS/ECS.h"
#include "Editor/Editor/ECS/Systems/RenderSystem.h"
#include "Editor/Editor/Objects/Base/Object.h"
#include "Editor/Editor/Windows/ObjectHierarchy/ObjectHierarchy.h"

#include <string>

namespace MPE
{
class MPE_EDITOR_API Scene : public Layer
{
  public:
    Scene();
    Scene(const std::string& sceneName);
    ~Scene() = default;

    // template <typename T, typename... Args>
    // T& CreateObject(Args&&... args)
    // {
    //     MPE_ASSERT((std::is_base_of<Object, T>::value), "T must be derived from Object");
    //     m_objects.emplace_back(NEWREF<T>(m_ECS, std::forward<Args>(args)...));
    //     return *static_cast<T*>(m_objects.back().get());
    // }

    // template <typename T, typename... Args>
    // MPE::ECS::Entity CreateEntity(Args&&... args)
    // {
    //     MPE_ASSERT((std::is_base_of<Object, T>::value), "T must be derived from Object");
    //     auto& object = CreateObject<T>(m_ECS, std::forward<Args>(args)...);
    //     return object.GetEntity();
    // }

    template <typename T>
    T& CreateObject()
    {
        MPE_ASSERT((std::is_base_of<Object, T>::value), "T must be derived from Object");
        // m_objects.emplace_back(NEWREF<T>(m_ECS));
        m_objects->emplace_back(NEWREF<T>(*m_ECS));
        return *static_cast<T*>(m_objects->back().get());
    }

    void DestroyEntity(ECS::Entity entity);

    virtual void OnUpdate(Time deltaTime) override;

    void OnRender();

    virtual void OnImGuiRender() override;

    virtual void OnEvent(Event& event) override;

  public:
    const std::string& GetSceneName() const { return m_sceneName; }

    REF<ECS::ECS> GetECS() const { return m_ECS; }

    REF<StaticOrthographicCamera> GetMainCamera() const { return m_mainCamera; }

    const REF<std::vector<REF<Object>>>& GetObjects() const { return m_objects; }

  private:
    std::string m_sceneName;
    REF<ECS::ECS> m_ECS;
    REF<StaticOrthographicCamera> m_mainCamera;
    REF<std::vector<REF<Object>>> m_objects;

    MPE::REF<MPE::ECS::RenderSystem> m_renderSystem;
};
}