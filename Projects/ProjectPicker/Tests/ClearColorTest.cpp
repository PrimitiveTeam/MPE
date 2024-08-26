#include "ClearColorTest.h"
#include "MPE/MPEPCH.h"

#include "MPE/Vendor/GLM/GLM.h"

ClearColorTest::ClearColorTest() : Layer("ClearColorTest"), CLEAR_COLOR{0.5f, 0.25f, 0.5f} {}

void ClearColorTest::OnUpdate(MPE::Time deltaTime)
{
    MPE::RenderPrimitive::SetClearColor(glm::vec4(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]));
    MPE::RenderPrimitive::Clear();
}

void ClearColorTest::OnImGuiRender()
{
    ImGui::Begin("TEST");

    ImGui::Text("SCENE VARIABLES");

    ImGui::ColorEdit4("CLEAR COLOR", CLEAR_COLOR);

    ImGui::End();
}

void ClearColorTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(ClearColorTest::OnKeyPressedEvent));
}

bool ClearColorTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}