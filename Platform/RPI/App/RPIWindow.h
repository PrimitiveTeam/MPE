#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/App/Window.h"
#include "Platform/OpenGLES/OpenGLESContext.h"
#include "Platform/Linux/App/WindowMonitors.h"

#ifdef MPE_OPENGL
#    include "Platform/OpenGL/OpenGLContext.h"
#endif
#ifdef MPE_OPENGLES
#    include "Platform/OpenGLES/OpenGLESContext.h"
#endif

struct GLFWwindow;

namespace MPE
{
class MPE_API RPIWindow : public Window
{
  public:
    RPIWindow(const WindowProps &props);
    virtual ~RPIWindow();

    void OnUpdate() override;

    virtual inline int GetWidth() const override { return m_data.m_width; }
    virtual inline int GetHeight() const override { return m_data.m_height; }
    virtual inline int GetWindowPositionX() const override { return m_data.m_windowPositionX; }
    virtual inline int GetWindowPositionY() const override { return m_data.m_windowPositionY; }

    virtual inline void SetEventCallback(const EventCallbackFn &callback) override { m_data.m_eventCallback = callback; }

    virtual void ToggleFullScreen() override;
    virtual void GoFullScreen() override;
    virtual void GoWindowed() override;

    virtual void SetLastWindowSize(int width, int height) override;
    virtual void SaveWindowSizeAndPosition() override;
    virtual void RestoreWindowSizeAndPosition() override;

    virtual void SetLastWindowPosition(int x, int y) override;
    virtual void SaveWindowPosition() override;
    virtual void RestoreWindowPosition() override;

    inline virtual void *GetNativeWindow() const override { return m_window; }

#ifdef MPE_OPENGL
    inline virtual GraphicalContext *GetNativeGLContext() const override { return m_GLcontext; }
#endif

#ifdef MPE_OPENGLES
    inline virtual GraphicalContext *GetNativeGLESContext() const override { return m_EScontext; }
#endif

  private:
    virtual void Init(const WindowProps &props);
    virtual void Shutdown();

  private:
    GLFWwindow *m_window;
#ifdef MPE_OPENGL
    OpenGLContext *m_GLcontext;
#endif
#ifdef MPE_OPENGLES
    OpenGLESContext *m_EScontext;
#endif

    struct WindowData
    {
        std::string m_title;
        int m_width, m_height;
        int m_windowPositionX, m_windowPositionY;
        int m_prevWidth, m_prevHeight;
        int m_prevWindowPositionX, m_prevWindowPositionY;

        EventCallbackFn m_eventCallback;
    };

    WindowData m_data;

    WindowMonitors m_monitors;
};
}