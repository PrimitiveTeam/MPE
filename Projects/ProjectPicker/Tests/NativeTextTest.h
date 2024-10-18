#pragma once

#include "MPE.h"
#include "MPEEDITOR.h"
#include "MPEECS.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#endif

#include <string>

class NativeTextTest : public MPE::Layer
{
  public:
    NativeTextTest();

    virtual ~NativeTextTest() = default;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

  private:
    MPE::SCOPE<std::string> m_LayerName;

    // Scene
    float CLEAR_COLOR[4];

    MPE::REF<MPE::ECS::ECS> m_ECS;

    // Camera
    MPE::REF<MPE::Camera> SYS_CAMERA_CONTROLLER;

    // Text
#ifdef MPE_OPENGL
    MPE::OpenGLTextRenderer SYS_TEXT_RENDERER;
#elif MPE_OPENGLES
    MPE::OpenGLESTextRenderer SYS_TEXT_RENDERER;
#endif

    std::string TEXT;
    float TEXT_COLOR[4];
    float TEXT_SCALE;
    float TEXT_BOX_LOCATION[2];
};
