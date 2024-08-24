#include "OpenGLDebugGuiLayer.h"

#include "MPE/App/App.h"
#include "Platform/OpenGL/OpenGLSettings.h"

#include <imgui.h>

namespace MPE
{
OpenGLDebugGuiLayer::OpenGLDebugGuiLayer() : Layer("OpenGLDebugGuiLayer") {}

void OpenGLDebugGuiLayer::OnAttach() {}

void OpenGLDebugGuiLayer::OnDetach() {}

void OpenGLDebugGuiLayer::OnUpdate(MPE::Time deltaTime) {}

void OpenGLDebugGuiLayer::OnImGuiRender()
{
    ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoSavedSettings);

    DebugMenu();

    GraphicsSettings();

    DisplayRefs();

    ImGui::End();
}

void OpenGLDebugGuiLayer::OnEvent(MPE::Event& event) {}

void OpenGLDebugGuiLayer::DebugMenu()
{
    ImGui::Separator();

    // GetFPS_MS from App/Renderer
    // Display FPS/ms
    auto fps_ms = MPE::App::GetFpsMs();
    ImGui::Text("FPS: %.1f", fps_ms.fps);
    ImGui::Text("MS: %.3f", fps_ms.ms);

    ImGui::Separator();
}

void OpenGLDebugGuiLayer::GraphicsSettings()
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

    auto settings = dynamic_cast<MPE::OpenGLSettings*>(MPE::RenderPrimitive::GetSettings());

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

    bool polygonMode = dynamic_cast<MPE::OpenGLSettings*>(settings)->GetPolygonMode();
    if (ImGui::Checkbox("Polygon Mode", &polygonMode))
    {
        settings->SetPolygonMode(polygonMode);
    }

    bool faceCulling = settings->GetFaceCulling();
    if (ImGui::Checkbox("Face Culling", &faceCulling))
    {
        settings->SetFaceCulling(faceCulling);
    }

    bool debugOutput = settings->GetDebugOutput();
    if (ImGui::Checkbox("Debug Output", &debugOutput))
    {
        settings->SetDebugOutput(debugOutput);
    }
}

void OpenGLDebugGuiLayer::DisplayRefs()
{
    ImGui::Text("Total References: %u", (unsigned int) MPE::ReferenceTracker::getInstance().GetTotalReferences());

    if (ImGui::BeginListBox("References"))
    {
        auto refs = MPE::ReferenceTracker::getInstance().GetReferences();
        for (const auto& ref : refs)
        {
            ImGui::Text("%s", ref.c_str());
        }
        ImGui::EndListBox();
    }

    if (ImGui::BeginListBox("Scope References"))
    {
        auto refs = MPE::ReferenceTracker::getInstance().GetScopeReferences();
        for (const auto& ref : refs)
        {
            ImGui::Text("%s", ref.c_str());
        }
        ImGui::EndListBox();
    }
}
}