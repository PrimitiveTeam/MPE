#include "ColorTriangleTest.h"
#include "MPE/MPEPCH.h"

#include <glm/gtc/matrix_transform.hpp>

ColorTriangleTest::ColorTriangleTest()
    : Layer("Test"),
      CLEAR_COLOR{0.5f, 0.25f, 0.5f},
      SYS_CAMERA_CONTROLLER(1280.0f / 720.0f, true),
      TRIANGLE_POSITION(0.0f),
      TRIANGLE_SCALE_FACTOR(1.0f),
      TRIANGLE_VECTOR_SCALE{1.0f, 1.0f, 1.0f},
      TRIANGLE_SCALE(glm::scale(glm::mat4(1.0f), glm::vec3(TRIANGLE_VECTOR_SCALE) * TRIANGLE_SCALE_FACTOR)),
      TRIANGLE_COLOR{1.0f, 0.2f, 0.2f, 1.0f}
{

    SYS_VertexArray = MPE::VertexArray::Create();
    float vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 1.0f, 0.2f, 1.0f, 1.0f, 0.5f, -0.5f, 0.0f, 0.2f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.2f, 1.0f};

    MPE::REF<MPE::VertexBuffer> vertexBuffer;
    vertexBuffer = MPE::VertexBuffer::Create(vertices, sizeof(vertices));
    vertexBuffer->SetLayout({{MPE::ShaderDataType::Vec3, "ATTR_POS"}, {MPE::ShaderDataType::Vec4, "ATTR_COLOR"}});
    SYS_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t indices[3] = {0, 1, 2};
    MPE::REF<MPE::IndexBuffer> indexBuffer;
    indexBuffer = MPE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    SYS_VertexArray->SetIndexBuffer(indexBuffer);

    // SHADERS
    auto FLAT_COLOR_SHADER = SYS_SHADER_LIBRARY.Load("Data/Shaders/FlatColor.glsl");
}

void ColorTriangleTest::OnUpdate(MPE::Time deltatime)
{
    MPE::RenderPrimitive::SetClearColor(glm::vec4(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]));
    MPE::RenderPrimitive::Clear();

    MPE::Renderer::BeginScene(SYS_CAMERA_CONTROLLER.GetCamera());

    auto FLAT_COLOR_SHADER = SYS_SHADER_LIBRARY.Get("FlatColor");

    std::dynamic_pointer_cast<MPE::OpenGLShader>(FLAT_COLOR_SHADER)->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLShader>(FLAT_COLOR_SHADER)
        ->InjectUniformFloat4("UNI_COLOR", glm::vec4(TRIANGLE_COLOR[0], TRIANGLE_COLOR[1], TRIANGLE_COLOR[2], TRIANGLE_COLOR[3]));

    glm::mat4 TRIANGLE_TRANSFORM = glm::translate(glm::mat4(1.0f), TRIANGLE_POSITION) * TRIANGLE_SCALE;
    MPE::Renderer::Submit(FLAT_COLOR_SHADER, SYS_VertexArray, TRIANGLE_TRANSFORM);

    MPE::Renderer::EndScene();
}

void ColorTriangleTest::OnImGuiRender()
{
    ImGui::Begin("TEST");

    ImGui::Text("SCENE VARIABLES");

    ImGui::ColorEdit4("CLEAR COLOR", CLEAR_COLOR);

    ImGui::Separator();

    ImGui::Text("TRIANGLE VARIABLES");
    ImGui::ColorEdit4("TRIANGLE COLOR", TRIANGLE_COLOR);

    ImGui::End();
}

void ColorTriangleTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(ColorTriangleTest::OnKeyPressedEvent));
}

bool ColorTriangleTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}