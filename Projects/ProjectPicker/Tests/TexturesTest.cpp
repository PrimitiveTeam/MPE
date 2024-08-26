#include "TexturesTest.h"

#include "MPE/App/Window.h"

#include <imgui.h>
#include "MPE/Vendor/GLM/GLM.h"

TexturesTest::TexturesTest() : Layer("TexturesTest"), SYS_CAMERA_CONTROLLER(1280.0f / 720.0f, true) {}

void TexturesTest::OnAttach()
{
    TEST_TEXTURE = MPE::Texture2D::Create("Data/Textures/TEST_TEXTURE.png");
}

void TexturesTest::OnDetach() {}

void TexturesTest::OnUpdate(MPE::Time deltaTime)
{
    MPE_PROFILE_FUNCTION();

    {
        MPE_PROFILE_SCOPE("SYS_CAMERA_CONTROLLER.OnUpdate()");
        SYS_CAMERA_CONTROLLER.OnUpdate(deltaTime);
    }

    MPE::RenderPrimitive::SetClearColor(CLEAR_COLOR);
    MPE::RenderPrimitive::Clear();

    MPE::Renderer2D::BeginScene(SYS_CAMERA_CONTROLLER.GetCamera());

    MPE::Renderer2D::DrawQuad({0.5f, 0.0f}, {0.5f, 0.5f}, SQUARE_COLOR);
    MPE::Renderer2D::DrawQuad({-0.5f, 0.0f}, {0.5f, 0.5f}, {0.0f, 0.0f, 0.0f, 1.0f});
    MPE::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {1.0f, 1.0f}, TEST_TEXTURE, 10.0f);

    MPE::Renderer2D::EndScene();
}

void TexturesTest::OnImGuiRender()
{
    ImGui::Begin("SANDBOX 2D");
    ImGui::ColorEdit4("CLEAR COLOR", glm::value_ptr(CLEAR_COLOR));
    ImGui::ColorEdit4("COLOR", glm::value_ptr(SQUARE_COLOR));
    if (ImGui::Button("RESET CAMERA"))
    {
        SYS_CAMERA_CONTROLLER.Reset();
    }

    ImGui::End();
}

void TexturesTest::OnEvent(MPE::Event &event)
{
    SYS_CAMERA_CONTROLLER.OnEvent(event);
}