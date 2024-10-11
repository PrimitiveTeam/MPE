#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/ECS/ECS.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/Shaders/Shader.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"

namespace MPE
{
namespace ECS
{
struct MPE_EDITOR_API RenderComponent
{
    REF<VertexArray> vertexArray;
    REF<Shader> shader;

    RenderComponent(REF<VertexArray> va, REF<Shader> shader) : vertexArray(va), shader(shader) {}

    void SetShader(const std::string& shaderPath) { shader = ShaderLibrary::AddOrLoadIfExists(shaderPath, true); }
};
}
}