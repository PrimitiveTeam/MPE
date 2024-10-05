#include "GeneralTest.h"
#include "MPE/MPEPCH.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"

#include "MPE/Vendor/GLM/GLM.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#endif

GeneralTest::GeneralTest()
    : Layer("GeneralTest"),
      SYS_CAMERA_CONTROLLER(1280.0f / 720.0f, true),
      // SCENE VARIABLES
      CLEAR_COLOR{0.5f, 0.25f, 0.5f},
      // TRIANGLE
      TRIANGLE_POSITION(0.0f),
      TRIANGLE_SCALE_FACTOR(1.0f),
      TRIANGLE_VECTOR_SCALE{1.0f, 1.0f, 1.0f},
      TRIANGLE_SCALE(glm::scale(glm::mat4(1.0f), glm::vec3(TRIANGLE_VECTOR_SCALE) * TRIANGLE_SCALE_FACTOR)),
      // SQUARE
      SQ_POSITION{0.0f, 0.0f, 0.0f},
      SQ_SCALE_FACTOR(0.05f),
      SQ_VECTOR_SCALE{1.0f, 1.0f, 1.0f},
      SQ_SCALE(glm::scale(glm::mat4(1.0f), glm::vec3(SQ_VECTOR_SCALE) * SQ_SCALE_FACTOR))
{
    // TRIANGLE
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

    // SQUARE
    SYS_SQVA = MPE::VertexArray::Create();
    float SQV[5 * 4] = {-0.75f, -0.75f, 0.0f, 0.0f, 0.0f, 0.75f, -0.75f, 0.0f, 1.0f, 0.0f, 0.75f, 0.75f, 0.0f, 1.0f, 1.0f, -0.75f, 0.75f, 0.0f, 0.0f, 1.0f};

    MPE::REF<MPE::VertexBuffer> SQVB;
    SQVB = MPE::VertexBuffer::Create(SQV, sizeof(SQV));
    SQVB->SetLayout({{MPE::ShaderDataType::Vec3, "ATTR_POS"}, {MPE::ShaderDataType::Vec2, "ATTR_TEXCOORD"}});
    SYS_SQVA->AddVertexBuffer(SQVB);

    uint32_t SQI[6] = {0, 1, 2, 2, 3, 0};
    MPE::REF<MPE::IndexBuffer> SQIB;
    SQIB = MPE::IndexBuffer::Create(SQI, sizeof(SQI) / sizeof(uint32_t));
    SYS_SQVA->SetIndexBuffer(SQIB);

    // SHADERS
    auto TEXTURE_SHADER = MPE::ShaderLibrary::Load("Data/Shaders/Texture.glsl", true);
    auto FLAT_COLOR_SHADER = MPE::ShaderLibrary::Load("Data/Shaders/FlatColor.glsl", true);
    auto VERTEX_BASED_COLOR_SHADER = MPE::ShaderLibrary::Load("Data/Shaders/VertexBasedColor.glsl", true);

    // TEXTURES
    TEST_TEXTURE = MPE::Texture2D::Create("Data/Textures/TEST_TEXTURE.png");
    TEST_TEXTURE2 = MPE::Texture2D::Create("Data/Textures/TEST_TEXTURE_TRANSPARENCY_1.png");

#ifdef MPE_OPENGL
    std::dynamic_pointer_cast<MPE::OpenGLShader>(TEXTURE_SHADER)->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLShader>(TEXTURE_SHADER)->InjectUniformInt1("UNI_TEXTURE", 0);
#elif MPE_OPENGLES
    std::dynamic_pointer_cast<MPE::OpenGLESShader>(TEXTURE_SHADER)->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLESShader>(TEXTURE_SHADER)->InjectUniformInt1("UNI_TEXTURE", 0);
#endif

    m_LayerName = MPE::NEWSCOPE<std::string>("GeneralTest");
}

