#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/App/Layers/Layer.h"

namespace MPE
{
class MPE_API OpenGLESDebugGuiLayer : public MPE::Layer
{
  public:
    OpenGLESDebugGuiLayer();

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(MPE::Time deltaTime) override;

    void OnImGuiRender() override;

    void OnEvent(MPE::Event& event) override;

  private:
    void DebugMenu();

    void GraphicsSettings();

    void DisplayRefs();

  private:
};
}