#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Events/Event.h"
#include "WindowProps.h"

namespace MPE
{
// Interface API for Desktop Systems.
class MPE_API Window
{
  public:
    using EventCallbackFn = std::function<void(Event &)>;

    virtual ~Window() {}

    virtual void OnUpdate() = 0;

    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;

    virtual void SetEventCallback(const EventCallbackFn &callback) = 0;

    virtual void ToggleFullScreen() = 0;
    virtual void GoFullScreen() = 0;
    virtual void GoWindowed() = 0;

    virtual void SetLastWindowSize(int width, int height) = 0;
    virtual void SaveWindowSizeAndPosition() = 0;
    virtual void RestoreWindowSizeAndPosition() = 0;

    virtual void *GetNativeWindow() const = 0;

    static REF<Window> CreateNativeWindow(const WindowProps &props = WindowProps());
};
}