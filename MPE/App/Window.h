#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Events/Event.h"
#include "WindowProps.h"
#include "MPE/Renderer/GraphicalContext.h"

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
    virtual int GetWindowPositionX() const = 0;
    virtual int GetWindowPositionY() const = 0;

    virtual void SetEventCallback(const EventCallbackFn &callback) = 0;

    virtual void ToggleFullScreen() = 0;
    virtual void GoFullScreen() = 0;
    virtual void GoWindowed() = 0;

    virtual void SetLastWindowSize(int width, int height) = 0;
    virtual void SaveWindowSizeAndPosition() = 0;
    virtual void RestoreWindowSizeAndPosition() = 0;

    virtual void SetLastWindowPosition(int x, int y) = 0;
    virtual void SaveWindowPosition() = 0;
    virtual void RestoreWindowPosition() = 0;

    virtual void *GetNativeWindow() const = 0;

#ifdef MPE_OPENGL
    inline virtual GraphicalContext *GetNativeGLContext() const = 0;
#endif

#ifdef MPE_OPENGLES
    inline virtual GraphicalContext *GetNativeGLESContext() const = 0;
#endif

    static REF<Window> CreateNativeWindow(const WindowProps &props = WindowProps());
};
}