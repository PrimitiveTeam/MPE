#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/ECS.h"
#include "MPE/Editor/ECS/Base/IComponentArray.h"

#include <array>
#include <unordered_map>

namespace MPE
{
namespace ECS
{
template <typename T>
class MPE_API ComponentArray : public IComponentArray
{
  public:
    ComponentArray() {};
    ~ComponentArray() {};

    void InsertData(Entity entity, T component)
    {
        m_entityToIndexMap[entity] = m_size;
        m_indexToEntityMap[m_size] = entity;
        m_componentArray[m_size] = component;
        m_size++;
    }

    void RemoveData(Entity entity)
    {
        m_entityToIndexMap.erase(entity);
        m_indexToEntityMap.erase(m_entityToIndexMap[entity]);
        m_componentArray[m_entityToIndexMap[entity]] = m_componentArray[m_size - 1];
        m_entityToIndexMap[m_indexToEntityMap[m_size - 1]] = m_entityToIndexMap[entity];
        m_indexToEntityMap[m_entityToIndexMap[entity]] = m_indexToEntityMap[m_size - 1];
        m_size--;
    };

    T& GetData(Entity entity) { return m_componentArray[m_entityToIndexMap[entity]]; }

  private:
    std::array<T, MAX_ENTITIES> m_componentArray;
    std::unordered_map<Entity, uint32_t> m_entityToIndexMap;
    std::unordered_map<uint32_t, Entity> m_indexToEntityMap;
    uint32_t m_size = 0;
};
}
}