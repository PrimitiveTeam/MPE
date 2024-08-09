#include "MPE/MPE.h"

#include "MPE/EntryPoint.h"

// TEMP
#ifdef MPE_OPENGL
#    include "Platform/OpenGL/Shaders/OpenGLShader.h"
#    include "Platform/OpenGL/OpenGLSettings.h"
#    include "Platform/OpenGL/Utilities/OpenGLUtilities.h"
#elif MPE_OPENGLES
#    include "Platform/OpenGLES/Shaders/OpenGLESShader.h"
#    include "Platform/OpenGLES/OpenGLESSettings.h"
#endif
#include "MPE/Renderer/Shaders/ShaderLibrary.h"
#include "MPE/Renderer/RendererUtilities.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
// #include <glad/glad.h>
// #include <glfw/glfw3.h>

#include "Tests/ClearColorTest.h"
#include "Tests/SimpleTriangleTest.h"
#include "Tests/SimpleRectangleTest.h"
#include "Tests/ColorTriangleTest.h"
#include "Tests/ColorAnimationTriangleTest.h"
#include "Tests/TextureRectangleTest.h"
#include "Tests/TriangleTransformationTest.h"
#include "Tests/RectangleTransformationTest.h"
#include "Tests/SimpleCubeTest.h"

#include "Tests/TexturesTest.h"
#include "Tests/GeneralTest.h"

#include "Tests/GridTest.h"

class DebugGuiLayer : public MPE::Layer
{
  public:
    DebugGuiLayer() : Layer("DebugGuiLayer")  //,
    // m_OpenGLUtilities(MPE::OpenGLUtilities::getInstance())
    {
    }

    void OnAttach() override {}

    void OnDetach() override {}

    void OnUpdate(MPE::Time deltaTime) override {}

    void OnImGuiRender() override
    {
        ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoSavedSettings);

        DebugMenu();

        GraphicsSettings();

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

        ImGui::Separator();
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
#ifdef MPE_OPENGL
            bool polygonMode = dynamic_cast<MPE::OpenGLSettings*>(settings)->GetPolygonMode();
            if (ImGui::Checkbox("Polygon Mode", &polygonMode))
            {
                dynamic_cast<MPE::OpenGLSettings*>(settings)->SetPolygonMode(polygonMode);
            }

            bool faceCulling = dynamic_cast<MPE::OpenGLSettings*>(settings)->GetFaceCulling();
            if (ImGui::Checkbox("Face Culling", &faceCulling))
            {
                dynamic_cast<MPE::OpenGLSettings*>(settings)->SetFaceCulling(faceCulling);
            }

            bool debugOutput = dynamic_cast<MPE::OpenGLSettings*>(settings)->GetDebugOutput();
            if (ImGui::Checkbox("Debug Output", &debugOutput))
            {
                dynamic_cast<MPE::OpenGLSettings*>(settings)->SetDebugOutput(debugOutput);
            }
#endif
        }
    }

    void DisplayRefs()
    {
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
    // MPE::OpenGLUtilities& m_OpenGLUtilities;
};

class ProjectPickerGuiLayer : public MPE::Layer
{
  public:
    ProjectPickerGuiLayer() : Layer("ProjectPickerGuiLayer")  //, m_OpenGLUtilities(MPE::OpenGLUtilities::getInstance())
    {
    }

    void OnAttach() override {}

    void OnDetach() override {}

    void OnUpdate(MPE::Time deltaTime) override { RenderClearColorScene(); }

    void OnImGuiRender() override
    {
        // PrintLayerStatus();

        ImGui::Begin("Scene Selection", nullptr, ImGuiWindowFlags_NoSavedSettings);

        SceneControl();

        // Add more buttons for other layers here

        ImGui::End();
    }

    void OnEvent(MPE::Event& event) override {}

