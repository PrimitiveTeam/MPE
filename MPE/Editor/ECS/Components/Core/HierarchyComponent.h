#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/ECS.h"
#include "MPE/Editor/Objects/Base/Object.h"

namespace MPE
{
namespace ECS
{
struct MPE_API HierarchyComponent
{
    MPE::Object &parent;
    MPE::Object &child;

    HierarchyComponent(MPE::Object &parent, MPE::Object &child) : parent(parent), child(child) {}
};
}
}