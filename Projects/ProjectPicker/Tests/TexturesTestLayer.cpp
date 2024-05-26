#include "TexturesTestLayer.h"

#include "MPE/App/Window.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TexturesTestLayer::TexturesTestLayer() : Layer("TexturesTestLayer"), SYS_CAMERA_CONTROLLER(1280.0f / 720.0f, true) {}

void TexturesTestLayer::OnAttach()
{
    TEST_TEXTURE = MPE::Texture2D::Create("Data/Textures/TEST_TEXTURE.png");
}

void TexturesTestLayer::OnDetach() {}

void TexturesTestLayer::OnUpdate(MPE::Time deltatime)
{
    MPE_PROFILE_FUNCTION();

    {
        MPE_PROFILE_SCOPE("SYS_CAMERA_CONTROLLER.OnUpdate()");
        SYS_CAMERA_CONTROLLER.OnUpdate(deltatime);
    }

    MPE::RenderPrimitive::SetClearColor(CLEAR_COLOR);
    MPE::RenderPrimitive::Clear();

    MPE::Renderer2D::BeginScene(SYS_CAMERA_CONTROLLER.GetCamera());

    MPE::Renderer2D::DrawQuad({0.5f, 0.0f}, {0.5f, 0.5f}, SQUARE_COLOR);
    MPE::Renderer2D::DrawQuad({-0.5f, 0.0f}, {0.5f, 0.5f}, {0.0f, 0.0f, 0.0f, 1.0f});
    MPE::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {1.0f, 1.0f}, TEST_TEXTURE, 10.0f);

    MPE::Renderer2D::EndScene();
}

void TexturesTestLayer::OnImGuiRender()
{
    ImGui::Begin("SANDBOX 2D");
    ImGui::ColorEdit4("CLEAR COLOR", glm::value_ptr(CLEAR_COLOR));
    ImGui::ColorEdit4("COLOR", glm::value_ptr(SQUARE_COLOR));
    if (ImGui::Button("RESET CAMERA"))
    {
        SYS_CAMERA_CONTROLLER.Reset();
    }

    if (ImGui::Button("TOGGLE VSYNC"))
    {
        MPE::App::GetApp().GetWindow()->ToggleVSync();
    }

    ImGui::Text("VSYNC: %s", MPE::App::GetApp().GetWindow()->IsVSync() ? "ON" : "OFF");
    ImGui::Text("%.3f ms/frame (%.1f FPS)", MPE::Renderer::GetFPS_MS().MS, MPE::Renderer::GetFPS_MS().FPS);

    ImGui::End();
}

void TexturesTestLayer::OnEvent(MPE::Event &event)
{
    SYS_CAMERA_CONTROLLER.OnEvent(event);
}