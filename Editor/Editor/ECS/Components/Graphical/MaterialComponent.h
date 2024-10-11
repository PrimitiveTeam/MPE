#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/ECS/ECS.h"
#include "MPE/Renderer/Textures/Texture2D.h"

namespace MPE
{
namespace ECS
{
struct MPE_EDITOR_API MaterialComponent
{
    glm::vec4 color;
    REF<Texture2D> texture;

    MaterialComponent(const glm::vec4& color = glm::vec4(1.0f), const std::string& texturePath = "") : color(color)
    {
        if (!texturePath.empty())
        {
            texture = Texture2D::Create(texturePath);
        }
    }
};
}
}