#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/App/Window.h"
#include "MPE/Platform/OpenGL/OpenGLContext.h"

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

    inline unsigned int GetWidth() const override { return SYS_Data.Width; }
    inline unsigned int GetHeight() const override { return SYS_Data.Height; }

    inline void SetEventCallback(const EventCallbackFn &callback) override { SYS_Data.EventCallback = callback; }
    void SetVSync(bool enabled) override;
    bool IsVSync() const override;

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
        unsigned int Width, Height;
        bool VSync;

        EventCallbackFn EventCallback;
    };

    WindowData SYS_Data;
};
}