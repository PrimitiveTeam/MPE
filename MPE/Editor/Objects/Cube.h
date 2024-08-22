#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"
#include "MPE/Renderer/Cameras/StaticOrthographicCamera.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/Shaders/Shader.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"
#include "MPE/Editor/ECS/ECS.h"
#include "MPE/Editor/ECS/Components/Core/TransformComponent.h"
#include "MPE/Editor/ECS/Components/Core/TagComponent.h"

#include <glm/glm.hpp>

namespace MPE
{
class MPE_API Cube
{
  public:
    Cube(ECS::ECS& ecs, const glm::vec3& position, const glm::vec3& scale);

    void OnUpdate(Time deltaTime);
    void OnRender(StaticOrthographicCamera& camera);
    void OnImGuiRender();

    ECS::Entity GetEntity() const { return m_entity; }

    ECS::TransformComponent& GetTransform() { return *m_transform; }

    glm::vec4& GetColor();
    void SetColor(const glm::vec4& color);

  private:
    void UpdateTransform();

  private:
    ECS::Entity m_entity;
    ECS::ECS& m_ECS;
    ECS::TagComponent* m_tag;
    ECS::TransformComponent* m_transform;

    glm::vec4 m_color;

    glm::vec3 m_eulerRotation = {0.0f, 0.0f, 0.0f};
    float m_maxAngle = 1080.0f;
    bool m_autoRotate = false;
    int m_rotateSpeed = 10;

    REF<ShaderLibrary> m_shaderLibrary;
    REF<Shader> m_shader;
    REF<VertexArray> m_vertexArray;
};
}