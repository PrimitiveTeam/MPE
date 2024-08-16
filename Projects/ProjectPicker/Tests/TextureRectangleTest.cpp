#include "TextureRectangleTest.h"
#include "MPE/MPEPCH.h"

#include <glm/gtc/matrix_transform.hpp>

#ifdef MPE_OPENGL
#    include "MPE/MPEGFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPEGFX_OPEN_GL_ES.h"
#endif

TextureRectangleTest::TextureRectangleTest()
    : Layer("Test"),
      CLEAR_COLOR{0.5f, 0.25f, 0.5f},
      SYS_CAMERA_CONTROLLER(1280.0f / 720.0f, true),
      RECTANGLE_POSITION(0.0f),
      RECTANGLE_SCALE_FACTOR(1.0f),
      RECTANGLE_VECTOR_SCALE{1.0f, 1.0f, 1.0f},
      RECTANGLE_SCALE(glm::scale(glm::mat4(1.0f), glm::vec3(RECTANGLE_VECTOR_SCALE) * RECTANGLE_SCALE_FACTOR))
{
    // SQUARE
    SYS_VertexArray = MPE::VertexArray::Create();
    float SQV[5 * 4] = {-0.75f, -0.75f, 0.0f, 0.0f, 0.0f, 0.75f, -0.75f, 0.0f, 1.0f, 0.0f, 0.75f, 0.75f, 0.0f, 1.0f, 1.0f, -0.75f, 0.75f, 0.0f, 0.0f, 1.0f};

    MPE::REF<MPE::VertexBuffer> vertexBuffer;
    vertexBuffer = MPE::VertexBuffer::Create(SQV, sizeof(SQV));
    vertexBuffer->SetLayout({{MPE::ShaderDataType::Vec3, "ATTR_POS"}, {MPE::ShaderDataType::Vec2, "ATTR_TEXCOORD"}});
    SYS_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t SQI[6] = {0, 1, 2, 2, 3, 0};
    MPE::REF<MPE::IndexBuffer> SQIB;
    SQIB = MPE::IndexBuffer::Create(SQI, sizeof(SQI) / sizeof(uint32_t));
    SYS_VertexArray->SetIndexBuffer(SQIB);

    // SHADERS
    auto TEXTURE_SHADER = SYS_SHADER_LIBRARY.Load("Data/Shaders/Texture.glsl", true);

    // TEXTURES
    TEST_TEXTURE = MPE::Texture2D::Create("Data/Textures/TEST_TEXTURE.png");

#ifdef MPE_OPENGL
    std::dynamic_pointer_cast<MPE::OpenGLShader>(TEXTURE_SHADER)->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLShader>(TEXTURE_SHADER)->InjectUniformInt1("UNI_TEXTURE", 0);
#elif MPE_OPENGLES
    std::dynamic_pointer_cast<MPE::OpenGLESShader>(TEXTURE_SHADER)->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLESShader>(TEXTURE_SHADER)->InjectUniformInt1("UNI_TEXTURE", 0);
#endif
}

void TextureRectangleTest::OnUpdate(MPE::Time deltaTime)
{
    MPE::RenderPrimitive::SetClearColor(glm::vec4(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]));
    MPE::RenderPrimitive::Clear();

    MPE::Renderer::BeginScene(SYS_CAMERA_CONTROLLER.GetCamera());

    auto TEXTURE_SHADER = SYS_SHADER_LIBRARY.Get("Texture");

    glm::mat4 SQ_TRANSFORM = glm::translate(glm::mat4(1.0f), RECTANGLE_POSITION) * glm::scale(glm::mat4(1.0f), glm::vec3(RECTANGLE_VECTOR_SCALE) * 1.0f);
    TEST_TEXTURE->Bind();
    MPE::Renderer::Submit(TEXTURE_SHADER, SYS_VertexArray, SQ_TRANSFORM);

    MPE::Renderer::EndScene();
}

void TextureRectangleTest::OnImGuiRender()
{
    ImGui::Begin("TEST");

    ImGui::Text("SCENE VARIABLES");

    ImGui::ColorEdit4("CLEAR COLOR", CLEAR_COLOR);

    ImGui::End();
}

void TextureRectangleTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(TextureRectangleTest::OnKeyPressedEvent));
    SYS_CAMERA_CONTROLLER.OnEvent(event);
}

bool TextureRectangleTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}