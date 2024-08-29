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

class MPE_EDITOR_API ECS
{
    // Core functionality
  public:
    Entity CreateEntity();
    void DestroyEntity(Entity entity);

    template <typename Component, typename... Args>
    void AddComponent(Entity entity, Args&&... args);

    template <typename Component>
    void RemoveComponent(Entity entity);

    template <typename Component>
    void RemoveComponent(uint32_t entityId);

    template <typename Component>
    Component& GetComponent(Entity entity);

    template <typename Component>
    Component& GetComponent(uint32_t entityId);

    template <typename Component>
    bool HasComponent(Entity entity);

    template <typename Component>
    bool HasComponent(uint32_t entityId);

    template <typename System>
    void RegisterSystem(System&& system);

    // template <typename System>
    // void RegisterSystem(void (*systemFunc)(System&, EntityRegistry&, float), System& system);

    template <typename Component, typename... Args>
    Component& AddComponentToEntity(Entity entity, Args&&... args);

    void RunSystems(float deltaTime);

    // Utility
  public:
    // TagQuery
    std::vector<Entity> FindEntityByName(const std::string& name);
    std::vector<Entity> FindEntityByTag(const std::string& tag);
    std::vector<Entity> FindEntityByNameAndTag(const std::string& name, const std::string& tag);
    // TagQuery

  private:
    // struct RegisteredSystem
    // {
    //     void (*func)(void*, EntityRegistry&, float);
    //     void* systemInstance;
    // };

    EntityRegistry m_registry;
    std::vector<std::function<void(EntityRegistry&, float)>> m_systems;
    // std::vector<RegisteredSystem> m_systems;
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
void ECS::RemoveComponent(uint32_t entityId)
{
    m_registry.remove<Component>((Entity) entityId);
}

template <typename Component>
Component& ECS::GetComponent(Entity entity)
{
    return m_registry.get<Component>(entity);
}

template <typename Component>
Component& ECS::GetComponent(uint32_t entityId)
{
    return m_registry.get<Component>((Entity) entityId);
}

template <typename Component>
bool ECS::HasComponent(Entity entity)
{
    return m_registry.any_of<Component>(entity);
}

template <typename Component>
bool ECS::HasComponent(uint32_t entityId)
{
    return m_registry.any_of<Component>((Entity) entityId);
}

template <typename System>
void ECS::RegisterSystem(System&& system)
{
    m_systems.push_back([system = std::forward<System>(system)](EntityRegistry& reg, float deltaTime) { system(reg, deltaTime); });
}

// template <typename System>
// void ECS::RegisterSystem(void (*systemFunc)(System&, EntityRegistry&, float), System& system)
// {
//     m_systems.push_back({reinterpret_cast<void (*)(void*, EntityRegistry&, float)>(systemFunc), &system});
// }

template <typename Component, typename... Args>
Component& ECS::AddComponentToEntity(Entity entity, Args&&... args)
{
    return m_registry.emplace<Component>(entity, std::forward<Args>(args)...);
}
}
}

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
template <>
struct fmt::formatter<MPE::ECS::Entity> : fmt::formatter<std::string>
{
    template <typename FormatContext>
    auto format(MPE::ECS::Entity entity, FormatContext& ctx)
    {
        // Cast the entity to its underlying integer type and then convert to string
        auto entity_id = static_cast<std::underlying_type_t<entt::entity>>(entity);
        return fmt::formatter<std::string>::format(std::to_string(entity_id), ctx);
    }
};