#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Time/Time.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/Shaders/Shader.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"
#include "MPE/Renderer/Textures/Texture2D.h"
#include "Editor/Editor/Objects/Base/Object.h"
#include "Editor/Editor/ECS/Components/Core/TransformComponent.h"
#include "Editor/Editor/ECS/Components/Meshes/MeshComponent.h"
#include "Editor/Editor/ECS/Components/Meshes/Metadata/SphereMetadataComponent.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
class Camera;
class MPE_EDITOR_API Sphere : public Object
{
  public:
    Sphere(ECS::ECS& ecs);
    Sphere(ECS::ECS& ecs, const glm::vec3& position, const glm::vec3& scale);
    Sphere(ECS::ECS& ecs, const glm::vec3& position, const glm::vec3& scale, float radius, uint32_t sectors, uint32_t stacks, bool smooth = true,
           int upAxis = 3);

  private:
    virtual void Init() override;

  public:
    virtual void OnUpdate(Time deltaTime) override;
    virtual void OnRender(Camera& camera) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Event& event) override;

    ECS::TransformComponent& GetTransform() { return *m_transform; }
    ECS::MeshComponent& GetMeshComponent() { return *m_meshComponent; }
    ECS::SphereMetadataComponent& GetSphereMetadata() { return *m_sphereMetadata; }

    glm::vec4& GetColor();
    void SetColor(const glm::vec4& color);

  private:
    ECS::TransformComponent* m_transform;
    ECS::MeshComponent* m_meshComponent;
    ECS::SphereMetadataComponent* m_sphereMetadata;

    glm::vec4 m_color;

    glm::vec3 m_eulerRotation = {0.0f, 0.0f, 0.0f};
    float m_maxAngle = 1080.0f;
    bool m_autoRotate = false;
    int m_rotateSpeed = 10;

    REF<Shader> m_shader;
    REF<Texture2D> m_texture;
    REF<VertexArray> m_vertexArray;
};
}