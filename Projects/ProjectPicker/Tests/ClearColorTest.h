#pragma once

#include "MPE.h"

#include "MPE/Renderer/Shaders/ShaderLibrary.h"

#include <imgui.h>
#include <string>

class ClearColorTest : public MPE::Layer
{
  public:
    ClearColorTest();

    virtual ~ClearColorTest() = default;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

  private:
    MPE::SCOPE<std::string> m_LayerName;

    // Scene
    float CLEAR_COLOR[4];
};
