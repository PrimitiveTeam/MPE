#include "Grid.h"
#include "MPE/MPEPCH.h"

#include "MPE/Renderer/Renderer.h"
#include "Editor/Editor/Objects/Cameras/Camera.h"
#include "Editor/Editor/ECS/Components/Graphical/MaterialComponent.h"
#include "Editor/Editor/ECS/Components/Graphical/RenderComponent.h"
#include "Editor/Editor/ECS/Components/Meshes/MeshFactory.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#endif

#include <imgui.h>

namespace MPE
{
Grid::Grid(ECS::ECS& ecs) : Object(ecs)
{
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

    auto [mesh, metadata] = ECS::MeshFactory::CreateGrid();
    mesh.lineDrawing = true;
    m_meshComponent = &m_ECS.AddComponentToEntity<ECS::MeshComponent>(m_entity, mesh);
    m_gridMetadata = &m_ECS.AddComponentToEntity<ECS::GridMetadataComponent>(m_entity, metadata);

    this->Init();
}
Grid::Grid(ECS::ECS& ecs, float gridSize, float gridSpacing) : Object(ecs)
{
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

    auto [mesh, metadata] = ECS::MeshFactory::CreateGrid(gridSize, gridSpacing);
    mesh.lineDrawing = true;
    m_meshComponent = &m_ECS.AddComponentToEntity<ECS::MeshComponent>(m_entity, mesh);
    m_gridMetadata = &m_ECS.AddComponentToEntity<ECS::GridMetadataComponent>(m_entity, metadata);

    this->Init();
}

void Grid::Init()
{
    m_shader = ShaderLibrary::AddOrLoadIfExists("Data/Shaders/Editor/Grid/GridShader.glsl", true);

    m_vertexArray = VertexArray::Create();

    REF<VertexBuffer> vertexBuffer = VertexBuffer::Create(m_meshComponent->vertices.data(), m_meshComponent->vertices.size() * sizeof(float));
    vertexBuffer->SetLayout({{ShaderDataType::Vec3, "ATTR_POS"}});
    m_vertexArray->AddVertexBuffer(vertexBuffer);

    REF<IndexBuffer> indexBuffer = IndexBuffer::Create(m_meshComponent->indices.data(), m_meshComponent->indices.size());
    m_vertexArray->SetIndexBuffer(indexBuffer);

    m_ECS.AddComponentToEntity<ECS::RenderComponent>(m_entity, m_vertexArray, m_shader);
    m_ECS.AddComponentToEntity<ECS::MaterialComponent>(m_entity, m_color);
}

void Grid::OnUpdate(Time deltaTime) {}

void Grid::OnRender(Camera& camera)
{

    // #ifdef MPE_OPENGL
    //     std::dynamic_pointer_cast<MPE::OpenGLShader>(renderComp.shader)->InjectUniformFloat4("UNI_COLOR", material.color);
    // #elif MPE_OPENGLES
    //     std::dynamic_pointer_cast<MPE::OpenGLESShader>(renderComp.shader)->InjectUniformFloat4("UNI_COLOR", material.color);
    // #endif

    // glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), m_transform->position);
    // transformMatrix *= glm::toMat4(m_transform->rotation);
    // transformMatrix = glm::scale(transformMatrix, m_transform->scale);

    // m_shader->Bind();
    // m_vertexArray->Bind();

    // Renderer::BeginScene(camera.GetProjection());
    // // Renderer::Submit(m_shader, m_vertexArray, m_transform);
    // Renderer::SubmitLines(m_shader, m_vertexArray, transformMatrix);
    // Renderer::EndScene();
}

void Grid::OnImGuiRender()
{
    ImGui::Begin("GRID");
    float gridSize = m_gridMetadata->GetGridSize();
    float gridSpacing = m_gridMetadata->GetGridSpacing();

    ImGui::Text("GRID VARIABLES");
    ImGui::SliderFloat("GRID SIZE", &gridSize, 0.0f, 100.0f);
    ImGui::SliderFloat("GRID SPACING", &gridSpacing, 0.0f, 10.0f);

    m_gridMetadata->SetGridSize(gridSize);
    m_gridMetadata->SetGridSpacing(gridSpacing);

    ImGui::ColorEdit4("Color", &m_color[0]);

    ImGui::End();
}

void Grid::OnEvent(Event& event) {}
}