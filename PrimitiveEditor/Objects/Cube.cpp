#define GLM_ENABLE_EXPERIMENTAL
#include "Cube.h"

#include "MPE/Log/GlobalLog.h"
#include "MPE/Renderer/Renderer.h"
#include "MPE/Editor/ECS/Utility/RotationUtilities.h"

#ifdef MPE_OPENGL
#    include "MPE/MPEGFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPEGFX_OPEN_GL_ES.h"
#endif

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

namespace MPE
{
Cube::Cube(ECS::ECS& ecs) : Object(ecs)
{
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

    Init();
}

Cube::Cube(ECS::ECS& ecs, const glm::vec3& position, const glm::vec3& scale) : Object(ecs)
{
    // Create an entity and add a transform component
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, position, glm::vec3(0.0f), scale);

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
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_transform->position);
    transform *= glm::toMat4(m_transform->rotation);
    transform = glm::scale(transform, m_transform->scale);

    m_shader->Bind();
// m_shader->InjectUniformFloat4("UNI_COLOR", m_color);
#ifdef MPE_OPENGL
    // std::dynamic_pointer_cast<MPE::OpenGLShader>(m_shader)->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLShader>(m_shader)->InjectUniformFloat4("UNI_COLOR", m_color);
#elif MPE_OPENGLES
    // std::dynamic_pointer_cast<MPE::OpenGLESShader>(m_shader)->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLESShader>(m_shader)->InjectUniformFloat4("UNI_COLOR", m_color);
#endif

    Renderer::BeginScene(camera);
    Renderer::Submit(m_shader, m_vertexArray, transform);
    Renderer::EndScene();
}

void Cube::OnImGuiRender()
{
    ImGui::Text("Cube Controls");
    ImGui::Checkbox("Auto Rotate", &m_autoRotate);
    if (ImGui::SliderFloat("Rotate X", &m_eulerRotation.x, -m_maxAngle, m_maxAngle) |
        ImGui::SliderFloat("Rotate Y", &m_eulerRotation.y, -m_maxAngle, m_maxAngle) |
        ImGui::SliderFloat("Rotate Z", &m_eulerRotation.z, -m_maxAngle, m_maxAngle))
    {
        m_transform->rotation = MPE::ECS::RotationUtilities::EulerToQuaternion(m_eulerRotation);
    }
    ImGui::SliderFloat3("Position", &m_transform->position.x, -10.0f, 10.0f);
}

void Cube::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
}

void Cube::Init()
{
    m_color = {0.6f, 0.6f, 0.6f, 1.0f};

    // Load shader
    m_shaderLibrary = NEWREF<ShaderLibrary>();
    m_shader = m_shaderLibrary->Load("Data/Shaders/FlatColor.glsl", true);

    // Initialize cube vertex array
    m_vertexArray = VertexArray::Create();
    float vertices[6 * 36] = {// I
                              -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
                              //
                              0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
                              //
                              0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
                              //
                              0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
                              //
                              -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
                              //
                              -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
                              // II
                              -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                              //
                              0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                              //
                              0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                              //
                              0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                              //
                              -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                              //
                              -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                              // III
                              -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
                              //
                              -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
                              //
                              -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
                              //
                              -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
                              //
                              -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
                              //
                              -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
                              // IV
                              0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
                              //
                              0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                              //
                              0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                              //
                              0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                              //
                              0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
                              //
                              0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
                              // V
                              -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
                              //
                              0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
                              //
                              0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
                              //
                              0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
                              //
                              -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
                              //
                              -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
                              // VI
                              -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                              //
                              0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                              //
                              0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
                              //
                              0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
                              //
                              -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
                              //
                              -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};
    REF<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
    vertexBuffer->SetLayout({{ShaderDataType::Vec3, "ATTR_POS"}, {ShaderDataType::Vec3, "ATTR_NORMAL"}});
    m_vertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t indices[36] = {// Front face
                            0, 1, 2, 3, 4, 5,
                            // Back face
                            6, 7, 8, 9, 10, 11,
                            // Left face
                            12, 13, 14, 15, 16, 17,
                            // Right face
                            18, 19, 20, 21, 22, 23,
                            // Top face
                            24, 25, 26, 27, 28, 29,
                            // Bottom face
                            30, 31, 32, 33, 34, 35};
    REF<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    m_vertexArray->SetIndexBuffer(indexBuffer);
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