#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/App/Layers/Layer.h"
#include "MPE/App/Layers/LayerStack.h"
#include "MPE/App/Window.h"
#include "MPE/Log/Log.h"
#include "MPE/Events/EventApp.h"
#include "MPE/Events/EventGraphics.h"
#include "MPE/Vendor/ImGui/ImGuiLayer.h"
#include "MPE/Renderer/Renderer.h"
#include "MPE/Sound/OpenALContext.h"

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

    virtual void Run();

    void OnEvent(Event &event);

    void PushLayer(const REF<Layer> &layer);
    void PopLayer();
    void PopLayer(const REF<Layer> &layer);
    void PopAllLayers();

    void PushOverlay(const REF<Layer> &overlay);
    void PopOverlay();
    void PopOverlay(const REF<Layer> &overlay);
    void PopAllOverlays();

    inline void Shutdown() { m_isAppRunning = false; }

    inline static App &GetApp() { return *m_appInstance; }
    inline REF<Window> GetWindow() { return m_appWindow; }
    inline OpenALContext &GetOpenALContext() { return m_openalContext; }

#ifdef MPE_DYNAMIC_LIBRARY
    ImGuiContext *GetImGuiContext() { return m_imguiLayer->GetImGuiContext(); }
#endif

    inline static WindowFpsMs GetFpsMs() { return Renderer::GetFpsMs(); }

    inline void ToggleGUI() { m_isGuiOn = !m_isGuiOn; }
    inline bool IsGUIEnabled() { return m_isGuiOn; }

  private:
    bool OnWindowClose(WindowCloseEvent &e);
    bool OnWindowResize(WindowResizeEvent &e);
    bool OnWindowMoved(WindowMovedEvent &e);
    bool OnGraphicsSettingsUpdate(GraphicsSettingsChangedEvent &e);
    void ToggleFullscreen();
    void ToggleDeltaTime();
    void ChangeTargetFPS(int fps);

    static App *m_appInstance;
    REF<ImGuiLayer> m_imguiLayer;
    REF<Window> m_appWindow;
    REF<LayerStack> m_layerStack;
    REF<Log> m_log;
    OpenALContext &m_openalContext;

    bool m_isAppRunning = true;
    bool m_isAppMinimized = false;
    bool m_isAppPaused = false;
    bool m_isGuiOn = true;

    float m_lastFrameTime = 0.0f;
    bool m_isDeltaTimePaused = false;

    int m_targetFPS = -1;
    int m_frameTimeMs = 1000 / m_targetFPS;
};

App *CreateApp();
}