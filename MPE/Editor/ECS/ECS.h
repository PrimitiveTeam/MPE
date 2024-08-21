#pragma once

#include "MPE/Core/_CORE.h"

#include <entt/entt.hpp>

#include <unordered_map>
#include <vector>

namespace MPE
{
namespace ECS
{
using Entity = entt::entity;
using EntityRegistry = entt::registry;

class MPE_API ECS
{
  public:
    Entity CreateEntity();
    void DestroyEntity(Entity entity);

    template <typename Component, typename... Args>
    void AddComponent(Entity entity, Args&&... args);

    template <typename Component>
    void RemoveComponent(Entity entity);

    template <typename Component>
    Component& GetComponent(Entity entity);

    template <typename Component>
    bool HasComponent(Entity entity);

    template <typename System>
    void RegisterSystem(System&& system);

    template <typename Component, typename... Args>
    Component& AddComponentToEntity(Entity entity, Args&&... args);

    void RunSystems(float deltaTime);

  private:
    EntityRegistry m_registry;
    std::vector<std::function<void(EntityRegistry&, float)>> m_systems;
};

template <typename Component, typename... Args>
void ECS::AddComponent(Entity entity, Args&&... args)
{
    m_registry.emplace<Component>(entity, std::forward<Args>(args)...);
}

template <typename Component>
void ECS::RemoveComponent(Entity entity)
{
    m_registry.remove<Component>(entity);
}

template <typename Component>
Component& ECS::GetComponent(Entity entity)
{
    return m_registry.get<Component>(entity);
}

template <typename Component>
bool ECS::HasComponent(Entity entity)
{
    return m_registry.any_of<Component>(entity);
}

template <typename System>
void ECS::RegisterSystem(System&& system)
{
    m_systems.push_back([system = std::forward<System>(system)](EntityRegistry& reg, float deltaTime) { system(reg, deltaTime); });
}

template <typename Component, typename... Args>
Component& ECS::AddComponentToEntity(Entity entity, Args&&... args)
{
    return m_registry.emplace<Component>(entity, std::forward<Args>(args)...);
}
}
}