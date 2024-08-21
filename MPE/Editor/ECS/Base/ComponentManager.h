#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/ECS.h"
#include "MPE/Editor/ECS/Base/ComponentArray.h"
#include "MPE/Editor/ECS/Base/ComponentTypeIDGenerator.h"

#include <unordered_map>

namespace MPE
{
namespace ECS
{
class MPE_API ComponentManager
{
  public:
    ComponentManager();
    ~ComponentManager();

    template <typename T>
    void AddComponent(Entity entity, T component)
    {
        GetComponentArray<T>()->InsertData(entity, component);
    }

    template <typename T>
    T& GetComponent(Entity entity)
    {
        return GetComponentArray<T>()->GetData(entity);
    }

    template <typename T>
    ComponentArray<T>* GetComponentArray()
    {
        const size_t typeID = GetComponentTypeID<T>();

        if (m_componentArrays.find(typeID) == m_componentArrays.end())
        {
            m_componentArrays[typeID] = std::make_shared<ComponentArray<T>>();
        }

        return static_cast<ComponentArray<T>*>(m_componentArrays[typeID].get());
    }

  private:
    std::unordered_map<uint32_t, std::shared_ptr<IComponentArray>> m_componentArrays;
};
}
}