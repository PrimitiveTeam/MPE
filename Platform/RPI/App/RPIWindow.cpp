#include "RPIWindow.h"

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
    MPE_CORE_WARN("Creating Native Window for Linux.");

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
    m_monitors = WindowMonitors();

    m_data.m_title = props.m_title;
    m_data.m_width = props.m_width;
    m_data.m_height = props.m_height;
    m_data.m_windowPositionX = props.m_windowPositionX;
    m_data.m_windowPositionY = props.m_windowPositionY;

    MPE_CORE_INFO("Creating window {0} ({1}, {2})", props.m_title, props.m_width, props.m_height);

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
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        // SETTINGS THIS TO GLFW_OPENGL_ES_API WILL CAUSE THE WINDOW TO NOT BE CREATED OR A LOT OF ERRORS WILL BE THROWN AND BLACK SCREEN WILL BE RENDERED.
        // Not sure why this is happening on linux but it works on windows.
        // Also this can be thrown when using GLFW_OPENGL_ES_API:
        /*
                X Error of failed request:  BadAccess (attempt to access private resource denied)
                Major opcode of failed request:  152 (GLX)
                Minor opcode of failed request:  5 (X_GLXMakeCurrent)
                Serial number of failed request:  178
                Current serial number in output stream:  178
        */
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
        // glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    }
    else
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    }

    m_window = glfwCreateWindow((int) props.m_width, (int) props.m_height, m_data.m_title.c_str(), nullptr, nullptr);
    SaveWindowSizeAndPosition();

    switch (api)
    {
        case RendererAPI::API::OpenGL:
#ifdef MPE_OPENGL
            m_GLcontext = new OpenGLContext(m_window);
            m_GLcontext->Init();
            break;
#else
            MPE_CORE_ASSERT(false, "OPENGL IS NOT SUPPORTED.");
#endif
        case RendererAPI::API::OpenGLES:
#ifdef MPE_OPENGLES
            m_EScontext = new OpenGLESContext(m_window);
            m_EScontext->Init();
            break;
#else
            MPE_CORE_ASSERT(false, "OPENGLES IS NOT SUPPORTED.");
#endif
        default:
            MPE_CORE_ASSERT(false, "NO RENDERER API SELECTED.");
    }

    glfwSetWindowUserPointer(m_window, &m_data);

    // SET GLFW CALLBACKS
    glfwSetWindowPosCallback(m_window,
                             [](GLFWwindow *window, int xPos, int yPos)
                             {
                                 WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
                                 data.m_windowPositionX = xPos;
                                 data.m_windowPositionY = yPos;

                                 WindowMovedEvent event(xPos, yPos);
                                 data.m_eventCallback(event);
                             });

    glfwSetWindowSizeCallback(m_window,
                              [](GLFWwindow *window, int width, int height)
                              {
                                  WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
                                  data.m_width = width;
                                  data.m_height = height;

                                  WindowResizeEvent event(width, height);
                                  data.m_eventCallback(event);
                              });

    glfwSetWindowCloseCallback(m_window,
                               [](GLFWwindow *window)
                               {
                                   WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
                                   WindowCloseEvent event;
                                   data.m_eventCallback(event);
                               });

    glfwSetKeyCallback(m_window,
                       [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       {
                           WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

                           switch (action)
                           {
                               case GLFW_PRESS:
                               {
                                   KeyPressedEvent event(key, 0);
                                   data.m_eventCallback(event);
                                   break;
                               }
                               case GLFW_RELEASE:
                               {
                                   KeyReleasedEvent event(key);
                                   data.m_eventCallback(event);
                                   break;
                               }
                               case GLFW_REPEAT:
                               {
                                   KeyPressedEvent event(key, 1);
                                   data.m_eventCallback(event);
                                   break;
                               }
                           }
                       });

    glfwSetCharCallback(m_window,
                        [](GLFWwindow *window, unsigned int keycode)
                        {
                            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

                            KeyTypedEvent event(keycode);
                            data.m_eventCallback(event);
                        });

    glfwSetMouseButtonCallback(m_window,
                               [](GLFWwindow *window, int button, int action, int mods)
                               {
                                   WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

                                   switch (action)
                                   {
                                       case GLFW_PRESS:
                                       {
                                           MouseButtonPressedEvent event(button);
                                           data.m_eventCallback(event);
                                           break;
                                       }
                                       case GLFW_RELEASE:
                                       {
                                           MouseButtonReleasedEvent event(button);
                                           data.m_eventCallback(event);
                                           break;
                                       }
                                   }
                               });

    glfwSetScrollCallback(m_window,
                          [](GLFWwindow *window, double xOffset, double yOffset)
                          {
                              WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

                              MouseScrolledEvent event((float) xOffset, (float) yOffset);
                              data.m_eventCallback(event);
                          });

    glfwSetCursorPosCallback(m_window,
                             [](GLFWwindow *window, double xPos, double yPos)
                             {
                                 WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

                                 MouseMovedEvent event((float) xPos, (float) yPos);
                                 data.m_eventCallback(event);
                             });
}

