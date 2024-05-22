#include "MPE/MPE.h"

#include "MPE/EntryPoint.h"

// TEMP
#include "MPE/Platform/OpenGL/Shaders/OpenGLShader.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Sandbox2D/Sandbox2D.h"

class TestLayer : public MPE::Layer
{
  private:
    // TRIANGLE
    MPE::REF<MPE::Shader> SYS_Shader;
    MPE::REF<MPE::VertexArray> SYS_VertexArray;

    // SQUARE
    MPE::REF<MPE::Shader> SYS_SQSH;
    MPE::REF<MPE::VertexArray> SYS_SQVA;

    // TEXTURES;
    MPE::REF<MPE::Texture2D> TEST_TEXTURE;
    MPE::REF<MPE::Texture2D> TEST_TEXTURE2;

    // SHADER LIBRARY
    MPE::ShaderLibrary SYS_SHADER_LIBRARY;

    // SCENE
    float CLEAR_COLOR[4];

    // CAMERA
    MPE::OrthographicCameraController SYS_CAMERA_CONTROLLER;

    // TRANSFORM
    float OBJECT_MOVEMENT_SPEED = 0.75f;
    float OBJECT_ROTATION_SPEED = 25.0f;

    // TRIANGLE
    glm::vec3 TRIANGLE_POSITION;
    float TRIANGLE_SCALE_FACTOR;
    glm::vec3 TRIANGLE_VECTOR_SCALE;
    glm::mat4 TRIANGLE_SCALE;

    // SQUARE
    glm::vec3 SQ_POSITION;
    float SQ_SCALE_FACTOR;
    glm::vec3 SQ_VECTOR_SCALE;
    glm::mat4 SQ_SCALE;
    // SQUARES COLOR
    float COL_1[4] = {1.0f, 0.2f, 0.2f, 1.0f};
    glm::vec4 COL_2 = {0.2f, 0.4f, 0.2f, 1.0f};

    // IMGUI
    bool SHOW_TRANSFORM[2] = {false};
    bool KEY_CONTROL_TRANSFORM[2] = {false};

