#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/App/Layers/Layer.h"
#include "MPE/App/Layers/LayerStack.h"
#include "MPE/App/Window.h"
#include "MPE/Log/Log.h"
#include "MPE/Events/EventApp.h"
#include "MPE/Vendor/ImGui/ImGuiLayer.h"
#include "MPE/Renderer/Renderer.h"

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
    void PopLayer(const REF<Layer> &Layer);
    void PopAllLayers();

    void PushOverlay(const REF<Layer> &Overlay);
    void PopOverlay();
    void PopOverlay(const REF<Layer> &Overlay);
    void PopAllOverlays();

    inline static App &GetApp() { return *SYS_APP_Instance; }
    inline REF<Window> GetWindow() { return SYS_APP_Window; }

#ifdef MPE_DYNAMIC_LIBRARY
    ImGuiContext *GetImGuiContext() { return SYS_ImGuiLayer->GetImGuiContext(); }
#endif

    inline void Shutdown() { SYS_APP_Running = false; }

    inline static WINDOW_FPS_MS GetFPS_MS() { return Renderer::GetFPS_MS(); }

    inline void ToggleGUI() { SYS_GUI = !SYS_GUI; }
    inline bool IsGUIEnabled() { return SYS_GUI; }

  private:
    bool OnWindowClose(WindowCloseEvent &e);
    bool OnWindowResize(WindowResizeEvent &e);
    void ToggleFullscreen();
    void ToggleDeltaTime();

    static App *SYS_APP_Instance;
    REF<ImGuiLayer> SYS_ImGuiLayer;
    REF<Window> SYS_APP_Window;
    REF<LayerStack> SYS_LayerStack;
    REF<Log> SYS_Log;

    bool SYS_APP_Running = true;
    bool SYS_Minimized = false;
    bool SYS_GUI = true;

    float SYS_LAST_FRAME_TIME = 0.0f;
    bool IsDeltaTimePaused = false;
};

App *CreateApp();
}