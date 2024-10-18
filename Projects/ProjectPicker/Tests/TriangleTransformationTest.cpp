#include "TriangleTransformationTest.h"
#include "MPE/MPEPCH.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"

#include "MPE/Vendor/GLM/GLM.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#endif

TriangleTransformationTest::TriangleTransformationTest()
    : Layer("Test"),
      CLEAR_COLOR{0.5f, 0.25f, 0.5f},
      TRIANGLE_POSITION(0.0f),
      TRIANGLE_SCALE_FACTOR(1.0f),
      TRIANGLE_VECTOR_SCALE{1.0f, 1.0f, 1.0f},
      TRIANGLE_SCALE(glm::scale(glm::mat4(1.0f), glm::vec3(TRIANGLE_VECTOR_SCALE) * TRIANGLE_SCALE_FACTOR)),
      TRIANGLE_COLOR{1.0f, 0.2f, 0.2f, 1.0f},
      autorotate(false),
      rotatespeed(10),
      rpm(0.0f),
      radians(0.0f)
{
    m_ECS = MPE::NEWREF<MPE::ECS::ECS>();
    MPE::REF<MPE::ECS::CameraComponent> cameraComponent = MPE::NEWREF<MPE::ECS::CameraComponent>();
    cameraComponent->SetMode(MPE::CameraMode::Orthographic, false);
    cameraComponent->SetOrthographic(1280.0f / 720.0f, 1.0f, -1.0f, 1.0f);
    SYS_CAMERA_CONTROLLER = MPE::NEWREF<MPE::Camera>(*m_ECS, cameraComponent);

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
    auto FLAT_COLOR_SHADER = MPE::ShaderLibrary::Load("Data/Shaders/FlatColor.glsl", true);
}

void TriangleTransformationTest::OnUpdate(MPE::Time deltaTime)
{
    UpdateColor(deltaTime);
    UpdateRotation(deltaTime);

    MPE::RenderPrimitive::SetClearColor(glm::vec4(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]));
    MPE::RenderPrimitive::Clear();

    MPE::Renderer::BeginScene(SYS_CAMERA_CONTROLLER->GetProjection());

    auto FLAT_COLOR_SHADER = MPE::ShaderLibrary::Get("FlatColor");

#ifdef MPE_OPENGL
    std::dynamic_pointer_cast<MPE::OpenGLShader>(FLAT_COLOR_SHADER)->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLShader>(FLAT_COLOR_SHADER)
        ->InjectUniformFloat4("UNI_COLOR", glm::vec4(TRIANGLE_COLOR[0], TRIANGLE_COLOR[1], TRIANGLE_COLOR[2], TRIANGLE_COLOR[3]));
#elif MPE_OPENGLES
    std::dynamic_pointer_cast<MPE::OpenGLESShader>(FLAT_COLOR_SHADER)->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLESShader>(FLAT_COLOR_SHADER)
        ->InjectUniformFloat4("UNI_COLOR", glm::vec4(TRIANGLE_COLOR[0], TRIANGLE_COLOR[1], TRIANGLE_COLOR[2], TRIANGLE_COLOR[3]));
#endif

    glm::mat4 TRIANGLE_TRANSFORM = glm::translate(glm::mat4(1.0f), TRIANGLE_POSITION);
#if MPE_PLATFORM_LINUX
    TRIANGLE_TRANSFORM = glm::rotate(TRIANGLE_TRANSFORM, (float) fmod(radians, 2.0f * glm::pi<float>()), glm::vec3(0.0f, 0.0f, 1.0f));
#else
    TRIANGLE_TRANSFORM = glm::rotate(TRIANGLE_TRANSFORM, fmod(radians, 2.0f * glm::pi<float>()), glm::vec3(0.0f, 0.0f, 1.0f));
#endif
    TRIANGLE_TRANSFORM = TRIANGLE_TRANSFORM * TRIANGLE_SCALE;

    MPE::Renderer::Submit(FLAT_COLOR_SHADER, SYS_VertexArray, TRIANGLE_TRANSFORM);

    MPE::Renderer::EndScene();
}

