#pragma once

#include "MPE/App/Layers/Layer.h"
#include "MPE/App/Layers/LayerStack.h"
#include "MPE/App/Window.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Log/Log.h"
#include "MPE/Events/EventApp.h"
#include "MPE/Vendor/ImGui/ImGuiLayer.h"

#include <memory>

/**
 * @file App.h
 * @brief App class for the MPE engine.
 * @date 2024-05-05
 * @author Sebastian Termen
 */

namespace MPE
{
/**
 * @brief App class for the MPE engine.
 * @details This class is used to define the application for the MPE engine.
 * @date 2024-05-05
 * @see EntryPoint.h
 */
class MPE_API App
{
  public:
    App();
    virtual ~App();
    void Initialize();

    virtual void Run();
    void OnEvent(Event &SYS_Event);

    void PushLayer(const REF<Layer> &Layer);
    void PopLayer();
    void PopAllLayers();

    void PushOverlay(const REF<Layer> &Overlay);
    void PopOverlay();
    void PopAllOverlays();

    inline static App &GetApp() { return *SYS_APP_Instance; }
    inline REF<Window> GetWindow() { return SYS_APP_Window; }

    inline void Shutdown() { SYS_APP_Running = false; }

  private:
    bool OnWindowClose(WindowCloseEvent &e);
    bool OnWindowResize(WindowResizeEvent &e);

    static App *SYS_APP_Instance;
    REF<ImGuiLayer> SYS_ImGuiLayer;
    REF<Window> SYS_APP_Window;
    REF<LayerStack> SYS_LayerStack;
    REF<Log> SYS_Log;

    bool SYS_APP_Running = true;
    bool SYS_Minimized = false;

    float SYS_LAST_FRAME_TIME = 0.0f;
};

App *CreateApp();
}