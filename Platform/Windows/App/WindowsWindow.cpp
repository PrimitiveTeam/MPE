#include "WindowsWindow.h"

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/Events/EventApp.h"
#include "MPE/Events/EventKey.h"
#include "MPE/Events/EventMouse.h"

#include "MPE/Renderer/RendererAPI.h"

#include <GLFW/glfw3.h>

namespace MPE
{
static bool SYS_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char *description)
{
    MPE_CORE_ERROR("GLFW ERROR ({0}): {1}", error, description);
}

REF<Window> Window::CreateNativeWindow(const WindowProps &props)
{
    MPE_CORE_WARN("Creating Native Window for Windows.");

    return NEWREF<WindowsWindow>(props);
}

WindowsWindow::WindowsWindow(const WindowProps &props)
{
    Init(props);
}

WindowsWindow::~WindowsWindow()
{
    Shutdown();
}

void WindowsWindow::Init(const WindowProps &props)
{
    SYS_Monitors = WindowMonitors();

    SYS_Data.Title = props.Title;
    SYS_Data.Width = props.Width;
    SYS_Data.Height = props.Height;
    SYS_Data.WindowPositionX = props.WindowPositionX;
    SYS_Data.WindowPositionY = props.WindowPositionY;

    MPE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height, props.WindowPositionX, props.WindowPositionY);

    if (!SYS_GLFWInitialized)
    {
        int success = glfwInit();
        MPE_CORE_ASSERT(success, "COULD NOT INITIALIZE GLFW.");
        glfwSetErrorCallback(GLFWErrorCallback);
        SYS_GLFWInitialized = true;
    }

    auto api = MPE::RendererAPI::GetGraphicsAPI();

    if (api == RendererAPI::API::OpenGLES)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    }
    else
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    }

    SYS_Window = glfwCreateWindow((int) props.Width, (int) props.Height, SYS_Data.Title.c_str(), nullptr, nullptr);
    SaveWindowSizeAndPosition();

    switch (api)
    {
        case RendererAPI::API::OpenGL:
#ifdef MPE_OPENGL
            SYS_Context = new OpenGLContext(SYS_Window);
            SYS_Context->Init();
            break;
#else
            MPE_CORE_ASSERT(false, "OPENGL IS NOT SUPPORTED.");
#endif
        case RendererAPI::API::OpenGLES:
#ifdef MPE_OPENGLES
            SYS_ESContext = new OpenGLESContext(SYS_Window);
            SYS_ESContext->Init();
            break;
#else
            MPE_CORE_ASSERT(false, "OPENGLES IS NOT SUPPORTED.");
#endif
        default:
            MPE_CORE_ASSERT(false, "NO RENDERER API SELECTED.");
    }

    glfwSetWindowUserPointer(SYS_Window, &SYS_Data);

    // SET GLFW CALLBACKS
    // Window moved
    glfwSetWindowPosCallback(SYS_Window,
                             [](GLFWwindow *window, int xPos, int yPos)
                             {
                                 WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
                                 data.WindowPositionX = xPos;
                                 data.WindowPositionY = yPos;

                                 WindowMovedEvent event(xPos, yPos);
                                 data.EventCallback(event);
                             });

    glfwSetWindowSizeCallback(SYS_Window,
                              [](GLFWwindow *window, int width, int height)
                              {
                                  WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
                                  data.Width = width;
                                  data.Height = height;

                                  WindowResizeEvent event(width, height);
                                  data.EventCallback(event);
                              });

    glfwSetWindowCloseCallback(SYS_Window,
                               [](GLFWwindow *window)
                               {
                                   WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
                                   WindowCloseEvent event;
                                   data.EventCallback(event);
                               });

    glfwSetKeyCallback(SYS_Window,
                       [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       {
                           WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

                           switch (action)
                           {
                               case GLFW_PRESS:
                               {
                                   KeyPressedEvent event(key, 0);
                                   data.EventCallback(event);
                                   break;
                               }
                               case GLFW_RELEASE:
                               {
                                   KeyReleasedEvent event(key);
                                   data.EventCallback(event);
                                   break;
                               }
                               case GLFW_REPEAT:
                               {
                                   KeyPressedEvent event(key, 1);
                                   data.EventCallback(event);
                                   break;
                               }
                           }
                       });

    glfwSetCharCallback(SYS_Window,
                        [](GLFWwindow *window, unsigned int keycode)
                        {
                            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

                            KeyTypedEvent event(keycode);
                            data.EventCallback(event);
                        });

    glfwSetMouseButtonCallback(SYS_Window,
                               [](GLFWwindow *window, int button, int action, int mods)
                               {
                                   WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

                                   switch (action)
                                   {
                                       case GLFW_PRESS:
                                       {
                                           MouseButtonPressedEvent event(button);
                                           data.EventCallback(event);
                                           break;
                                       }
                                       case GLFW_RELEASE:
                                       {
                                           MouseButtonReleasedEvent event(button);
                                           data.EventCallback(event);
                                           break;
                                       }
                                   }
                               });

    glfwSetScrollCallback(SYS_Window,
                          [](GLFWwindow *window, double xOffset, double yOffset)
                          {
                              WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

                              MouseScrolledEvent event((float) xOffset, (float) yOffset);
                              data.EventCallback(event);
                          });

    glfwSetCursorPosCallback(SYS_Window,
                             [](GLFWwindow *window, double xPos, double yPos)
                             {
                                 WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

                                 MouseMovedEvent event((float) xPos, (float) yPos);
                                 data.EventCallback(event);
                             });
}

