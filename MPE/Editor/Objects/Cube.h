#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"
#include "MPE/Renderer/Cameras/StaticOrthographicCamera.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/Shaders/Shader.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"
#include "MPE/Editor/ECS/ECS.h"
#include "MPE/Editor/ECS/Components/TransformComponent.h"

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

    glm::vec3& GetPosition();
    void SetPosition(const glm::vec3& position);

    glm::vec4& GetColor();
    void SetColor(const glm::vec4& color);

  private:
    void UpdateTransform();

  private:
    ECS::Entity m_entity;
    ECS::ECS& m_ECS;
    ECS::TransformComponent* m_transform;

    glm::vec4 m_color;

    float m_angleX, m_angleY, m_angleZ;
    bool m_autoRotate;
    int m_rotateSpeed;

    REF<ShaderLibrary> m_shaderLibrary;
    REF<Shader> m_shader;
    REF<VertexArray> m_vertexArray;
};
}