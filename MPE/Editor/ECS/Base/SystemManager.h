#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/ECS.h"
#include "MPE/Editor/ECS/Systems/System.h"

#include <unordered_map>
#include <bitset>
#include <memory>

namespace MPE
{
namespace ECS
{
class MPE_API SystemManager
{
  public:
    SystemManager();
    ~SystemManager();

    template <typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        const char* typeName = typeid(T).name();

        auto system = std::make_shared<T>();
        m_systems.insert({typeName, system});
        return system;
    }

    template <typename T>
    void EntitySignatureChanged(Entity entity, std::bitset<MAX_COMPONENTS> entitySignature)
    {
        const char* typeName = typeid(T).name();

        auto system = m_systems.find(typeName);
        if (system != m_systems.end())
        {
            auto& entities = system->second->entities;

            if ((entitySignature & system->second->signature) == system->second->signature)
            {
                entities.insert(entity);
            }
            else
            {
                entities.erase(entity);
            }
        }
    }

  private:
    std::unordered_map<const char*, std::shared_ptr<System>> m_systems;
};
}
}