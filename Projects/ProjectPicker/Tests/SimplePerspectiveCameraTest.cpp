#include "SimplePerspectiveCameraTest.h"
#include "MPE/MPEPCH.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"

#include "MPE/Vendor/GLM/GLM.h"

SimplePerspectiveCameraTest::SimplePerspectiveCameraTest()
    : Layer("Test"),
      m_clearColor{0.5f, 0.25f, 0.5f},
      m_rectanglePosition(0.0f),
      m_rectangleScaleFactor(0.5f),
      m_rectangleVectorScale{1.0f, 1.0f, 1.0f},
      m_rectangleScale(glm::scale(glm::mat4(1.0f), glm::vec3(m_rectangleVectorScale) * m_rectangleScaleFactor)),
      m_rectangleColor{0.0f, 0.0f, 1.0f, 1.0f},
      m_autoRotate(true),
      m_rotateSpeed(10),
      m_angleX(0.0f),
      m_angleY(0.0f),
      m_angleZ(0.0f)
{
    // m_perspectiveCamera(90.0f, 1280.0f / 720.0f, 0.1f, 100.0f),
    m_ECS = MPE::NEWREF<MPE::ECS::ECS>();
    MPE::REF<MPE::ECS::CameraComponent> cameraComponent = MPE::NEWREF<MPE::ECS::CameraComponent>();
    cameraComponent->SetMode(MPE::CameraMode::Perspective, false);
    cameraComponent->SetPerspective(90.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
    m_perspectiveCamera = MPE::NEWREF<MPE::Camera>(*m_ECS, cameraComponent);

    // Get the camera a bit further away from the cube to see it
    m_perspectiveCamera->SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));
    m_rectanglePosition.z = -1.0f;

    // CUBE
    m_vertexArray = MPE::VertexArray::Create();
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
    m_vertexArray->AddVertexBuffer(vertexBuffer);

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
    m_vertexArray->SetIndexBuffer(SQIB);

    // SHADERS
    auto VERTEX_BASED_COLOR_SHADER = MPE::ShaderLibrary::Load("Data/Shaders/FlatColor.glsl", true);
}

void SimplePerspectiveCameraTest::OnUpdate(MPE::Time deltaTime)
{
    UpdateRotation(deltaTime);

    MPE::RenderPrimitive::SetClearColor(glm::vec4(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    MPE::RenderPrimitive::Clear();

    MPE::Renderer::BeginScene(m_perspectiveCamera->GetProjection());

    auto VERTEX_BASED_COLOR_SHADER = MPE::ShaderLibrary::Get("FlatColor");
    VERTEX_BASED_COLOR_SHADER->SetFloat4("UNI_COLOR", glm::vec4(m_rectangleColor[0], m_rectangleColor[1], m_rectangleColor[2], m_rectangleColor[3]));

    glm::mat4 RECTANGLE_TRANSFORM = glm::translate(glm::mat4(1.0f), m_rectanglePosition);
    RECTANGLE_TRANSFORM = glm::rotate(RECTANGLE_TRANSFORM, glm::radians(m_angleX), glm::vec3(1.0f, 0.0f, 0.0f));
    RECTANGLE_TRANSFORM = glm::rotate(RECTANGLE_TRANSFORM, glm::radians(m_angleY), glm::vec3(0.0f, 1.0f, 0.0f));
    RECTANGLE_TRANSFORM = glm::rotate(RECTANGLE_TRANSFORM, glm::radians(m_angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
    RECTANGLE_TRANSFORM = RECTANGLE_TRANSFORM * m_rectangleScale;

    MPE::Renderer::Submit(VERTEX_BASED_COLOR_SHADER, m_vertexArray, RECTANGLE_TRANSFORM);

    MPE::Renderer::EndScene();
}

void SimplePerspectiveCameraTest::OnImGuiRender()
{
    ImGui::Begin("TEST");

    ImGui::Text("SCENE VARIABLES");

    ImGui::ColorEdit4("CLEAR COLOR", m_clearColor);

    ImGui::Separator();

    ImGui::Text("CAMERA VARIABLES");

    float fov = m_perspectiveCamera->GetFov();
    ImGui::SliderFloat("FOV", &fov, 1.0f, 179.0f);
    m_perspectiveCamera->SetFov(fov);

    float cNear = m_perspectiveCamera->GetNear();
    ImGui::SliderFloat("NEAR", &cNear, 0.1f, 10.0f);
    m_perspectiveCamera->SetNear(cNear);

    float cFar = m_perspectiveCamera->GetFar();
    ImGui::SliderFloat("FAR", &cFar, 10.0f, 100.0f);
    m_perspectiveCamera->SetFar(cFar);

    ImGui::Separator();
    ImGui::Text("CUBE VARIABLES");

    ImGui::ColorEdit4("RECTANGLE COLOR", m_rectangleColor);

    // Translate cube
    ImGui::SliderFloat("Translate X", &m_rectanglePosition.x, -10.0f, 10.0f);
    ImGui::SliderFloat("Translate Y", &m_rectanglePosition.y, -10.0f, 10.0f);
    ImGui::SliderFloat("Translate Z", &m_rectanglePosition.z, -10.0f, 10.0f);

    ImGui::Checkbox("Auto Rotate", &m_autoRotate);

    ImGui::SliderFloat("Rotate X", &m_angleX, -360.0f, 360.0f);
    ImGui::SliderFloat("Rotate Y", &m_angleY, -360.0f, 360.0f);
    ImGui::SliderFloat("Rotate Z", &m_angleZ, -360.0f, 360.0f);
    if (ImGui::Button("Reset Rotation"))
    {
        m_angleX = 0.0f;
        m_angleY = 0.0f;
        m_angleZ = 0.0f;
    }

    ImGui::End();
}

void SimplePerspectiveCameraTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(SimplePerspectiveCameraTest::OnKeyPressedEvent));
    m_perspectiveCamera->OnEvent(event);
}

bool SimplePerspectiveCameraTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}

void SimplePerspectiveCameraTest::UpdateRotation(MPE::Time deltaTime)
{
    if (m_autoRotate)
    {
        float deltaAngle = m_rotateSpeed * deltaTime.GetSeconds();

        m_angleX += deltaAngle;
        m_angleY += deltaAngle;
        m_angleZ += deltaAngle;

        // Keep angles within the interval [0, 360]
        if (m_angleX > 360.0f) m_angleX -= 360.0f;
        if (m_angleY > 360.0f) m_angleY -= 360.0f;
        if (m_angleZ > 360.0f) m_angleZ -= 360.0f;

        if (m_angleX < 0.0f) m_angleX += 360.0f;
        if (m_angleY < 0.0f) m_angleY += 360.0f;
        if (m_angleZ < 0.0f) m_angleZ += 360.0f;
    }
}