#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Core/_PTRS.h"
#include "MPE/Time/Time.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/Shaders/Shader.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"
#include "Editor/Editor/Objects/Base/Object.h"
#include "Editor/Editor/ECS/Components/Core/TransformComponent.h"

namespace MPE
{
class Camera;
class MPE_EDITOR_API Grid : public Object
{
  public:
    Grid(ECS::ECS& ecs);
    Grid(ECS::ECS& ecs, float gridSize, float gridSpacing);
    ~Grid() = default;

  private:
    // virtual void Init() override;

  public:
    virtual void OnUpdate(Time deltaTime) override;
    virtual void OnRender(Camera& camera) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Event& event) override;

    ECS::TransformComponent& GetTransform() { return *m_transform; }

    float GetGridSize() const { return m_size; }
    float GetGridSpacing() const { return m_spacing; }

    void Resize(float gridSize, float gridSpacing);

  private:
    ECS::TransformComponent* m_transform;

    float m_size;
    float m_spacing;

    REF<Shader> m_shader;
    REF<VertexArray> m_vertexArray;
};
}