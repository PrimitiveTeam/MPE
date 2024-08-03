#include "RPIWindow.h"

#include "MPE/Log/GlobalLog.h"
#include "MPE/Events/EventApp.h"
#include "MPE/Events/EventKey.h"
#include "MPE/Events/EventMouse.h"

namespace MPE
{
static bool SYS_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char *description)
{
    MPE_CORE_ERROR("GLFW ERROR ({0}): {1}", error, description);
}

REF<Window> Window::CreateNativeWindow(const WindowProps &props)
{
    MPE_CORE_WARN("Creating Native Window for RPI4.");

    return NEWREF<RPIWindow>(props);
}

RPIWindow::RPIWindow(const WindowProps &props)
{
    Init(props);
}

RPIWindow::~RPIWindow()
{
    Shutdown();
}

void RPIWindow::Init(const WindowProps &props)
{
    SYS_Data.Title = props.Title;
    SYS_Data.Width = props.Width;
    SYS_Data.Height = props.Height;
    SYS_Data.WindowPositionX = props.WindowPositionX;
    SYS_Data.WindowPositionY = props.WindowPositionY;

    MPE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

    if (!SYS_GLFWInitialized)
    {
        int success = glfwInit();
        MPE_CORE_ASSERT(success, "COULD NOT INITIALIZE GLFW.");
        glfwSetErrorCallback(GLFWErrorCallback);
        SYS_GLFWInitialized = true;
    }

    SYS_Window = glfwCreateWindow((int) props.Width, (int) props.Height, SYS_Data.Title.c_str(), nullptr, nullptr);
    SaveWindowSizeAndPosition();

    SYS_ESContext = new OpenGLESContext(SYS_Window);
    SYS_ESContext->Init();

    glfwSetWindowUserPointer(SYS_Window, &SYS_Data);

    // SET GLFW CALLBACKS
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

void RPIWindow::Shutdown()
{
    glfwDestroyWindow(SYS_Window);
}

void RPIWindow::OnUpdate()
{
    glfwPollEvents();
    SYS_ESContext->SwapBuffers();
    // glfwSwapBuffers(SYS_Window);
}

void RPIWindow::ToggleFullScreen()
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

void RPIWindow::GoFullScreen()
{
    SaveWindowSizeAndPosition();

    glfwSetWindowMonitor(SYS_Window, SYS_Monitors.GetMonitors().at(0).monitor, 0, 0, SYS_Monitors.GetMonitors().at(0).mode->width,
                         SYS_Monitors.GetMonitors().at(0).mode->height, SYS_Monitors.GetMonitors().at(0).mode->refreshRate);
}

void RPIWindow::GoWindowed()
{
    glfwSetWindowMonitor(SYS_Window, nullptr, SYS_Data.PrevWindowPositionX, SYS_Data.PrevWindowPositionY, SYS_Data.PrevWidth, SYS_Data.PrevHeight, 0);
}

void RPIWindow::SetLastWindowSize(int width, int height)
{
    SYS_Data.PrevWidth = width;
    SYS_Data.PrevHeight = height;
}

void RPIWindow::SaveWindowSizeAndPosition()
{
    glfwGetWindowSize(SYS_Window, &SYS_Data.PrevWidth, &SYS_Data.PrevHeight);
    glfwGetWindowPos(SYS_Window, &SYS_Data.PrevWindowPositionX, &SYS_Data.PrevWindowPositionY);
}

void RPIWindow::RestoreWindowSizeAndPosition()
{
    glfwSetWindowSize(SYS_Window, SYS_Data.PrevWidth, SYS_Data.PrevHeight);
    glfwSetWindowPos(SYS_Window, SYS_Data.PrevWindowPositionX, SYS_Data.PrevWindowPositionY);
}

void RPIWindow::SetLastWindowPosition(int x, int y)
{
    SYS_Data.PrevWindowPositionX = x;
    SYS_Data.PrevWindowPositionY = y;
}

void RPIWindow::SaveWindowPosition()
{
    glfwGetWindowPos(SYS_Window, &SYS_Data.PrevWindowPositionX, &SYS_Data.PrevWindowPositionY);
}

void RPIWindow::RestoreWindowPosition()
{
    glfwSetWindowPos(SYS_Window, SYS_Data.PrevWindowPositionX, SYS_Data.PrevWindowPositionY);
}
}