#include "Sphere.h"

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
const unsigned char MINIMUM_SECTORS = 2;
const unsigned char MINIMUM_STACKS = 2;

Sphere::Sphere(ECS::ECS& ecs) : Object(ecs)
{
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

    auto [mesh, metadata] = ECS::MeshFactory::CreateSphere();
    m_meshComponent = &m_ECS.AddComponentToEntity<ECS::MeshComponent>(m_entity, mesh);
    m_sphereMetadata = &m_ECS.AddComponentToEntity<ECS::SphereMetadataComponent>(m_entity, metadata);

    Init();
}

Sphere::Sphere(ECS::ECS& ecs, const glm::vec3& position, const glm::vec3& scale) : Object(ecs)
{
    // Create an entity and add a transform component
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, position, glm::vec3(0.0f), scale);

    auto [mesh, metadata] = ECS::MeshFactory::CreateSphere();
    m_meshComponent = &m_ECS.AddComponentToEntity<ECS::MeshComponent>(m_entity, mesh);
    m_sphereMetadata = &m_ECS.AddComponentToEntity<ECS::SphereMetadataComponent>(m_entity, metadata);

    Init();
}

Sphere::Sphere(ECS::ECS& ecs, const glm::vec3& position, const glm::vec3& scale, float radius, uint32_t sectors, uint32_t stacks, bool smooth, int upAxis)
    : Object(ecs)
{
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, position, glm::vec3(0.0f), scale);

    auto [mesh, metadata] = ECS::MeshFactory::CreateSphere(radius, sectors, stacks, smooth, upAxis);
    m_meshComponent = &m_ECS.AddComponentToEntity<ECS::MeshComponent>(m_entity, mesh);
    m_sphereMetadata = &m_ECS.AddComponentToEntity<ECS::SphereMetadataComponent>(m_entity, metadata);

    Init();
    // RecalculateSphere(radius, sectors, stacks, smooth, upAxis);
}

void Sphere::OnUpdate(Time deltaTime)
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

void Sphere::OnRender(OrthographicCamera& camera)
{
    //     glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_transform->position);
    //     transform *= glm::toMat4(m_transform->rotation);
    //     transform = glm::scale(transform, m_transform->scale);

    //     // m_shader->Bind();

    // #ifdef MPE_OPENGL
    //     std::dynamic_pointer_cast<MPE::OpenGLShader>(m_shader)->Bind();
    //     // std::dynamic_pointer_cast<MPE::OpenGLShader>(m_shader)->InjectUniformFloat4("UNI_COLOR", m_color);
    //     std::dynamic_pointer_cast<MPE::OpenGLShader>(m_shader)->InjectUniformInt1("UNI_TEXTURE", 0);
    // #elif MPE_OPENGLES
    //     // std::dynamic_pointer_cast<MPE::OpenGLESShader>(m_shader)->Bind();
    //     // std::dynamic_pointer_cast<MPE::OpenGLESShader>(m_shader)->InjectUniformFloat4("UNI_COLOR", m_color);
    // #endif

    //     m_vertexArray->Bind();
    //     m_texture->Bind();
    //     Renderer::BeginScene(camera);
    //     // if (m_lineDrawing)
    //     //     Renderer::SubmitLines(m_shader, m_vertexArray, transform);
    //     // else
    //     Renderer::Submit(m_shader, m_vertexArray, transform);
    //     Renderer::EndScene();
}

void Sphere::OnImGuiRender()
{
    // ImGui::Text("Sphere Controls");
    // ImGui::Checkbox("Auto Rotate", &m_autoRotate);
    // if (ImGui::SliderFloat("Rotate X", &m_eulerRotation.x, -m_maxAngle, m_maxAngle) |
    //     ImGui::SliderFloat("Rotate Y", &m_eulerRotation.y, -m_maxAngle, m_maxAngle) |
    //     ImGui::SliderFloat("Rotate Z", &m_eulerRotation.z, -m_maxAngle, m_maxAngle))
    // {
    //     m_transform->rotation = MPE::ECS::RotationUtilities::EulerToQuaternion(m_eulerRotation);
    // }
    // ImGui::SliderFloat3("Position", &m_transform->position.x, -10.0f, 10.0f);

    // // Temporary metadata editor
    // ImGui::Text("Sphere Metadata");
    // auto radius = m_sphereMetadata->GetRadius();
    // auto sectors = m_sphereMetadata->GetSectors();
    // auto stacks = m_sphereMetadata->GetStacks();
    // auto smooth = m_sphereMetadata->GetSmooth();
    // auto upAxis = m_sphereMetadata->GetUpAxis();

    // if (ImGui::SliderFloat("Radius", &radius, 0.1f, 10.0f))
    // {
    //     m_sphereMetadata->SetRadius(radius);
    // }

    // if (ImGui::SliderInt("Sectors", (int*) &sectors, MINIMUM_SECTORS, 100))
    // {
    //     m_sphereMetadata->SetSectors(sectors);
    // }

    // if (ImGui::SliderInt("Stacks", (int*) &stacks, MINIMUM_STACKS, 100))
    // {
    //     m_sphereMetadata->SetStacks(stacks);
    // }

    // if (ImGui::Checkbox("Smooth", &smooth))
    // {
    //     m_sphereMetadata->SetSmooth(smooth);
    // }

    // // make a lambda toggle to switch between 1, 2, 3
    // if (ImGui::Button("Toggle Up Axis"))
    // {
    //     m_sphereMetadata->SetUpAxis((m_sphereMetadata->GetUpAxis() % 3) + 1);
    // }

    // if (ImGui::Button("Reverse Normals"))
    // {
    //     m_sphereMetadata->ReverseNormals();
    // }

    // if (ImGui::Button("Toggle Line Drawing"))
    // {
    //     m_meshComponent->lineDrawing = !m_meshComponent->lineDrawing;
    // }
}

void Sphere::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
}

void Sphere::Init()
{
    m_color = {0.6f, 0.6f, 0.6f, 1.0f};

    m_shader = ShaderLibrary::AddOrLoadIfExists("Data/Shaders/TextureWithNormals.glsl", true);
    // m_texture = MPE::Texture2D::Create("Data/Textures/earth2048.bmp");

    m_vertexArray = VertexArray::Create();

    REF<VertexBuffer> vertexBuffer =
        VertexBuffer::Create(m_meshComponent->interleavedVertices.data(), m_meshComponent->interleavedVertices.size() * sizeof(float));
    vertexBuffer->SetLayout({{ShaderDataType::Vec3, "ATTR_POS"}, {MPE::ShaderDataType::Vec3, "ATTR_NORMALS"}, {MPE::ShaderDataType::Vec2, "ATTR_TEXCOORD"}});
    m_vertexArray->AddVertexBuffer(vertexBuffer);

    REF<IndexBuffer> indexBuffer = IndexBuffer::Create(m_meshComponent->indices.data(), m_meshComponent->indices.size());
    m_vertexArray->SetIndexBuffer(indexBuffer);

    m_ECS.AddComponentToEntity<ECS::RenderComponent>(m_entity, m_vertexArray, m_shader);
    m_ECS.AddComponentToEntity<ECS::MaterialComponent>(m_entity, glm::vec4(1.0f), "Data/Textures/earth2048.bmp");
}

glm::vec4& Sphere::GetColor()
{
    return m_color;
}

void Sphere::SetColor(const glm::vec4& color)
{
    m_color = color;
}
}