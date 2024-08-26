#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/ECS/ECS.h"
#include "Editor/Editor/Objects/Base/Object.h"

namespace MPE
{
namespace ECS
{
struct MPE_EDITOR_API HierarchyComponent
{
    MPE::Object &parent;
    MPE::Object &child;

    HierarchyComponent(MPE::Object &parent, MPE::Object &child) : parent(parent), child(child) {}
};
}
}