void RPIWindow::Shutdown()
{
    glfwDestroyWindow(m_window);
}

void RPIWindow::OnUpdate()
{
    glfwPollEvents();

    auto api = MPE::RendererAPI::GetGraphicsAPI();
    switch (api)
    {
        case RendererAPI::API::OpenGL:
#ifdef MPE_OPENGL
            m_GLcontext->SwapBuffers();
            break;
#else
            MPE_CORE_ASSERT(false, "OPENGL IS NOT SUPPORTED.");
#endif
        case RendererAPI::API::OpenGLES:
#ifdef MPE_OPENGLES
            m_EScontext->SwapBuffers();
            break;
#else
            MPE_CORE_ASSERT(false, "OPENGLES IS NOT SUPPORTED.");
#endif
        default:
            MPE_CORE_ASSERT(false, "NO RENDERER API SELECTED.");
    }
}

void RPIWindow::ToggleFullScreen()
{
    m_monitors.UpdateMonitors();

    if (glfwGetWindowMonitor(m_window))
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

    glfwSetWindowMonitor(m_window, m_monitors.GetMonitors().at(0).m_monitor, 0, 0, m_monitors.GetMonitors().at(0).m_mode->width,
                         m_monitors.GetMonitors().at(0).m_mode->height, m_monitors.GetMonitors().at(0).m_mode->refreshRate);
}

void RPIWindow::GoWindowed()
{
    glfwSetWindowMonitor(m_window, nullptr, m_data.m_prevWindowPositionX, m_data.m_prevWindowPositionY, m_data.m_prevWidth, m_data.m_prevHeight, 0);
}

void RPIWindow::SetLastWindowSize(int width, int height)
{
    m_data.m_prevWidth = width;
    m_data.m_prevHeight = height;
}

void RPIWindow::SaveWindowSizeAndPosition()
{
    glfwGetWindowSize(m_window, &m_data.m_prevWidth, &m_data.m_prevHeight);
    glfwGetWindowPos(m_window, &m_data.m_prevWindowPositionX, &m_data.m_prevWindowPositionY);
}

void RPIWindow::RestoreWindowSizeAndPosition()
{
    glfwSetWindowSize(m_window, m_data.m_prevWidth, m_data.m_prevHeight);
    glfwSetWindowPos(m_window, m_data.m_prevWindowPositionX, m_data.m_prevWindowPositionY);
}

void RPIWindow::SetLastWindowPosition(int x, int y)
{
    m_data.m_prevWindowPositionX = x;
    m_data.m_prevWindowPositionY = y;
}

void RPIWindow::SaveWindowPosition()
{
    glfwGetWindowPos(m_window, &m_data.m_prevWindowPositionX, &m_data.m_prevWindowPositionY);
}

void RPIWindow::RestoreWindowPosition()
{
    glfwSetWindowPos(m_window, m_data.m_prevWindowPositionX, m_data.m_prevWindowPositionY);
}
}