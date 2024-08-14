#include "SimpleAudioTest.h"
#include "MPE/MPEPCH.h"

#include <glm/gtc/matrix_transform.hpp>

SimpleAudioTest::SimpleAudioTest() : Layer("SimpleAudioTest"), CLEAR_COLOR{0.5f, 0.25f, 0.5f}, m_SoundPlayer("Data/Sounds/Sound.wav")
{
    m_SoundPlayer.Play();
}

void SimpleAudioTest::OnUpdate(MPE::Time deltatime)
{
    MPE::RenderPrimitive::SetClearColor(glm::vec4(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]));
    MPE::RenderPrimitive::Clear();
}

void SimpleAudioTest::OnImGuiRender()
{
    ImGui::Begin("TEST");

    ImGui::Text("SCENE VARIABLES");

    ImGui::ColorEdit4("CLEAR COLOR", CLEAR_COLOR);

    if (ImGui::Button("Play Sound"))
    {
        m_SoundPlayer.Play();
    }

    ImGui::End();
}

void SimpleAudioTest::OnEvent(MPE::Event &event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::KeyPressedEvent>(MPE_BIND_EVENT_FUNCTION(SimpleAudioTest::OnKeyPressedEvent));
}

bool SimpleAudioTest::OnKeyPressedEvent(MPE::KeyPressedEvent &event)
{
    return false;
}