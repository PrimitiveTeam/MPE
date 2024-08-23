#pragma once

#include "MPE.h"
#include "MPEECS.h"
#include "MPEEDITOR.h"

#include <imgui.h>
#include <string>
#include <vector>

class SceneTest : public MPE::Layer
{
  public:
    SceneTest();

    virtual ~SceneTest() = default;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

  private:
    MPE::SCOPE<std::string> m_layerName;

    // Scene
    MPE::SCOPE<MPE::SceneManager> m_sceneManager;
    MPE::REF<MPE::Scene> m_scene;
};
