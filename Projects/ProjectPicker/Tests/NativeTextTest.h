#pragma once

#include "MPE.h"
#include "MPEGFX_OPEN_GL.h"

#include <string>

class NativeTextTest : public MPE::Layer
{
  public:
    NativeTextTest();

    virtual ~NativeTextTest() = default;

    virtual void OnUpdate(MPE::Time deltatime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

  private:
    MPE::SCOPE<std::string> m_LayerName;

    // Scene
    float CLEAR_COLOR[4];

    // Camera
    MPE::OrthographicCameraController SYS_CAMERA_CONTROLLER;

    // Text
    MPE::OpenGLTextRenderer SYS_TEXT_RENDERER;

    std::string TEXT;
    float TEXT_COLOR[4];
    float TEXT_SCALE;
    float TEXT_BOX_LOCATION[2];
};
