#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/App/Window.h"
#include "Platform/macOS/App/WindowMonitors.h"

#ifdef MPE_OPENGL
#    include "Platform/OpenGL/OpenGLContext.h"
#endif
#ifdef MPE_OPENGLES
#    include "Platform/OpenGLES/OpenGLESContext.h"
#endif

struct GLFWwindow;

namespace MPE
{
class MPE_API macOSWindow : public Window
{
  public:
    macOSWindow(const WindowProps &props);
    virtual ~macOSWindow();

    void OnUpdate() override;

    inline int GetWidth() const override { return SYS_Data.Width; }
    inline int GetHeight() const override { return SYS_Data.Height; }
    virtual inline int GetWindowPositionX() const override { return SYS_Data.WindowPositionX; }
    virtual inline int GetWindowPositionY() const override { return SYS_Data.WindowPositionY; }

    inline void SetEventCallback(const EventCallbackFn &callback) override { SYS_Data.EventCallback = callback; }

    virtual void ToggleFullScreen() override;
    virtual void GoFullScreen() override;
    virtual void GoWindowed() override;

    virtual void SetLastWindowSize(int width, int height) override;
    virtual void SaveWindowSizeAndPosition() override;
    virtual void RestoreWindowSizeAndPosition() override;

    virtual void SetLastWindowPosition(int x, int y) override;
    virtual void SaveWindowPosition() override;
    virtual void RestoreWindowPosition() override;

    inline virtual void *GetNativeWindow() const override { return SYS_Window; }

#ifdef MPE_OPENGL
    inline virtual GraphicalContext *GetNativeGLContext() const override { return SYS_Context; }
#endif

#ifdef MPE_OPENGLES
    inline virtual GraphicalContext *GetNativeGLESContext() const override { return SYS_ESContext; }
#endif

  private:
    virtual void Init(const WindowProps &props);
    virtual void Shutdown();
    void InternalTest();

  private:
    GLFWwindow *SYS_Window;
#ifdef MPE_OPENGL
    OpenGLContext *SYS_Context;
#endif
#ifdef MPE_OPENGLES
    OpenGLESContext *SYS_ESContext;
#endif

    struct WindowData
    {
        std::string Title;
        int Width, Height;
        int WindowPositionX, WindowPositionY;
        int PrevWidth, PrevHeight;
        int PrevWindowPositionX, PrevWindowPositionY;

        EventCallbackFn EventCallback;
    };

    WindowData SYS_Data;

    WindowMonitors SYS_Monitors;
};
}