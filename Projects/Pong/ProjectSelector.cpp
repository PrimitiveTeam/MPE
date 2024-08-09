#include "source/Pong.h"
#include "MPE/EntryPoint.h"

#ifdef MPE_OPENGL
#    include "Platform/OpenGL/OpenGLSettings.h"
#endif
#ifdef MPE_OPENGLES
#    include "Platform/OpenGLES/OpenGLESSettings.h"
#endif

class DebugGuiLayer : public MPE::Layer
{
  public:
    DebugGuiLayer() : Layer("DebugGuiLayer") {}

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
#endif
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
};

class ProjectSelector : public MPE::App
{
  public:
    ProjectSelector()
    {
#ifdef MPE_DYNAMIC_LIBRARY
        ImGui::SetCurrentContext(this->GetImGuiContext());
#endif
        PushOverlay(MPE::NEWREF<DebugGuiLayer>());
        PushLayer(MPE::NEWREF<PONG::Pong>());
    }

    ~ProjectSelector() {}
};

MPE::App* MPE::CreateApp()
{
    return new ProjectSelector();
}