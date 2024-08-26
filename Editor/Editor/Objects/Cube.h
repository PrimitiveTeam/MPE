#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"
#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/Shaders/Shader.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"
#include "Editor/Editor/Objects/Base/Object.h"
#include "Editor/Editor/ECS/Components/Core/TransformComponent.h"

#include "MPE/Vendor/GLM/GLM.h"


namespace MPE
{
class MPE_EDITOR_API Cube : public Object
{
  public:
    Cube(ECS::ECS& ecs);
    Cube(ECS::ECS& ecs, const glm::vec3& position, const glm::vec3& scale);

  private:
    virtual void Init() override;

  public:
    virtual void OnUpdate(Time deltaTime) override;
    virtual void OnRender(OrthographicCamera& camera) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Event& event) override;

    ECS::TransformComponent& GetTransform() { return *m_transform; }

    glm::vec4& GetColor();
    void SetColor(const glm::vec4& color);

  private:
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