  public:
    TestLayer()
        : Layer("Test"),
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
        float vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 1.0f, 0.2f, 1.0f, 1.0f, 0.5f, -0.5f, 0.0f, 0.2f,
                                 1.0f,  1.0f,  1.0f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.2f,  1.0f};

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
        auto TEXTURE_SHADER = SYS_SHADER_LIBRARY.Load("Data/Shaders/Texture.glsl");
        auto FLAT_COLOR_SHADER = SYS_SHADER_LIBRARY.Load("Data/Shaders/FlatColor.glsl");
        auto VERTEX_BASED_COLOR_SHADER = SYS_SHADER_LIBRARY.Load("Data/Shaders/VertexBasedColor.glsl");

        // TEXTURES
        TEST_TEXTURE = MPE::Texture2D::Create("Data/Textures/TEST_TEXTURE.png");
        TEST_TEXTURE2 = MPE::Texture2D::Create("Data/Textures/TEST_TEXTURE_TRANSPARENCY_1.png");

        std::dynamic_pointer_cast<MPE::OpenGLShader>(TEXTURE_SHADER)->Bind();
        std::dynamic_pointer_cast<MPE::OpenGLShader>(TEXTURE_SHADER)->InjectUniformInt1("UNI_TEXTURE", 0);
    }

    virtual void OnUpdate(MPE::Time deltatime) override
    {
        // MPE_TRACE("Delta time: {0}s ({1}ms)", deltatime.GetSeconds(), deltatime.GetMilliSeconds());

        // OBJECT TRANSLATION
        // TRIANGLE
        if (KEY_CONTROL_TRANSFORM[0])
        {
            if (MPE::Input::IsKeyPressed(MPE_KEY_LEFT))
            {
                TRIANGLE_POSITION[0] -= OBJECT_MOVEMENT_SPEED * deltatime;
            }
            if (MPE::Input::IsKeyPressed(MPE_KEY_RIGHT))
            {
                TRIANGLE_POSITION[0] += OBJECT_MOVEMENT_SPEED * deltatime;
            }
            if (MPE::Input::IsKeyPressed(MPE_KEY_DOWN))
            {
                TRIANGLE_POSITION[1] -= OBJECT_MOVEMENT_SPEED * deltatime;
            }
            if (MPE::Input::IsKeyPressed(MPE_KEY_UP))
            {
                TRIANGLE_POSITION[1] += OBJECT_MOVEMENT_SPEED * deltatime;
            }
        }
        // SQUARE
        if (KEY_CONTROL_TRANSFORM[1])
        {
            if (MPE::Input::IsKeyPressed(MPE_KEY_LEFT))
            {
                SQ_POSITION[0] -= OBJECT_MOVEMENT_SPEED * deltatime;
            }
            if (MPE::Input::IsKeyPressed(MPE_KEY_RIGHT))
            {
                SQ_POSITION[0] += OBJECT_MOVEMENT_SPEED * deltatime;
            }
            if (MPE::Input::IsKeyPressed(MPE_KEY_DOWN))
            {
                SQ_POSITION[1] -= OBJECT_MOVEMENT_SPEED * deltatime;
            }
            if (MPE::Input::IsKeyPressed(MPE_KEY_UP))
            {
                SQ_POSITION[1] += OBJECT_MOVEMENT_SPEED * deltatime;
            }
        }

        // SCENE
        SYS_CAMERA_CONTROLLER.OnUpdate(deltatime);

        MPE::RenderPrimitive::SetClearColor(glm::vec4(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]));
        MPE::RenderPrimitive::Clear();

        MPE::Renderer::BeginScene(SYS_CAMERA_CONTROLLER.GetCamera());

        auto FLAT_COLOR_SHADER = SYS_SHADER_LIBRARY.Get("FlatColor");

        std::dynamic_pointer_cast<MPE::OpenGLShader>(FLAT_COLOR_SHADER)->Bind();
        std::dynamic_pointer_cast<MPE::OpenGLShader>(FLAT_COLOR_SHADER)->InjectUniformFloat4("UNI_COLOR", glm::vec4(COL_1[0], COL_1[1], COL_1[2], COL_1[3]));

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

        auto VERTEX_BASED_COLOR_SHADER = SYS_SHADER_LIBRARY.Get("VertexBasedColor");
        glm::mat4 TRIANGLE_TRANSFORM = glm::translate(glm::mat4(1.0f), TRIANGLE_POSITION) * TRIANGLE_SCALE;
        MPE::Renderer::Submit(VERTEX_BASED_COLOR_SHADER, SYS_VertexArray, TRIANGLE_TRANSFORM);

        auto TEXTURE_SHADER = SYS_SHADER_LIBRARY.Get("Texture");

        glm::mat4 SQ_TRANSFORM = glm::translate(glm::mat4(1.0f), SQ_POSITION) * glm::scale(glm::mat4(1.0f), glm::vec3(SQ_VECTOR_SCALE) * 1.0f);
        TEST_TEXTURE->Bind();
        MPE::Renderer::Submit(TEXTURE_SHADER, SYS_SQVA, SQ_TRANSFORM);
        TEST_TEXTURE2->Bind();
        MPE::Renderer::Submit(TEXTURE_SHADER, SYS_SQVA, SQ_TRANSFORM);

        MPE::Renderer::EndScene();
        // MPE_INFO("TestLayer::Update");
    }

    virtual void OnImGuiRender() override
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

    virtual void OnEvent(MPE::Event &event) override
    {
        SYS_CAMERA_CONTROLLER.OnEvent(event);

        MPE::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(TestLayer::OnKeyPressedEvent));
    }

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event) { return false; }

    void ComputeTriangleScale() { TRIANGLE_SCALE = glm::scale(glm::mat4(1.0f), glm::vec3(TRIANGLE_VECTOR_SCALE) * TRIANGLE_SCALE_FACTOR); }

    void ComputeSquareScale() { SQ_SCALE = glm::scale(glm::mat4(1.0f), glm::vec3(SQ_VECTOR_SCALE) * SQ_SCALE_FACTOR); }
};

class Sandbox : public MPE::App
{
  public:
    Sandbox()
    {
#ifdef MPE_DYNAMIC_LIBRARY
        ImGui::SetCurrentContext(this->GetImGuiContext());
#endif
        PushLayer(MPE::NEWREF<Sandbox2D>());
    }

    ~Sandbox() {}
};

MPE::App *MPE::CreateApp()
{
    return new Sandbox();
}