void TriangleTransformationTest::OnImGuiRender()
{
    // Allow manipulation up to 0.001% of the screen width and height
    auto screen_width = MPE::App::GetApp().GetWindow().get()->GetWidth() * 0.001f;
    auto screen_height = MPE::App::GetApp().GetWindow().get()->GetHeight() * 0.001f;

    ImGui::Begin("TEST");

    ImGui::Text("SCENE VARIABLES");

    ImGui::ColorEdit4("CLEAR COLOR", CLEAR_COLOR);
    ImGui::Text("SCREEN WIDTH: %f, SCREEN HEIGHT: %f", screen_width, screen_height);

    ImGui::Separator();

    ImGui::Text("TRIANGLE VARIABLES");
    ImGui::Text("R: %f, G: %f, B: %f", TRIANGLE_COLOR[0], TRIANGLE_COLOR[1], TRIANGLE_COLOR[2]);
    ImGui::ColorEdit4("Triangle Color", TRIANGLE_COLOR);

    ImGui::Separator();
    ImGui::Text("2D TRIANGLE TRANSFORMATION");
    ImGui::SliderFloat3("Triangle X Position", &TRIANGLE_POSITION.x, screen_width * -1.0f, screen_width);
    // ImGui::SliderFloat3("Triangle Y Position", &TRIANGLE_POSITION.y, screen_width * -1.0f, screen_width);
    if (ImGui::Button("RESET TRANSLATIONS"))
    {
        TRIANGLE_POSITION[0] = 0;
        TRIANGLE_POSITION[1] = 0;
        TRIANGLE_POSITION[2] = 0;
    }

    ImGui::Checkbox("Toggle Automatic Triangle Rotation", &autorotate);
    ImGui::SliderInt("Rotation Speed", &rotatespeed, -500, 500);
    float degrees = glm::degrees(radians);
    ImGui::SliderFloat("Triangle Rotation", &degrees, -360.0f, 360.0f, "%.1f", ImGuiSliderFlags_NoInput);

    ImGui::Text("%.1f RPM", rpm);
    if (ImGui::Button("Reset Triangle Rotation")) radians = 0.0f;

    ImGui::SliderFloat3("Triangle Vector Scale", &TRIANGLE_VECTOR_SCALE.x, 0.0f, 50.0f);
    if (ImGui::Button("RESET SCALE FACTOR")) TRIANGLE_SCALE_FACTOR = 1.0f;

    ImGui::SliderFloat("Trinagle Ratio Scale", &TRIANGLE_SCALE_FACTOR, -0.0f, 10.0f);
    if (ImGui::Button("RESET VECTORS"))
    {
        TRIANGLE_VECTOR_SCALE[0] = 1.0f;
        TRIANGLE_VECTOR_SCALE[1] = 1.0f;
        TRIANGLE_VECTOR_SCALE[2] = 1.0f;
    }
    ComputeTriangleScale();

    ImGui::Separator();
    ImGui::Text("2D CAMERA CONTROLLER");
    auto CAMERA_POSITION = SYS_CAMERA_CONTROLLER->GetPosition();
    ImGui::Text("Camera Position: X: %f, Y: %f, Z: %f", CAMERA_POSITION.x, CAMERA_POSITION.y, CAMERA_POSITION.z);
    ImGui::SliderFloat3("Camera Position", &CAMERA_POSITION.x, screen_width * -1.0f, screen_width);
    SYS_CAMERA_CONTROLLER->SetPosition(CAMERA_POSITION);

    // if (ImGui::Button("RESET CAMERA"))
    // {
    //     SYS_CAMERA_CONTROLLER.Reset();
    // }

    ImGui::End();
}

void TriangleTransformationTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(TriangleTransformationTest::OnKeyPressedEvent));
    SYS_CAMERA_CONTROLLER->OnEvent(event);
}

bool TriangleTransformationTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}

void TriangleTransformationTest::UpdateColor(MPE::Time deltaTime)
{
    if (!istimeset)
    {
        settime = deltaTime.GetSeconds();
        istimeset = true;
    }

    float &r = TRIANGLE_COLOR[0];
    float &g = TRIANGLE_COLOR[1];
    float &b = TRIANGLE_COLOR[2];

    float delta = deltaTime.GetSeconds();

    if (br)
    {
        if (r >= 1.0f)
        {
            incrR = -incrementValue;
        }
        else if (r <= 0.0f)
        {
            incrR = incrementValue;
        }
        r += incrR * delta;
        r = std::clamp(r, 0.0f, 1.0f);
    }

    if (bg)
    {
        if (g >= 1.0f)
        {
            incrG = -incrementValue;
        }
        else if (g <= 0.0f)
        {
            incrG = incrementValue;
        }
        g += incrG * delta;
        g = std::clamp(g, 0.0f, 1.0f);
    }

    if (bb)
    {
        if (b >= 1.0f)
        {
            incrB = -incrementValue;
        }
        else if (b <= 0.0f)
        {
            incrB = incrementValue;
        }
        b += incrB * delta;
        b = std::clamp(b, 0.0f, 1.0f);
    }
}

void TriangleTransformationTest::UpdateRotation(MPE::Time deltaTime)
{
    // if (autorotate)
    // {
    //     radians += glm::radians(rotatespeed * deltaTime.GetSeconds());
    //     rpm = rotatespeed * 60.0f / (2.0f * glm::pi<float>());
    // }

    if (autorotate)
    {
        radians += glm::radians(rotatespeed * deltaTime.GetSeconds());

        // Keep radians within the interval [-2π, 2π]
        if (radians > 2.0f * glm::pi<float>())
        {
            radians -= 2.0f * glm::pi<float>() * 2;
        }
        else if (radians < -2.0f * glm::pi<float>())
        {
            radians += 2.0f * glm::pi<float>() * 2;
        }

        rpm = rotatespeed * 60.0f / (2.0f * glm::pi<float>());
    }
}

void TriangleTransformationTest::ComputeTriangleScale()
{
    TRIANGLE_SCALE = glm::scale(glm::mat4(1.0f), glm::vec3(TRIANGLE_VECTOR_SCALE) * TRIANGLE_SCALE_FACTOR);
}
