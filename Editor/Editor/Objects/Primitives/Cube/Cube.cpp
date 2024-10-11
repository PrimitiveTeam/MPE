#include "Cube.h"

#include "MPE/Log/GlobalLog.h"
#include "MPE/Renderer/Renderer.h"
#include "Editor/Editor/ECS/Utility/RotationUtilities.h"
#include "Editor/Editor/ECS/Components/Graphical/MaterialComponent.h"
#include "Editor/Editor/ECS/Components/Graphical/RenderComponent.h"
#include "Editor/Editor/ECS/Components/Meshes/MeshFactory.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#endif

#include <imgui.h>
#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
Cube::Cube(ECS::ECS& ecs) : Object(ecs)
{
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

    ECS::MeshComponent cubeMesh = ECS::MeshFactory::CreateCube();
    m_meshComponent = &m_ECS.AddComponentToEntity<ECS::MeshComponent>(m_entity, std::move(cubeMesh));

    Init();
}

Cube::Cube(ECS::ECS& ecs, const glm::vec3& position, const glm::vec3& scale) : Object(ecs)
{
    // Create an entity and add a transform component
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, position, glm::vec3(0.0f), scale);

    ECS::MeshComponent cubeMesh = ECS::MeshFactory::CreateCube();
    m_meshComponent = &m_ECS.AddComponentToEntity<ECS::MeshComponent>(m_entity, std::move(cubeMesh));

    Init();
}

void Cube::OnUpdate(Time deltaTime)
{
    if (m_autoRotate)
    {
        float deltaAngle = m_rotateSpeed * deltaTime.GetSeconds();
        m_eulerRotation.x += deltaAngle;
        m_eulerRotation.y += deltaAngle;
        m_eulerRotation.z += deltaAngle;

        m_eulerRotation.x = fmod(m_eulerRotation.x, m_maxAngle);
        m_eulerRotation.y = fmod(m_eulerRotation.y, m_maxAngle);
        m_eulerRotation.z = fmod(m_eulerRotation.z, m_maxAngle);

        m_transform->rotation = MPE::ECS::RotationUtilities::EulerToQuaternion(m_eulerRotation);
    }
}

void Cube::OnRender(OrthographicCamera& camera)
{
    //     glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_transform->position);
    //     transform *= glm::toMat4(m_transform->rotation);
    //     transform = glm::scale(transform, m_transform->scale);

    //     m_shader->Bind();
    // // m_shader->InjectUniformFloat4("UNI_COLOR", m_color);
    // #ifdef MPE_OPENGL
    //     // std::dynamic_pointer_cast<MPE::OpenGLShader>(m_shader)->Bind();
    //     std::dynamic_pointer_cast<MPE::OpenGLShader>(m_shader)->InjectUniformFloat4("UNI_COLOR", m_color);
    // #elif MPE_OPENGLES
    //     // std::dynamic_pointer_cast<MPE::OpenGLESShader>(m_shader)->Bind();
    //     std::dynamic_pointer_cast<MPE::OpenGLESShader>(m_shader)->InjectUniformFloat4("UNI_COLOR", m_color);
    // #endif

    //     Renderer::BeginScene(camera);
    //     Renderer::Submit(m_shader, m_vertexArray, transform);
    //     Renderer::EndScene();
}

void Cube::OnImGuiRender()
{
    // ImGui::Text("Cube Controls");
    // ImGui::Checkbox("Auto Rotate", &m_autoRotate);
    // if (ImGui::SliderFloat("Rotate X", &m_eulerRotation.x, -m_maxAngle, m_maxAngle) |
    //     ImGui::SliderFloat("Rotate Y", &m_eulerRotation.y, -m_maxAngle, m_maxAngle) |
    //     ImGui::SliderFloat("Rotate Z", &m_eulerRotation.z, -m_maxAngle, m_maxAngle))
    // {
    //     m_transform->rotation = MPE::ECS::RotationUtilities::EulerToQuaternion(m_eulerRotation);
    // }
    // ImGui::SliderFloat3("Position", &m_transform->position.x, -10.0f, 10.0f);
}

void Cube::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
}

void Cube::Init()
{
    m_color = {0.6f, 0.6f, 0.6f, 1.0f};

    // Load shader
    m_shader = ShaderLibrary::AddOrLoadIfExists("Data/Shaders/FlatColorCube.glsl", true);

    // Initialize cube vertex array
    m_vertexArray = VertexArray::Create();

    // vertices

    REF<VertexBuffer> vertexBuffer =
        VertexBuffer::Create(m_meshComponent->interleavedVertices.data(), m_meshComponent->interleavedVertices.size() * sizeof(float));
    // vertexBuffer->SetLayout({{ShaderDataType::Vec3, "ATTR_POS"}});
    vertexBuffer->SetLayout({{ShaderDataType::Vec3, "ATTR_POS"}, {ShaderDataType::Vec3, "ATTR_NORMAL"}, {ShaderDataType::Vec2, "ATTR_TEXCOORD"}});
    m_vertexArray->AddVertexBuffer(vertexBuffer);

    // indices

    REF<IndexBuffer> indexBuffer = IndexBuffer::Create(m_meshComponent->indices.data(), m_meshComponent->indices.size());
    m_vertexArray->SetIndexBuffer(indexBuffer);

    // Add the RenderComponent and MaterialComponent
    m_ECS.AddComponentToEntity<ECS::RenderComponent>(m_entity, m_vertexArray, m_shader);
    m_ECS.AddComponentToEntity<ECS::MaterialComponent>(m_entity, glm::vec4(1.0f));
}

glm::vec4& Cube::GetColor()
{
    return m_color;
}

void Cube::SetColor(const glm::vec4& color)
{
    m_color = color;
}
}