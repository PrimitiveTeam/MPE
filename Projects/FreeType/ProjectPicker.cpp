#include "MPE/EntryPoint.h"
#include "MPE/MPE.h"

#include "Platform/OpenGL/OpenGLSettings.h"
#include "Platform/OpenGL/Shaders/OpenGLShader.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// opengl
// #include <glad/glad.h>

const char* staticFontPath = "Data/Fonts/Hack_v3_003/Hack-Regular.ttf";

struct Character
{
    MPE::REF<MPE::Texture2D> Texture;  // Texture ID handle of the glyph texture
    glm::ivec2 Size;                   // Size of glyph
    glm::ivec2 Bearing;                // Offset from baseline to left/top of glyph
    uint32_t Advance;                  // Offset to advance to next glyph
};

void CheckGLError(const char* stmt, const char* fname, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error " << err << ", at " << fname << ":" << line << " - for " << stmt << std::endl;
        exit(1);
    }
}

#define GL_CHECK(stmt)                           \
    do                                           \
    {                                            \
        stmt;                                    \
        CheckGLError(#stmt, __FILE__, __LINE__); \
    } while (0)

class TextRenderer
{
    TextRenderer(const std::string& fontPath, int fontSize)
    {
        LoadFont(fontPath, fontSize);
        TextShader = MPE::Shader::Create("Data/Shaders/OpenGL/Text.glsl");

        SYS_VertexArray = MPE::VertexArray::Create();

        MPE::REF<MPE::VertexBuffer> vertexBuffer;
        float vertices[6 * 4] = {0.0f};  // Initialize with zeros
        vertexBuffer = MPE::VertexBuffer::Create(vertices, sizeof(vertices));
        vertexBuffer->SetLayout({{MPE::ShaderDataType::Vec4, "ATTR_POS"}});
        SYS_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[6] = {0, 1, 2, 3, 4, 5};
        MPE::REF<MPE::IndexBuffer> indexBuffer;
        indexBuffer = MPE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        SYS_VertexArray->SetIndexBuffer(indexBuffer);
    }

    void LoadFont(const std::string& fontPath, int fontSize)
    {
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {
            std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            return;
        }

        FT_Face face;
        if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
        {
            std::cerr << "ERROR::FREETYPE: Failed to load font from " << fontPath << std::endl;
            return;
        }

        FT_Set_Pixel_Sizes(face, 0, fontSize);
        // GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));  // Disable byte-alignment restriction

        for (unsigned char c = 0; c < 128; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cerr << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
                continue;
            }

            MPE::REF<MPE::Texture2D> texture = MPE::Texture2D::Create(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);

            Character character = {texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                                   glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), static_cast<uint32_t>(face->glyph->advance.x)};
            Characters.insert(std::pair<char, Character>(c, character));
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    void RenderText(const std::string& text, float x, float y, float scale, glm::vec3 color, const glm::mat4& projection)
    {
        TextShader->Bind();
        std::dynamic_pointer_cast<MPE::OpenGLShader>(TextShader)->InjectUniformFloat3("textColor", color);
        std::dynamic_pointer_cast<MPE::OpenGLShader>(TextShader)->InjectUniformMat4("projection", projection);

        for (auto c = text.begin(); c != text.end(); c++)
        {
            Character ch = Characters[*c];

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;

            float vertices[6][4] = {{xpos, ypos + h, 0.0f, 0.0f}, {xpos, ypos, 0.0f, 1.0f},     {xpos + w, ypos, 1.0f, 1.0f},
                                    {xpos, ypos + h, 0.0f, 0.0f}, {xpos + w, ypos, 1.0f, 1.0f}, {xpos + w, ypos + h, 1.0f, 0.0f}};

            SYS_VertexArray->GetVertexBuffers()[0]->SetData(vertices, sizeof(vertices));
            ch.Texture->Bind();

            glm::mat4 transform = glm::mat4(1.0f);
            MPE::Renderer::Submit(TextShader, SYS_VertexArray, transform);

            x += (ch.Advance >> 6) * scale;  // Advance cursors for next glyph (2^6 = 64)
        }
    }

  public:
    std::map<char, Character> Characters;
    MPE::REF<MPE::Shader> TextShader;
    MPE::REF<MPE::VertexArray> SYS_VertexArray;
};

class DebugGuiLayer : public MPE::Layer
{
  public:
    DebugGuiLayer() : Layer("DebugGuiLayer"), SYS_CAMERA_CONTROLLER(1920.0f / 1080.0f, true), textRenderer(staticFontPath, 48) {}

    void OnAttach() override {}

    void OnDetach() override {}

    void OnUpdate(MPE::Time deltaTime) override
    {
        // textRenderer = new TextRenderer(staticFontPath, 48);

        MPE::RenderPrimitive::SetClearColor(glm::vec4(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]));
        MPE::RenderPrimitive::Clear();

        MPE::Renderer::BeginScene(SYS_CAMERA_CONTROLLER.GetCamera());

        // Render text
        // textRenderer->RenderText("Hello, FreeType!", 25.0f, 25.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        textRenderer.RenderText("Hello, FreeType!", 25.0f, 25.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

        MPE::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoSavedSettings);

        DebugMenu();

        GraphicsSettings();

        ImGui::ColorEdit4("CLEAR COLOR", CLEAR_COLOR);

        DisplayRefs();

        ImGui::End();
    }

    void OnEvent(MPE::Event& event) override {}

  private:
    void DebugMenu()
    {
        ImGui::Separator();

        // GetFPS_MS from App/Renderer
        // Display FPS/ms
        auto fps_ms = MPE::App::GetFPS_MS();
        ImGui::Text("FPS: %.1f", fps_ms.FPS);
        ImGui::Text("MS: %.3f", fps_ms.MS);
    }

    void GraphicsSettings()
    {
        ImGui::Separator();

        ImGui::Text("Graphics Settings");
        // Retrieve RenderSettings
        auto api = MPE::RendererAPI::GetGraphicsAPI();
        switch (api)
        {
            case MPE::RendererAPI::API::OpenGL:
                ImGui::Text("Graphics API: OpenGL");
                break;
            case MPE::RendererAPI::API::OpenGLES:
                ImGui::Text("Graphics API: OpenGLES");
                break;
            default:
                MPE_CORE_ASSERT(false, "NO RENDERER API SELECTED.");
        }
        // auto settings = dynamic_cast<MPE::OpenGLSettings*>(MPE::RenderPrimitive::GetSettings());
        auto settings = MPE::RenderPrimitive::GetSettings();
        // Display RenderSettings (vsync, blend, depthTest)

        ImGui::Text("Current Vsync: %s", settings->GetVsync() ? "Enabled" : "Disabled");

        bool vsync = settings->GetVsync();
        if (ImGui::Checkbox("VSync", &vsync))
        {
            settings->SetVsync(vsync);
        }

        bool limitFPS = settings->GetLimitFPS();
        if (ImGui::Checkbox("Limit FPS", &limitFPS))
        {
            settings->SetLimitFPS(limitFPS);
        }

        int maxFPS = settings->GetMaxFPS();
        if (ImGui::SliderInt("Max FPS", &maxFPS, 1, 120))
        {
            settings->SetMaxFPS(maxFPS);
        }

        bool blend = settings->GetBlend();
        if (ImGui::Checkbox("Blend", &blend))
        {
            settings->SetBlend(blend);
        }

        bool depthTest = settings->GetDepthTest();
        if (ImGui::Checkbox("Depth Test", &depthTest))
        {
            settings->SetDepthTest(depthTest);
        }

        if (api == MPE::RendererAPI::API::OpenGL)
        {
            bool polygonMode = dynamic_cast<MPE::OpenGLSettings*>(settings)->GetPolygonMode();
            if (ImGui::Checkbox("Polygon Mode", &polygonMode))
            {
                dynamic_cast<MPE::OpenGLSettings*>(settings)->SetPolygonMode(polygonMode);
            }
        }
    }

    void DisplayRefs()
    {
        ImGui::Separator();

        ImGui::Text("Total References: %d", MPE::ReferenceTracker::getInstance().GetTotalReferences());

        if (ImGui::BeginListBox("References"))
        {
            auto refs = MPE::ReferenceTracker::getInstance().GetReferences();
            for (const auto& ref : refs)
            {
                ImGui::Text(ref.c_str());
            }
            ImGui::EndListBox();
        }

        if (ImGui::BeginListBox("Scope References"))
        {
            auto refs = MPE::ReferenceTracker::getInstance().GetScopeReferences();
            for (const auto& ref : refs)
            {
                ImGui::Text(ref.c_str());
            }
            ImGui::EndListBox();
        }
    }

  private:
    float CLEAR_COLOR[4];
    // TextRenderer* textRenderer;
    TextRenderer textRenderer;
    MPE::OrthographicCameraController SYS_CAMERA_CONTROLLER;
};

class ProjectPicker : public MPE::App
{
  public:
    ProjectPicker()
    {
#ifdef MPE_DYNAMIC_LIBRARY
        ImGui::SetCurrentContext(this->GetImGuiContext());
#endif
        PushOverlay(MPE::NEWREF<DebugGuiLayer>());
        // PushLayer(MPE::NEWREF<PONG::Pong>());
    }

    ~ProjectPicker() {}
};

MPE::App* MPE::CreateApp()
{
    return new ProjectPicker();
}