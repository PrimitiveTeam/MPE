#include "PBRTest.h"
#include "MPE/MPEPCH.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"

#include "MPE/Vendor/GLM/GLM.h"

PBRTest::PBRTest()
    : Layer("Test"),
      m_clearColor{0.5f, 0.25f, 0.5f},
      m_rectanglePosition(0.0f),
      m_rectangleScaleFactor(0.5f),
      m_rectangleVectorScale{1.0f, 1.0f, 1.0f},
      m_rectangleScale(glm::scale(glm::mat4(1.0f), glm::vec3(m_rectangleVectorScale) * m_rectangleScaleFactor)),
      m_rectangleColor{1.0f, 0.5f, 0.31f, 1.0f},
      m_autoRotate(true),
      m_rotateSpeed(10),
      m_angleX(0.0f),
      m_angleY(0.0f),
      m_angleZ(0.0f),
      m_lightPosition(2.0f, 0.0f, -2.0f),
      m_rectanglePosition2(0.0f),
      m_rectangleScaleFactor2(0.5f),
      m_rectangleVectorScale2{1.0f, 1.0f, 1.0f},
      m_rectangleScale2(glm::scale(glm::mat4(1.0f), glm::vec3(m_rectangleVectorScale2) * m_rectangleScaleFactor2)),
      m_rectangleColor2{1.0f, 0.5f, 0.31f, 1.0f},
      m_autoRotate2(true),
      m_rotateSpeed2(10),
      m_angleX2(0.0f),
      m_angleY2(0.0f),
      m_angleZ2(0.0f),
      m_lightColor{1.0f, 1.0f, 1.0f, 1.0f}
{
    // m_perspectiveCamera(90.0f, 1280.0f / 720.0f, 0.1f, 100.0f),
    m_ECS = MPE::NEWREF<MPE::ECS::ECS>();
    m_perspectiveCamera = MPE::NEWREF<MPE::PerspectiveCamera>(*m_ECS, 90.0f, 1280.0f / 720.0f, 0.1f, 100.0f);

    // Get the camera a bit further away from the cube to see it
    m_perspectiveCamera->GetPerspectiveCameraComponent()->ManipulatePosition() = glm::vec3(0.0f, 0.0f, -10.0f);
    m_rectanglePosition.z = -1.0f;

    m_rectanglePosition2.x = -0.75f;
    m_rectanglePosition2.z = -1.0f;

    m_lightVertexArray = MPE::VertexArray::Create();
    float light_SQV[5 * 24] = {// Front face
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
    MPE::REF<MPE::VertexBuffer> lightVertexBuffer;
    lightVertexBuffer = MPE::VertexBuffer::Create(light_SQV, sizeof(light_SQV));
    lightVertexBuffer->SetLayout({{MPE::ShaderDataType::Vec3, "ATTR_POS"}, {MPE::ShaderDataType::Vec2, "ATTR_TEXCOORD"}});
    m_lightVertexArray->AddVertexBuffer(lightVertexBuffer);

    uint32_t light_SQI[36] = {// Front face
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
    MPE::REF<MPE::IndexBuffer> light_SQIB;
    light_SQIB = MPE::IndexBuffer::Create(light_SQI, sizeof(light_SQI) / sizeof(uint32_t));
    m_lightVertexArray->SetIndexBuffer(light_SQIB);

    auto light_shader = MPE::ShaderLibrary::Load("Data/Shaders/Lighting/Sources/LightSource_DynamicColor.glsl", true);

    // CUBE
    m_vertexArray = MPE::VertexArray::Create();
    float SQV[6 * 36] = {// I
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

    MPE::REF<MPE::VertexBuffer> vertexBuffer;
    vertexBuffer = MPE::VertexBuffer::Create(SQV, sizeof(SQV));
    vertexBuffer->SetLayout({{MPE::ShaderDataType::Vec3, "ATTR_POS"}, {MPE::ShaderDataType::Vec3, "ATTR_NORMAL"}});
    m_vertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t SQI[36] = {// Front face
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

    MPE::REF<MPE::IndexBuffer> SQIB;
    SQIB = MPE::IndexBuffer::Create(SQI, sizeof(SQI) / sizeof(uint32_t));
    m_vertexArray->SetIndexBuffer(SQIB);

    // SHADERS
    auto VERTEX_BASED_COLOR_SHADER = MPE::ShaderLibrary::Load("Data/Shaders/Lighting/Phong/LitSurface_WorldSpace.glsl", true);

    // CUBE 2
    m_vertexArray2 = MPE::VertexArray::Create();
    float SQV2[6 * 36] = {// I
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

    MPE::REF<MPE::VertexBuffer> vertexBuffer2;
    vertexBuffer2 = MPE::VertexBuffer::Create(SQV2, sizeof(SQV2));
    vertexBuffer2->SetLayout({{MPE::ShaderDataType::Vec3, "ATTR_POS"}, {MPE::ShaderDataType::Vec3, "ATTR_NORMAL"}});
    m_vertexArray2->AddVertexBuffer(vertexBuffer2);

    uint32_t SQI2[36] = {// Front face
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

    MPE::REF<MPE::IndexBuffer> SQIB2;
    SQIB2 = MPE::IndexBuffer::Create(SQI2, sizeof(SQI2) / sizeof(uint32_t));
    m_vertexArray2->SetIndexBuffer(SQIB2);

    auto VERTEX_BASED_COLOR_SHADER2 = MPE::ShaderLibrary::Load("Data/Shaders/Lighting/Phong/LitSurface_ViewSpace.glsl", true);
}

void PBRTest::OnUpdate(MPE::Time deltaTime)
{
    UpdateRotation(deltaTime);

    MPE::RenderPrimitive::SetClearColor(glm::vec4(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    MPE::RenderPrimitive::Clear();

    MPE::Renderer::BeginScene(m_perspectiveCamera->GetPerspectiveCameraComponent()->GetProjectionViewMatrix());

    // LIGHT
    {
        auto light_shader = MPE::ShaderLibrary::Get("LightSource_DynamicColor");
        light_shader->Bind();
        light_shader->SetFloat4("UNI_COLOR", glm::vec4(m_lightColor[0], m_lightColor[1], m_lightColor[2], m_lightColor[3]));

        glm::mat4 light_transform = glm::translate(glm::mat4(1.0f), m_lightPosition);
        light_transform = glm::scale(light_transform, glm::vec3(0.2f));

        MPE::Renderer::Submit(light_shader, m_lightVertexArray, light_transform);
    }
    // CUBE WORLD SPACE
    {
        auto VERTEX_BASED_COLOR_SHADER = MPE::ShaderLibrary::Get("LitSurface_WorldSpace");
        VERTEX_BASED_COLOR_SHADER->Bind();
        // VERTEX_BASED_COLOR_SHADER->SetFloat4("UNI_COLOR", glm::vec4(m_rectangleColor[0], m_rectangleColor[1], m_rectangleColor[2], m_rectangleColor[3]));
        VERTEX_BASED_COLOR_SHADER->SetFloat4("UNI_OBJECT_COLOR", glm::vec4(m_rectangleColor[0], m_rectangleColor[1], m_rectangleColor[2], m_rectangleColor[3]));
        VERTEX_BASED_COLOR_SHADER->SetFloat4("UNI_LIGHT_COLOR", glm::vec4(m_lightColor[0], m_lightColor[1], m_lightColor[2], m_lightColor[3]));
        VERTEX_BASED_COLOR_SHADER->SetFloat3("UNI_LIGHT_POSITION", m_lightPosition);
        VERTEX_BASED_COLOR_SHADER->SetFloat3("UNI_VIEW_POSITION", m_perspectiveCamera->GetPerspectiveCameraComponent()->GetPosition());
        VERTEX_BASED_COLOR_SHADER->Unbind();

        glm::mat4 RECTANGLE_TRANSFORM = glm::translate(glm::mat4(1.0f), m_rectanglePosition);
        RECTANGLE_TRANSFORM = glm::rotate(RECTANGLE_TRANSFORM, glm::radians(m_angleX), glm::vec3(1.0f, 0.0f, 0.0f));
        RECTANGLE_TRANSFORM = glm::rotate(RECTANGLE_TRANSFORM, glm::radians(m_angleY), glm::vec3(0.0f, 1.0f, 0.0f));
        RECTANGLE_TRANSFORM = glm::rotate(RECTANGLE_TRANSFORM, glm::radians(m_angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
        RECTANGLE_TRANSFORM = RECTANGLE_TRANSFORM * m_rectangleScale;

        MPE::Renderer::Submit(VERTEX_BASED_COLOR_SHADER, m_vertexArray, RECTANGLE_TRANSFORM);
    }
    // CUBE VIEW SPACE
    {
        auto VERTEX_BASED_COLOR_SHADER = MPE::ShaderLibrary::Get("LitSurface_ViewSpace");
        VERTEX_BASED_COLOR_SHADER->Bind();
        // VERTEX_BASED_COLOR_SHADER->SetFloat4("UNI_COLOR", glm::vec4(m_rectangleColor[0], m_rectangleColor[1], m_rectangleColor[2], m_rectangleColor[3]));
        VERTEX_BASED_COLOR_SHADER->SetFloat4("UNI_OBJECT_COLOR",
                                             glm::vec4(m_rectangleColor2[0], m_rectangleColor2[1], m_rectangleColor2[2], m_rectangleColor2[3]));
        // auto m_lightPosition2 = glm::vec3(m_lightPosition[0] + 0.25f, m_lightPosition[1], m_lightPosition[2]);
        VERTEX_BASED_COLOR_SHADER->SetFloat4("UNI_LIGHT_COLOR", glm::vec4(m_lightColor[0], m_lightColor[1], m_lightColor[2], m_lightColor[3]));
        VERTEX_BASED_COLOR_SHADER->SetFloat3("UNI_LIGHT_POSITION", m_lightPosition);
        // VERTEX_BASED_COLOR_SHADER->SetFloat3("UNI_VIEW_POSITION", m_perspectiveCamera->GetPerspectiveCameraComponent()->GetPosition());
        VERTEX_BASED_COLOR_SHADER->Unbind();

        glm::mat4 RECTANGLE_TRANSFORM = glm::translate(glm::mat4(1.0f), m_rectanglePosition2);
        RECTANGLE_TRANSFORM = glm::rotate(RECTANGLE_TRANSFORM, glm::radians(m_angleX2), glm::vec3(1.0f, 0.0f, 0.0f));
        RECTANGLE_TRANSFORM = glm::rotate(RECTANGLE_TRANSFORM, glm::radians(m_angleY2), glm::vec3(0.0f, 1.0f, 0.0f));
        RECTANGLE_TRANSFORM = glm::rotate(RECTANGLE_TRANSFORM, glm::radians(m_angleZ2), glm::vec3(0.0f, 0.0f, 1.0f));
        RECTANGLE_TRANSFORM = RECTANGLE_TRANSFORM * m_rectangleScale2;

        MPE::Renderer::Submit(VERTEX_BASED_COLOR_SHADER, m_vertexArray2, RECTANGLE_TRANSFORM);
    }

    MPE::Renderer::EndScene();
}

void PBRTest::OnImGuiRender()
{
    ImGui::Begin("TEST");

    ImGui::Text("SCENE VARIABLES");

    ImGui::ColorEdit4("CLEAR COLOR", m_clearColor);

    ImGui::Separator();

    ImGui::Text("CAMERA VARIABLES");

    float fov = m_perspectiveCamera->GetPerspectiveCameraComponent()->GetFov();
    ImGui::SliderFloat("FOV", &fov, 1.0f, 179.0f);
    m_perspectiveCamera->GetPerspectiveCameraComponent()->SetFov(fov);

    float cNear = m_perspectiveCamera->GetPerspectiveCameraComponent()->GetNear();
    ImGui::SliderFloat("NEAR", &cNear, 0.1f, 10.0f);
    m_perspectiveCamera->GetPerspectiveCameraComponent()->SetNear(cNear);

    float cFar = m_perspectiveCamera->GetPerspectiveCameraComponent()->GetFar();
    ImGui::SliderFloat("FAR", &cFar, 10.0f, 100.0f);
    m_perspectiveCamera->GetPerspectiveCameraComponent()->SetFar(cFar);

    ImGui::Separator();

    ImGui::Text("LIGHT VARIABLES");

    ImGui::ColorEdit4("LIGHT COLOR", m_lightColor);

    ImGui::SliderFloat("Light X", &m_lightPosition.x, -10.0f, 10.0f);
    ImGui::SliderFloat("Light Y", &m_lightPosition.y, -10.0f, 10.0f);
    ImGui::SliderFloat("Light Z", &m_lightPosition.z, -10.0f, 10.0f);

    ImGui::Separator();
    ImGui::Text("CUBE#1 VARIABLES");

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

    ImGui::Separator();

    ImGui::Text("CUBE#2 VARIABLES");

    ImGui::ColorEdit4("RECTANGLE COLOR 2", m_rectangleColor2);

    // Translate cube
    ImGui::SliderFloat("Translate X 2", &m_rectanglePosition2.x, -10.0f, 10.0f);
    ImGui::SliderFloat("Translate Y 2", &m_rectanglePosition2.y, -10.0f, 10.0f);
    ImGui::SliderFloat("Translate Z 2", &m_rectanglePosition2.z, -10.0f, 10.0f);

    ImGui::Checkbox("Auto Rotate 2", &m_autoRotate2);

    ImGui::SliderFloat("Rotate X 2", &m_angleX2, -360.0f, 360.0f);
    ImGui::SliderFloat("Rotate Y 2", &m_angleY2, -360.0f, 360.0f);
    ImGui::SliderFloat("Rotate Z 2", &m_angleZ2, -360.0f, 360.0f);
    if (ImGui::Button("Reset Rotation 2"))
    {
        m_angleX2 = 0.0f;
        m_angleY2 = 0.0f;
        m_angleZ2 = 0.0f;
    }

    ImGui::End();
}

void PBRTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(PBRTest::OnKeyPressedEvent));
    // m_perspectiveCamera->GetPerspectiveCameraComponent()->OnEvent(event);
}

bool PBRTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}

void PBRTest::UpdateRotation(MPE::Time deltaTime)
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

    if (m_autoRotate2)
    {
        float deltaAngle = m_rotateSpeed2 * deltaTime.GetSeconds();

        m_angleX2 += deltaAngle;
        m_angleY2 += deltaAngle;
        m_angleZ2 += deltaAngle;

        // Keep angles within the interval [0, 360]
        if (m_angleX2 > 360.0f) m_angleX2 -= 360.0f;
        if (m_angleY2 > 360.0f) m_angleY2 -= 360.0f;
        if (m_angleZ2 > 360.0f) m_angleZ2 -= 360.0f;

        if (m_angleX2 < 0.0f) m_angleX2 += 360.0f;
        if (m_angleY2 < 0.0f) m_angleY2 += 360.0f;
        if (m_angleZ2 < 0.0f) m_angleZ2 += 360.0f;
    }
}