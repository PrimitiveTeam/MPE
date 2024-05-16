#pragma once

#include "MPE/App/Layers/Layer.h"
#include "MPE/App/Layers/LayerStack.h"
#include "MPE/App/Window.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Log/Log.h"

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
class MPE_API App : public std::enable_shared_from_this<App>
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

    inline REF<App> GetApp() { return SYS_Instance; }
    inline REF<Window> GetWindow() { return SYS_Window; }

    inline void Shutdown() { SYS_Running = false; }

  private:
    REF<App> SYS_Instance;
    REF<Window> SYS_Window;
    REF<LayerStack> SYS_LayerStack;
    REF<Log> SYS_Log;

    bool SYS_Running = true;
    bool SYS_Minimized = false;
};

static REF<App> CreateApp();
}