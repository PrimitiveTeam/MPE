#include "Grid.h"
#include "MPE/MPEPCH.h"

#include "MPE/Renderer/Renderer.h"
#include "Editor/Editor/Objects/Cameras/Camera.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#endif

namespace MPE
{
Grid::Grid(ECS::ECS& ecs) : Object(ecs)
{
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

    this->Resize(10.0f, 1.0f);
}
Grid::Grid(ECS::ECS& ecs, float gridSize, float gridSpacing) : Object(ecs)
{
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

    this->Resize(gridSize, gridSpacing);
}

void Grid::OnUpdate(Time deltaTime) {}

void Grid::OnRender(Camera& camera)
{

    // #ifdef MPE_OPENGL
    //     std::dynamic_pointer_cast<MPE::OpenGLShader>(renderComp.shader)->InjectUniformFloat4("UNI_COLOR", material.color);
    // #elif MPE_OPENGLES
    //     std::dynamic_pointer_cast<MPE::OpenGLESShader>(renderComp.shader)->InjectUniformFloat4("UNI_COLOR", material.color);
    // #endif

    glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), m_transform->position);
    transformMatrix *= glm::toMat4(m_transform->rotation);
    transformMatrix = glm::scale(transformMatrix, m_transform->scale);

    m_shader->Bind();
    m_vertexArray->Bind();

    Renderer::BeginScene(camera.GetProjection());
    // Renderer::Submit(m_shader, m_vertexArray, m_transform);
    Renderer::SubmitLines(m_shader, m_vertexArray, transformMatrix);
    Renderer::EndScene();
}

void Grid::OnImGuiRender() {}

void Grid::OnEvent(Event& event) {}

void Grid::Resize(float gridSize, float gridSpacing)
{
    if (gridSize <= 0)
    {
        MPE_CORE_ERROR("Grid size must be greater than 0.");
        return;
    }
    if (gridSpacing <= 0)
    {
        MPE_CORE_ERROR("Grid spacing must be greater than 0.");
        return;
    }
    if (gridSize == m_size && gridSpacing == m_spacing) return;

    m_size = gridSize;
    m_spacing = gridSpacing;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    unsigned int index = 0;

    for (float i = -gridSize; i <= gridSize; i += gridSpacing)
    {
        vertices.push_back(i);
        vertices.push_back(-gridSize);
        vertices.push_back(0.0f);

        vertices.push_back(i);
        vertices.push_back(gridSize);
        vertices.push_back(0.0f);

        indices.push_back(index);
        indices.push_back(index + 1);
        index += 2;

        vertices.push_back(-gridSize);
        vertices.push_back(i);
        vertices.push_back(0.0f);

        vertices.push_back(gridSize);
        vertices.push_back(i);
        vertices.push_back(0.0f);

        indices.push_back(index);
        indices.push_back(index + 1);
        index += 2;
    }

    m_vertexArray = MPE::VertexArray::Create();
    MPE::REF<MPE::VertexBuffer> vertexBuffer;
    vertexBuffer = MPE::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float));
    vertexBuffer->SetLayout({{MPE::ShaderDataType::Vec3, "ATTR_POS"}});
    m_vertexArray->AddVertexBuffer(vertexBuffer);

    MPE::REF<MPE::IndexBuffer> indexBuffer = MPE::IndexBuffer::Create(indices.data(), indices.size());
    m_vertexArray->SetIndexBuffer(indexBuffer);

    m_shader = ShaderLibrary::AddOrLoadIfExists("Data/Shaders/Editor/Grid/GridShader.glsl", true);
}
}