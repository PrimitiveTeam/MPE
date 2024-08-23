#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/ECS.h"

namespace MPE
{
namespace ECS
{
struct MPE_API TagComponent
{
    std::string name;
    std::string tag;

    TagComponent(const std::string& name = "Entity", const std::string& tag = "") : name(name), tag(tag) {}
};
}
}