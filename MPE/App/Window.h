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

    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;

    virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
    virtual void ToggleVSync() = 0;
    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;
    virtual void SetFrameRate(unsigned int frameRate) = 0;

    virtual void *GetNativeWindow() const = 0;

    static REF<Window> CreateNativeWindow(const WindowProps &props = WindowProps());
};
}