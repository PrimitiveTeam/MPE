#include "SimpleAudioTest.h"
#include "MPE/MPEPCH.h"

#include "MPE/Vendor/GLM/GLM.h"

SimpleAudioTest::SimpleAudioTest()
    : Layer("SimpleAudioTest"),
      CLEAR_COLOR{0.5f, 0.25f, 0.5f},
      m_WavSoundPlayer(new MPE::WavSoundPlayer("Data/Sounds/Sound.wav")),
      m_OggSoundPlayer(new MPE::OggSoundPlayer("Data/Sounds/Sound.ogg"))
{
    MPE_TRACE("{}", m_WavSoundPlayer->GetInfo());
    MPE_TRACE("{}", m_OggSoundPlayer->GetInfo());
}

void SimpleAudioTest::OnUpdate(MPE::Time deltaTime)
{
    MPE::RenderPrimitive::SetClearColor(glm::vec4(CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]));
    MPE::RenderPrimitive::Clear();
}

void SimpleAudioTest::OnImGuiRender()
{
    ImGui::Begin("TEST");

    ImGui::Text("SCENE VARIABLES");

    ImGui::ColorEdit4("CLEAR COLOR", CLEAR_COLOR);

    if (ImGui::Button("Play WAV Sound"))
    {
        m_WavSoundPlayer->Play();
    }

    if (ImGui::Button("Play OGG Sound"))
    {
        m_OggSoundPlayer->Play();
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