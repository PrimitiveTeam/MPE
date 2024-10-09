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
    virtual void OnRender(OrthographicCamera& camera) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Event& event) override;

    ECS::TransformComponent& GetTransform() { return *m_transform; }

    glm::vec4& GetColor();
    void SetColor(const glm::vec4& color);

    bool GetLineDrawing() const { return m_lineDrawing; }
    void SetLineDrawing(bool lineDrawing) { m_lineDrawing = lineDrawing; }
    void ToggleLineDrawing() { m_lineDrawing = !m_lineDrawing; }

    float GetRadius() const { return m_radius; }
    void SetRadius(float radius);

    uint32_t GetSectors() const { return m_sectors; }
    void SetSectors(uint32_t sectors);

    uint32_t GetStacks() const { return m_stacks; }
    void SetStacks(uint32_t stacks);

    uint32_t GetUpAxis() const { return m_upAxis; }
    void SetUpAxis(uint32_t upAxis);

    bool GetSmooth() const { return m_smooth; }
    void SetSmooth(bool smooth);

    void ReverseNormals();

  private:
    void RecalculateSphere(float radius, uint32_t sectors, uint32_t stacks, bool smooth, int upAxis);
    void EnsureCleanArrays();
    void AddVertex(float x, float y, float z);
    void AddNormal(float nx, float ny, float nz);
    void AddTexureCoord(float s, float t);
    void AddIndices(unsigned int i1, unsigned int i2, unsigned int i3);
    void SwitchUpAxis(unsigned int from, unsigned int to);
    void GenerateVertices();
    void GenerateSmoothVertices();
    void GenerateFlatVertices();
    void GenerateInterleavedVertices();
    std::vector<float> GenerateFaceNormal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);

  private:
    ECS::TransformComponent* m_transform;

    glm::vec4 m_color;

    glm::vec3 m_eulerRotation = {0.0f, 0.0f, 0.0f};
    float m_maxAngle = 1080.0f;
    bool m_autoRotate = false;
    int m_rotateSpeed = 10;

    bool m_lineDrawing = false;

    float m_radius;
    // longitudes
    uint32_t m_sectors;
    // latitudes
    uint32_t m_stacks;
    bool m_smooth;
    uint32_t m_upAxis;
    std::vector<float> m_vertices;
    std::vector<float> m_normals;
    std::vector<float> m_textureCoords;
    std::vector<unsigned int> m_indices;
    std::vector<unsigned int> m_indicesLines;

    // interleaved
    std::vector<float> m_interleavedVertices;
    unsigned int m_interleavedStride;

    REF<Shader> m_shader;
    REF<VertexArray> m_vertexArray;
};
}