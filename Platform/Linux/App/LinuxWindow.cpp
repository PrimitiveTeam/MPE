#include "LinuxWindow.h"

#include "MPE/Log/GlobalLog.h"
#include "MPE/Events/EventApp.h"
#include "MPE/Events/EventKey.h"
#include "MPE/Events/EventMouse.h"

#include "MPE/Renderer/RendererAPI.h"

#include <GLFW/glfw3.h>

namespace MPE
{
static bool g_glfwInitialized = false;

static void GLFWErrorCallback(int error, const char *description)
{
    MPE_CORE_ERROR("GLFW ERROR ({0}): {1}", error, description);
}

REF<Window> Window::CreateNativeWindow(const WindowProps &props)
{
    MPE_CORE_WARN("Creating Native Window for Linux.");

    return NEWREF<LinuxWindow>(props);
}

LinuxWindow::LinuxWindow(const WindowProps &props)
{
    Init(props);
}

LinuxWindow::~LinuxWindow()
{
    Shutdown();
}

void LinuxWindow::Init(const WindowProps &props)
{
    m_data.title = props.title;
    m_data.width = props.width;
    m_data.height = props.height;
    m_data.windowPositionX = props.windowPositionX;
    m_data.windowPositionY = props.windowPositionY;

    MPE_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

    if (!g_glfwInitialized)
    {
        int success = glfwInit();
        MPE_CORE_ASSERT(success, "COULD NOT INITIALIZE GLFW.");
        glfwSetErrorCallback(GLFWErrorCallback);
        g_glfwInitialized = true;
    }

    auto api = MPE::RendererAPI::GetGraphicsAPI();

    if (api == RendererAPI::API::OpenGLES)
    {

#ifdef MPE_PLATFORM_LINUX
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
#else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
#endif
    }
    else
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    }

    // Allows OpenGL to send debug messages to provided callback function
#ifdef MPE_ENABLE_DEBUG_LOG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    m_window = glfwCreateWindow((int) props.width, (int) props.height, m_data.title.c_str(), nullptr, nullptr);
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
                                 data.windowPositionX = xPos;
                                 data.windowPositionY = yPos;

                                 WindowMovedEvent event(xPos, yPos);
                                 data.eventCallback(event);
                             });

    glfwSetWindowSizeCallback(m_window,
                              [](GLFWwindow *window, int width, int height)
                              {
                                  WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
                                  data.width = width;
                                  data.height = height;

                                  WindowResizeEvent event(width, height);
                                  data.eventCallback(event);
                              });

    glfwSetWindowCloseCallback(m_window,
                               [](GLFWwindow *window)
                               {
                                   WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
                                   WindowCloseEvent event;
                                   data.eventCallback(event);
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
                                   data.eventCallback(event);
                                   break;
                               }
                               case GLFW_RELEASE:
                               {
                                   KeyReleasedEvent event(key);
                                   data.eventCallback(event);
                                   break;
                               }
                               case GLFW_REPEAT:
                               {
                                   KeyPressedEvent event(key, 1);
                                   data.eventCallback(event);
                                   break;
                               }
                           }
                       });

    glfwSetCharCallback(m_window,
                        [](GLFWwindow *window, unsigned int keycode)
                        {
                            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

                            KeyTypedEvent event(keycode);
                            data.eventCallback(event);
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
                                           data.eventCallback(event);
                                           break;
                                       }
                                       case GLFW_RELEASE:
                                       {
                                           MouseButtonReleasedEvent event(button);
                                           data.eventCallback(event);
                                           break;
                                       }
                                   }
                               });

    glfwSetScrollCallback(m_window,
                          [](GLFWwindow *window, double xOffset, double yOffset)
                          {
                              WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

                              MouseScrolledEvent event((float) xOffset, (float) yOffset);
                              data.eventCallback(event);
                          });

    glfwSetCursorPosCallback(m_window,
                             [](GLFWwindow *window, double xPos, double yPos)
                             {
                                 WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

                                 MouseMovedEvent event((float) xPos, (float) yPos);
                                 data.eventCallback(event);
                             });
}

void LinuxWindow::Shutdown()
{
    glfwDestroyWindow(m_window);
}

void LinuxWindow::OnUpdate()
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
    // glfwSwapBuffers(m_window);
}

void LinuxWindow::ToggleFullScreen()
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

void LinuxWindow::GoFullScreen()
{
    SaveWindowSizeAndPosition();

    glfwSetWindowMonitor(m_window, m_monitors.GetMonitors().at(0).monitor, 0, 0, m_monitors.GetMonitors().at(0).mode->width,
                         m_monitors.GetMonitors().at(0).mode->height, m_monitors.GetMonitors().at(0).mode->refreshRate);
}

void LinuxWindow::GoWindowed()
{
    glfwSetWindowMonitor(m_window, nullptr, m_data.prevWindowPositionX, m_data.prevWindowPositionY, m_data.prevWidth, m_data.prevHeight, 0);
}

void LinuxWindow::SetLastWindowSize(int width, int height)
{
    m_data.prevWidth = width;
    m_data.prevHeight = height;
}

void LinuxWindow::SaveWindowSizeAndPosition()
{
    glfwGetWindowSize(m_window, &m_data.prevWidth, &m_data.prevHeight);
    glfwGetWindowPos(m_window, &m_data.prevWindowPositionX, &m_data.prevWindowPositionY);
}

void LinuxWindow::RestoreWindowSizeAndPosition()
{
    glfwSetWindowSize(m_window, m_data.prevWidth, m_data.prevHeight);
    glfwSetWindowPos(m_window, m_data.prevWindowPositionX, m_data.prevWindowPositionY);
}

void LinuxWindow::SetLastWindowPosition(int x, int y)
{
    m_data.prevWindowPositionX = x;
    m_data.prevWindowPositionY = y;
}

void LinuxWindow::SaveWindowPosition()
{
    glfwGetWindowPos(m_window, &m_data.prevWindowPositionX, &m_data.prevWindowPositionY);
}

void LinuxWindow::RestoreWindowPosition()
{
    glfwSetWindowPos(m_window, m_data.prevWindowPositionX, m_data.prevWindowPositionY);
}
}