void GeneralTest::OnUpdate(MPE::Time deltaTime)
{
    {
        // m_LayerName = MPE::NEWSCOPE<std::string>("GeneralTest");
    }
    {
        // m_LayerName = nullptr;
    }
    // MPE_TRACE("Delta time: {0}s ({1}ms)", deltaTime.GetSeconds(), deltaTime.GetMilliSeconds());

    // OBJECT TRANSLATION
    // TRIANGLE
    if (KEY_CONTROL_TRANSFORM[0])
    {
        if (MPE::Input::IsKeyPressed(MPE_KEY_LEFT))
        {
            TRIANGLE_POSITION[0] -= OBJECT_MOVEMENT_SPEED * deltaTime;
        }
        if (MPE::Input::IsKeyPressed(MPE_KEY_RIGHT))
        {
            TRIANGLE_POSITION[0] += OBJECT_MOVEMENT_SPEED * deltaTime;
        }
        if (MPE::Input::IsKeyPressed(MPE_KEY_DOWN))
        {
            TRIANGLE_POSITION[1] -= OBJECT_MOVEMENT_SPEED * deltaTime;
        }
        if (MPE::Input::IsKeyPressed(MPE_KEY_UP))
        {
            TRIANGLE_POSITION[1] += OBJECT_MOVEMENT_SPEED * deltaTime;
        }
    }
    // SQUARE
    if (KEY_CONTROL_TRANSFORM[1])
    {
        if (MPE::Input::IsKeyPressed(MPE_KEY_LEFT))
        {
            SQ_POSITION[0] -= OBJECT_MOVEMENT_SPEED * deltaTime;
        }
        if (MPE::Input::IsKeyPressed(MPE_KEY_RIGHT))
        {
            SQ_POSITION[0] += OBJECT_MOVEMENT_SPEED * deltaTime;
        }
        if (MPE::Input::IsKeyPressed(MPE_KEY_DOWN))
        {
            SQ_POSITION[1] -= OBJECT_MOVEMENT_SPEED * deltaTime;
        }
        if (MPE::Input::IsKeyPressed(MPE_KEY_UP))
        {
            SQ_POSITION[1] += OBJECT_MOVEMENT_SPEED * deltaTime;
        }
    }

    // SCENE
    SYS_CAMERA_CONTROLLER.OnUpdate(deltaTime);

    MPE::RenderPrimitive::SetClearColor(glm::vec4(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]));
    MPE::RenderPrimitive::Clear();

    MPE::Renderer::BeginScene(SYS_CAMERA_CONTROLLER.GetCamera());

    auto FLAT_COLOR_SHADER = MPE::ShaderLibrary::Get("FlatColor");

#ifdef MPE_OPENGL
    std::dynamic_pointer_cast<MPE::OpenGLShader>(FLAT_COLOR_SHADER)->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLShader>(FLAT_COLOR_SHADER)->InjectUniformFloat4("UNI_COLOR", glm::vec4(COL_1[0], COL_1[1], COL_1[2], COL_1[3]));
#elif MPE_OPENGLES
    std::dynamic_pointer_cast<MPE::OpenGLESShader>(FLAT_COLOR_SHADER)->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLESShader>(FLAT_COLOR_SHADER)->InjectUniformFloat4("UNI_COLOR", glm::vec4(COL_1[0], COL_1[1], COL_1[2], COL_1[3]));
#endif

    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            SQ_POSITION[0] = x * 0.10f;
            SQ_POSITION[1] = y * 0.10f;
            SQ_POSITION[2] = 0.0f;
            glm::mat4 SQ_TRANSFORM = glm::translate(glm::mat4(1.0f), SQ_POSITION) * SQ_SCALE;
            MPE::Renderer::Submit(FLAT_COLOR_SHADER, SYS_SQVA, SQ_TRANSFORM);
        }
    }

    auto VERTEX_BASED_COLOR_SHADER = MPE::ShaderLibrary::Get("VertexBasedColor");
    glm::mat4 TRIANGLE_TRANSFORM = glm::translate(glm::mat4(1.0f), TRIANGLE_POSITION) * TRIANGLE_SCALE;
    MPE::Renderer::Submit(VERTEX_BASED_COLOR_SHADER, SYS_VertexArray, TRIANGLE_TRANSFORM);

    auto TEXTURE_SHADER = MPE::ShaderLibrary::Get("Texture");

    glm::mat4 SQ_TRANSFORM = glm::translate(glm::mat4(1.0f), SQ_POSITION) * glm::scale(glm::mat4(1.0f), glm::vec3(SQ_VECTOR_SCALE) * 1.0f);
    TEST_TEXTURE->Bind();
    MPE::Renderer::Submit(TEXTURE_SHADER, SYS_SQVA, SQ_TRANSFORM);
    TEST_TEXTURE2->Bind();
    MPE::Renderer::Submit(TEXTURE_SHADER, SYS_SQVA, SQ_TRANSFORM);

    MPE::Renderer::EndScene();
    // MPE_INFO("TestLayer::Update");
}