  private:
    void SceneControl()
    {
        // If any layer is active then we only want to show the close button
        if (std::any_of(m_Layers.begin(), m_Layers.end(), [](bool layer) { return layer; }))
        {
            if (ImGui::Button("Close Layer"))
            {
                for (int i = 0; i < m_Layers.size(); i++)
                {
                    if (m_Layers[i])
                    {
                        m_Layers[i] = false;
                        MPE::App::GetApp().PopLayer(m_LayerRefs[i]);
                        m_LayerRefs[i] = nullptr;
                    }
                }
            }
        }
        else
        {
            if (ImGui::Button("Open Clear Color Test"))
            {
                m_Layers[0] = true;
                m_LayerRefs[0] = MPE::NEWREF<ClearColorTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[0]);
            }

            if (ImGui::Button("Open Simple Triangle Test"))
            {
                m_Layers[1] = true;
                m_LayerRefs[1] = MPE::NEWREF<SimpleTriangleTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[1]);
            }

            if (ImGui::Button("Open Simple Rectangle Test"))
            {
                m_Layers[2] = true;
                m_LayerRefs[2] = MPE::NEWREF<SimpleRectangleTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[2]);
            }

            if (ImGui::Button("Open Color Triangle Test"))
            {
                m_Layers[3] = true;
                m_LayerRefs[3] = MPE::NEWREF<ColorTriangleTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[3]);
            }

            if (ImGui::Button("Open Color Animation Triangle Test"))
            {
                m_Layers[4] = true;
                m_LayerRefs[4] = MPE::NEWREF<ColorAnimationTriangleTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[4]);
            }

            if (ImGui::Button("Open Texture Rectangle Test"))
            {
                m_Layers[5] = true;
                m_LayerRefs[5] = MPE::NEWREF<TextureRectangleTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[5]);
            }

            if (ImGui::Button("Open Triangle Transformation Test"))
            {
                m_Layers[6] = true;
                m_LayerRefs[6] = MPE::NEWREF<TriangleTransformationTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[6]);
            }

            if (ImGui::Button("Open Rectangle Transformation Test"))
            {
                m_Layers[7] = true;
                m_LayerRefs[7] = MPE::NEWREF<RectangleTransformationTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[7]);
            }

            if (ImGui::Button("Open Simple Cube Test"))
            {
                m_Layers[8] = true;
                m_LayerRefs[8] = MPE::NEWREF<SimpleCubeTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[8]);
            }

            if (ImGui::Button("Open Grid Test"))
            {
                m_Layers[9] = true;
                m_LayerRefs[9] = MPE::NEWREF<GridTest>();
                MPE::App::GetApp().PushLayer(m_LayerRefs[9]);
            }

            // if (ImGui::Button("Open General Layer"))
            // {
            //     m_Layers[1] = true;
            //     m_LayerRefs[1] = MPE::NEWREF<GeneralTest>();
            //     MPE::App::GetApp().PushLayer(m_LayerRefs[0]);
            // }

            // if (ImGui::Button("Open Textures Layer"))
            // {
            //     m_Layers[2] = true;
            //     m_LayerRefs[2] = MPE::NEWREF<TexturesTest>();
            //     MPE::App::GetApp().PushLayer(m_LayerRefs[1]);
            // }
        }
    }

    void RenderClearColorScene()
    {
        // If any layer is active, do not execute this
        if (std::any_of(m_Layers.begin(), m_Layers.end(), [](bool layer) { return layer; })) return;

        m_RendererUtilities.DrawClearColorScene();
    }

    void PrintLayerStatus()
    {
        // Using array
        // MPE_CORE_INFO("General Layer: {0}", m_Layers[0] ? "true" : "false");
        // MPE_CORE_INFO("Textures Layer: {0}", m_Layers[1] ? "true" : "false");
    }

  private:
    static const size_t MAX_LAYERS = 10;
    std::array<bool, MAX_LAYERS> m_Layers = {false};
    MPE::REF<MPE::Layer> m_LayerRefs[MAX_LAYERS];
    MPE::RendererUtilities m_RendererUtilities = MPE::RendererUtilities();
};

class ProjectPicker : public MPE::App
{
  public:
    ProjectPicker()
    {
#ifdef MPE_DYNAMIC_LIBRARY
        ImGui::SetCurrentContext(this->GetImGuiContext());
#endif
        // PushLayer(MPE::NEWREF<MainMenuLayer>());
        PushLayer(MPE::NEWREF<DebugGuiLayer>());
        PushOverlay(MPE::NEWREF<ProjectPickerGuiLayer>());
    }

    ~ProjectPicker() {}
};

MPE::App* MPE::CreateApp()
{
    return new ProjectPicker();
}