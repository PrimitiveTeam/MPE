#include "GridTest.h"
#include "MPE/MPEPCH.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"

#include "MPE/Vendor/GLM/GLM.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#    if MPE_PLATFORM_LINUX
#    else
#        include <glad/glad.h>
#        include <GLFW/glfw3.h>
#    endif
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#endif

GridTest::GridTest()
    : Layer("Test"),
      CLEAR_COLOR{0.5f, 0.25f, 0.5f},
      TRIANGLE_POSITION(0.0f),
      TRIANGLE_SCALE_FACTOR(1.0f),
      TRIANGLE_VECTOR_SCALE{1.0f, 1.0f, 1.0f},
      TRIANGLE_SCALE(glm::scale(glm::mat4(1.0f), glm::vec3(TRIANGLE_VECTOR_SCALE) * TRIANGLE_SCALE_FACTOR)),
      TRIANGLE_COLOR{1.0f, 0.2f, 0.2f, 1.0f}
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

    // GRID
    SYS_Grid = MPE::NEWREF<MPE::Grid>(*m_ECS, 10.0f, 0.2f);
    // SYS_Grid.Init(10.0f, 0.2f, SYS_CAMERA_CONTROLLER);
}

void GridTest::OnUpdate(MPE::Time deltaTime)
{
    UpdateColor(deltaTime);
    SYS_CAMERA_CONTROLLER->OnUpdate(deltaTime);

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

    glm::mat4 TRIANGLE_TRANSFORM = glm::translate(glm::mat4(1.0f), TRIANGLE_POSITION) * TRIANGLE_SCALE;
    MPE::Renderer::Submit(FLAT_COLOR_SHADER, SYS_VertexArray, TRIANGLE_TRANSFORM);

    SYS_Grid->OnRender(*SYS_CAMERA_CONTROLLER);

    MPE::Renderer::EndScene();
}

void GridTest::OnImGuiRender()
{
    ImGui::Begin("TEST");

    ImGui::Text("SCENE VARIABLES");

    ImGui::ColorEdit4("CLEAR COLOR", CLEAR_COLOR);

    ImGui::Separator();

    // Get grid size and spacing, then use imgui sliders to change them
    float gridSize = SYS_Grid->GetGridSize();
    float gridSpacing = SYS_Grid->GetGridSpacing();

    ImGui::Text("GRID VARIABLES");
    ImGui::SliderFloat("GRID SIZE", &gridSize, 0.0f, 100.0f);
    ImGui::SliderFloat("GRID SPACING", &gridSpacing, 0.0f, 10.0f);

    SYS_Grid->Resize(gridSize, gridSpacing);

    ImGui::Separator();

    ImGui::Text("TRIANGLE VARIABLES");
    ImGui::Text("R: %f, G: %f, B: %f", TRIANGLE_COLOR[0], TRIANGLE_COLOR[1], TRIANGLE_COLOR[2]);

    ImGui::End();
}

void GridTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(GridTest::OnKeyPressedEvent));
    SYS_CAMERA_CONTROLLER->OnEvent(event);
}

bool GridTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}

void GridTest::UpdateColor(MPE::Time deltaTime)
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