void WindowsWindow::Shutdown()
{
    glfwDestroyWindow(SYS_Window);
}

void WindowsWindow::OnUpdate()
{
    glfwPollEvents();

    auto api = MPE::RendererAPI::GetGraphicsAPI();
    switch (api)
    {
        case RendererAPI::API::OpenGL:
#ifdef MPE_OPENGL
            SYS_Context->SwapBuffers();
            break;
#else
            MPE_CORE_ASSERT(false, "OPENGL IS NOT SUPPORTED.");
#endif
        case RendererAPI::API::OpenGLES:
#ifdef MPE_OPENGLES
            SYS_ESContext->SwapBuffers();
            break;
#else
            MPE_CORE_ASSERT(false, "OPENGLES IS NOT SUPPORTED.");
#endif
        default:
            MPE_CORE_ASSERT(false, "NO RENDERER API SELECTED.");
    }
    // glfwSwapBuffers(SYS_Window);
}

void WindowsWindow::ToggleFullScreen()
{
    SYS_Monitors.UpdateMonitors();

    if (glfwGetWindowMonitor(SYS_Window))
    {
        GoWindowed();
    }
    else
    {
        GoFullScreen();
    }
}

void WindowsWindow::GoFullScreen()
{
    SaveWindowSizeAndPosition();

    glfwSetWindowMonitor(SYS_Window, SYS_Monitors.GetMonitors().at(0).monitor, 0, 0, SYS_Monitors.GetMonitors().at(0).mode->width,
                         SYS_Monitors.GetMonitors().at(0).mode->height, SYS_Monitors.GetMonitors().at(0).mode->refreshRate);
}

void WindowsWindow::GoWindowed()
{
    glfwSetWindowMonitor(SYS_Window, nullptr, SYS_Data.PrevWindowPositionX, SYS_Data.PrevWindowPositionY, SYS_Data.PrevWidth, SYS_Data.PrevHeight, 0);
}

void WindowsWindow::SetLastWindowSize(int width, int height)
{
    SYS_Data.PrevWidth = width;
    SYS_Data.PrevHeight = height;
}

void WindowsWindow::SaveWindowSizeAndPosition()
{
    glfwGetWindowSize(SYS_Window, &SYS_Data.PrevWidth, &SYS_Data.PrevHeight);
    glfwGetWindowPos(SYS_Window, &SYS_Data.PrevWindowPositionX, &SYS_Data.PrevWindowPositionY);
}

void WindowsWindow::RestoreWindowSizeAndPosition()
{
    glfwSetWindowSize(SYS_Window, SYS_Data.PrevWidth, SYS_Data.PrevHeight);
    glfwSetWindowPos(SYS_Window, SYS_Data.PrevWindowPositionX, SYS_Data.PrevWindowPositionY);
}

void WindowsWindow::SetLastWindowPosition(int x, int y)
{
    SYS_Data.PrevWindowPositionX = x;
    SYS_Data.PrevWindowPositionY = y;
}

void WindowsWindow::SaveWindowPosition()
{
    glfwGetWindowPos(SYS_Window, &SYS_Data.PrevWindowPositionX, &SYS_Data.PrevWindowPositionY);
}

void WindowsWindow::RestoreWindowPosition()
{
    glfwSetWindowPos(SYS_Window, SYS_Data.PrevWindowPositionX, SYS_Data.PrevWindowPositionY);
}
}