void GeneralTest::OnImGuiRender()
{
    ImGui::Begin("TEST");

    ImGui::Text("SCENE VARIABLES");

    ImGui::ColorEdit4("CLEAR COLOR", CLEAR_COLOR);

    if (ImGui::Button("RESET CAMERA"))
    {
        SYS_CAMERA_CONTROLLER.Reset();
    }

    // Object manipulation
    ImGui::Text("OBJECT TRANSLATION:");
    ImGui::Checkbox("TRIANGLE:", &SHOW_TRANSFORM[0]);
    if (SHOW_TRANSFORM[0])
    {
        ImGui::SliderFloat3("", &TRIANGLE_POSITION.x, -2.5f, 2.5f);
        ImGui::Checkbox("CONTROL TRANSLATION WITH KEYS (ARROW KEYS + RIGHT SHIFT AND RIGHT CONTROL", &KEY_CONTROL_TRANSFORM[0]);
        ImGui::SliderFloat("MANIPULATE SCALE FACTOR", &TRIANGLE_SCALE_FACTOR, 0.0f, 2.0f);
        ImGui::SliderFloat3("MANIPULATE VECTORS", &TRIANGLE_VECTOR_SCALE.x, 0.0f, 2.5f);
        if (ImGui::Button("RESET TRANSLATIONS"))
        {
            TRIANGLE_POSITION[0] = 0;
            TRIANGLE_POSITION[1] = 0;
            TRIANGLE_POSITION[2] = 0;
        }
        if (ImGui::Button("RESET SCALE FACTOR"))
        {
            TRIANGLE_SCALE_FACTOR = 1.0f;
        }
        if (ImGui::Button("RESET VECTORS"))
        {
            TRIANGLE_VECTOR_SCALE[0] = 1.0f;
            TRIANGLE_VECTOR_SCALE[1] = 1.0f;
            TRIANGLE_VECTOR_SCALE[2] = 1.0f;
        }
        ComputeTriangleScale();
    }
    ImGui::Checkbox("SQUARES:", &SHOW_TRANSFORM[1]);
    if (SHOW_TRANSFORM[1])
    {
        ImGui::SliderFloat3("", &SQ_POSITION.x, -2.5f, 2.5f);
        ImGui::ColorEdit4("COLOR", COL_1);
        ImGui::Checkbox("CONTROL TRANSLATION WITH KEYS (ARROW KEYS + RIGHT SHIFT AND RIGHT CONTROL", &KEY_CONTROL_TRANSFORM[1]);
        ImGui::SliderFloat("MANIPULATE SCALE FACTOR", &SQ_SCALE_FACTOR, 0.0f, 2.0f);
        ImGui::SliderFloat3("MANIPULATE VECTORS", &SQ_VECTOR_SCALE.x, 0.0f, 2.5f);
        if (ImGui::Button("RESET TRANSLATIONS"))
        {
            SQ_POSITION[0] = 0;
            SQ_POSITION[1] = 0;
            SQ_POSITION[2] = 0;
        }
        if (ImGui::Button("RESET SCALE FACTOR"))
        {
            SQ_SCALE_FACTOR = 0.05f;
        }
        if (ImGui::Button("RESET VECTORS"))
        {
            SQ_VECTOR_SCALE[0] = 1.0f;
            SQ_VECTOR_SCALE[1] = 1.0f;
            SQ_VECTOR_SCALE[2] = 1.0f;
        }
        if (ImGui::Button("RESET COLOR"))
        {
            COL_1[0] = 1.0f;
            COL_1[1] = 0.2f;
            COL_1[2] = 0.2f;
            COL_1[3] = 1.0f;
        }
        ComputeSquareScale();
    }

    ImGui::End();
}

void GeneralTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(GeneralTest::OnKeyPressedEvent));
    SYS_CAMERA_CONTROLLER.OnEvent(event);
}

bool GeneralTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}

void GeneralTest::ComputeTriangleScale()
{
    TRIANGLE_SCALE = glm::scale(glm::mat4(1.0f), glm::vec3(TRIANGLE_VECTOR_SCALE) * TRIANGLE_SCALE_FACTOR);
}

void GeneralTest::ComputeSquareScale()
{
    SQ_SCALE = glm::scale(glm::mat4(1.0f), glm::vec3(SQ_VECTOR_SCALE) * SQ_SCALE_FACTOR);
}
