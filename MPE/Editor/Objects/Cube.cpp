#include "Cube.h"

#include "MPE/Log/GlobalLog.h"
#include "MPE/Renderer/Renderer.h"

#ifdef MPE_OPENGL
#    include "MPE/MPEGFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPEGFX_OPEN_GL_ES.h"
#endif

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

namespace MPE
{
Cube::Cube(ECS::ECS& ecs, const glm::vec3& position, const glm::vec3& scale)
    : m_ECS(ecs), m_angleX(0.0f), m_angleY(0.0f), m_angleZ(0.0f), m_autoRotate(true), m_rotateSpeed(10), m_color{0.5f, 0.5f, 0.0f, 1.0f}
{
    // Create an entity and add a transform component
    m_entity = m_ECS.CreateEntity();
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, position, glm::vec3(0.0f), scale);

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

void Cube::OnUpdate(Time deltaTime)
{
    if (m_autoRotate)
    {
        float deltaAngle = m_rotateSpeed * deltaTime.GetSeconds();
        m_angleX += deltaAngle;
        m_angleY += deltaAngle;
        m_angleZ += deltaAngle;

        m_angleX = fmod(m_angleX, 360.0f);
        m_angleY = fmod(m_angleY, 360.0f);
        m_angleZ = fmod(m_angleZ, 360.0f);
    }
}

void Cube::OnRender(StaticOrthographicCamera& camera)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_transform->position);
    transform = glm::rotate(transform, glm::radians(m_angleX), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_angleY), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
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

    Renderer::BeginScene(camera.GetCamera());
    Renderer::Submit(m_shader, m_vertexArray, transform);
    Renderer::EndScene();
}

void Cube::OnImGuiRender()
{
    ImGui::Text("Cube Controls");
    ImGui::Checkbox("Auto Rotate", &m_autoRotate);
    ImGui::SliderFloat("Rotate X", &m_angleX, -360.0f, 360.0f);
    ImGui::SliderFloat("Rotate Y", &m_angleY, -360.0f, 360.0f);
    ImGui::SliderFloat("Rotate Z", &m_angleZ, -360.0f, 360.0f);
    ImGui::SliderFloat3("Position", &m_transform->position.x, -10.0f, 10.0f);
}

glm::vec3& Cube::GetPosition()
{
    return m_transform->position;
}

void Cube::SetPosition(const glm::vec3& position)
{
    m_transform->position = position;
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