#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/App/Window.h"
#include "MPE/Platform/OpenGL/OpenGLContext.h"
#include "MPE/Platform/Linux/App/WindowMonitors.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace MPE
{
class MPE_API LinuxWindow : public Window
{
  public:
    LinuxWindow(const WindowProps &props);
    virtual ~LinuxWindow();

    void OnUpdate() override;

    inline int GetWidth() const override { return SYS_Data.Width; }
    inline int GetHeight() const override { return SYS_Data.Height; }

    inline void SetEventCallback(const EventCallbackFn &callback) override { SYS_Data.EventCallback = callback; }

    virtual void ToggleFullScreen() override;
    virtual void GoFullScreen() override;
    virtual void GoWindowed() override;

    virtual void SetLastWindowSize(int width, int height) override;
    virtual void SaveWindowSizeAndPosition() override;
    virtual void RestoreWindowSizeAndPosition() override;

    inline virtual void *GetNativeWindow() const override { return SYS_Window; }

  private:
    virtual void Init(const WindowProps &props);
    virtual void Shutdown();

  private:
    GLFWwindow *SYS_Window;
    OpenGLContext *SYS_Context;

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