#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/App/Layers/Layer.h"
// #include "MPE/App/App.h"

#include <imgui.h>

namespace MPE
{
class MPE_API App;

class MPE_API ImGuiLayer : public Layer
{
  public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnImGuiRender() override;

    void Begin();
    void End();

#ifdef MPE_DYNAMIC_LIBRARY
    ImGuiContext* GetImGuiContext() { return m_imguiContext; }
#endif

  private:
    float m_time = 0.0f;
    static App* m_app;

#ifdef MPE_DYNAMIC_LIBRARY
    ImGuiContext* m_imguiContext;
#endif
};
}