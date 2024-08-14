#include "SimpleCubeTest.h"
#include "MPE/MPEPCH.h"

#include <glm/gtc/matrix_transform.hpp>

SimpleCubeTest::SimpleCubeTest()
    : Layer("Test"),
      CLEAR_COLOR{0.5f, 0.25f, 0.5f},
      SYS_CAMERA_CONTROLLER(1280.0f / 720.0f, true),
      RECTANGLE_POSITION(0.0f),
      RECTANGLE_SCALE_FACTOR(1.0f),
      RECTANGLE_VECTOR_SCALE{1.0f, 1.0f, 1.0f},
      RECTANGLE_SCALE(glm::scale(glm::mat4(1.0f), glm::vec3(RECTANGLE_VECTOR_SCALE) * RECTANGLE_SCALE_FACTOR)),
      autorotate(true),
      rotatespeed(10),
      angleX(0.0f),
      angleY(0.0f),
      angleZ(0.0f)
{
    // CUBE
    SYS_VertexArray = MPE::VertexArray::Create();
    float SQV[5 * 24] = {// Front face
                         // 0
                         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                         // 1
                         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                         // 2
                         0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                         // 3
                         -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,

                         // Back face
                         // 0
                         -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                         // 1
                         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
                         // 2
                         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                         // 3
                         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

                         // Left face
                         // 0
                         -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                         // 1
                         -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
                         // 2
                         -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
                         // 3
                         -0.5f, 0.5f, -0.5f, 1.0f, 0.0f,

                         // Right face
                         // 0
                         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                         // 1
                         0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                         // 2
                         0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                         // 3
                         0.5f, 0.5f, 0.5f, 0.0f, 0.0f,

                         // Top face
                         // 0
                         -0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
                         // 1
                         0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
                         // 2
                         0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                         // 3
                         -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,

                         // Bottom face
                         // 0
                         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                         // 1
                         0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                         // 2
                         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                         // 3
                         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f};

    MPE::REF<MPE::VertexBuffer> vertexBuffer;
    vertexBuffer = MPE::VertexBuffer::Create(SQV, sizeof(SQV));
    vertexBuffer->SetLayout({{MPE::ShaderDataType::Vec3, "ATTR_POS"}, {MPE::ShaderDataType::Vec2, "ATTR_TEXCOORD"}});
    SYS_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t SQI[36] = {// Front face
                        0, 1, 2, 2, 3, 0,
                        // Back face
                        4, 5, 6, 6, 7, 4,
                        // Left face
                        8, 9, 10, 10, 11, 8,
                        // Right face
                        12, 13, 14, 14, 15, 12,
                        // Top face
                        16, 17, 18, 18, 19, 16,
                        // Bottom face
                        20, 21, 22, 22, 23, 20};
    MPE::REF<MPE::IndexBuffer> SQIB;
    SQIB = MPE::IndexBuffer::Create(SQI, sizeof(SQI) / sizeof(uint32_t));
    SYS_VertexArray->SetIndexBuffer(SQIB);

    // SHADERS
    auto VERTEX_BASED_COLOR_SHADER = SYS_SHADER_LIBRARY.Load("Data/Shaders/VertexBasedColor.glsl", true);
}

void SimpleCubeTest::OnUpdate(MPE::Time deltatime)
{
    UpdateRotation(deltatime);

    MPE::RenderPrimitive::SetClearColor(glm::vec4(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]));
    MPE::RenderPrimitive::Clear();

    MPE::Renderer::BeginScene(SYS_CAMERA_CONTROLLER.GetCamera());

    auto VERTEX_BASED_COLOR_SHADER = SYS_SHADER_LIBRARY.Get("VertexBasedColor");

    glm::mat4 RECTANGLE_TRANSFORM = glm::translate(glm::mat4(1.0f), RECTANGLE_POSITION);
    RECTANGLE_TRANSFORM = glm::rotate(RECTANGLE_TRANSFORM, glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));
    RECTANGLE_TRANSFORM = glm::rotate(RECTANGLE_TRANSFORM, glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));
    RECTANGLE_TRANSFORM = glm::rotate(RECTANGLE_TRANSFORM, glm::radians(angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
    RECTANGLE_TRANSFORM = RECTANGLE_TRANSFORM * RECTANGLE_SCALE;

    MPE::Renderer::Submit(VERTEX_BASED_COLOR_SHADER, SYS_VertexArray, RECTANGLE_TRANSFORM);

    MPE::Renderer::EndScene();
}

void SimpleCubeTest::OnImGuiRender()
{
    ImGui::Begin("TEST");

    ImGui::Text("SCENE VARIABLES");

    ImGui::ColorEdit4("CLEAR COLOR", CLEAR_COLOR);

    ImGui::Separator();
    ImGui::Text("CUBE VARIABLES");
    ImGui::Checkbox("Auto Rotate", &autorotate);

    ImGui::SliderFloat("Rotate X", &angleX, -360.0f, 360.0f);
    ImGui::SliderFloat("Rotate Y", &angleY, -360.0f, 360.0f);
    ImGui::SliderFloat("Rotate Z", &angleZ, -360.0f, 360.0f);
    if (ImGui::Button("Reset Rotation"))
    {
        angleX = 0.0f;
        angleY = 0.0f;
        angleZ = 0.0f;
    }

    ImGui::End();
}

void SimpleCubeTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(SimpleCubeTest::OnKeyPressedEvent));
    SYS_CAMERA_CONTROLLER.OnEvent(event);
}

bool SimpleCubeTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}

void SimpleCubeTest::UpdateRotation(MPE::Time deltaTime)
{
    if (autorotate)
    {
        float deltaAngle = rotatespeed * deltaTime.GetSeconds();

        angleX += deltaAngle;
        angleY += deltaAngle;
        angleZ += deltaAngle;

        // Keep angles within the interval [0, 360]
        if (angleX > 360.0f) angleX -= 360.0f;
        if (angleY > 360.0f) angleY -= 360.0f;
        if (angleZ > 360.0f) angleZ -= 360.0f;

        if (angleX < 0.0f) angleX += 360.0f;
        if (angleY < 0.0f) angleY += 360.0f;
        if (angleZ < 0.0f) angleZ += 360.0f;
    }
}