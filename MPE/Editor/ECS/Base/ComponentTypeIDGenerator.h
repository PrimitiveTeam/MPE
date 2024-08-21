#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/ECS.h"

#include <typeindex>
#include <unordered_map>

namespace MPE
{
namespace ECS
{
class MPE_API ComponentTypeIDGenerator
{
  public:
    ComponentTypeIDGenerator();
    ~ComponentTypeIDGenerator();

    template <typename T>
    static uint32_t GetComponentTypeID()
    {
        static const uint32_t typeID = m_nextTypeID++;
        return typeID;
    }

  private:
    static uint32_t m_nextTypeID;
};

template <typename T>
uint32_t GetComponentTypeID()
{
    return ComponentTypeIDGenerator::GetComponentTypeID<T>();
}
}
}
