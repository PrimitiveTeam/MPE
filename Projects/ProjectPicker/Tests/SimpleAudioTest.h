#pragma once

#include "MPE.h"

#include "MPE/Renderer/Shaders/ShaderLibrary.h"

#include <imgui.h>
#include <string>

class SimpleAudioTest : public MPE::Layer
{
  public:
    SimpleAudioTest();

    virtual ~SimpleAudioTest() = default;

    virtual void OnUpdate(MPE::Time deltatime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

  private:
    MPE::SCOPE<std::string> m_LayerName;

    // Scene
    float CLEAR_COLOR[4];

    // Audio
    MPE::WavSoundPlayer m_SoundPlayer;
};
