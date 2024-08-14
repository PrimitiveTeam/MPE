#include "OpenGLESContext.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/Renderer/RendererAPI.h"

#ifdef MPE_PLATFORM_WINDOWS
#    define GLFW_EXPOSE_NATIVE_WIN32
#elif MPE_PLATFORM_LINUX
#    define GLFW_EXPOSE_NATIVE_X11
#elif MPE_PLATFORM_OSX
#    define GLFW_EXPOSE_NATIVE_COCOA
#elif MPE_PLATFORM_RPI4
#    define GLFW_EXPOSE_NATIVE_EGL
#endif

#ifdef MPE_PLATFORM_OSX
#    define GLFW_EXPOSE_NATIVE_COCOA
#    include "Platform/macOS/App/macOSContext.h"
#endif
#include <GLFW/glfw3native.h>
#include <GLES3/gl31.h>

namespace MPE
{
OpenGLESContext::OpenGLESContext(GLFWwindow *window) : SYS_Window(window)
{
    MPE_CORE_ASSERT(SYS_Window, "WINDOW IS NULL.");
}

void OpenGLESContext::Init()
{
#ifdef MPE_PLATFORM_WINDOWS
    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#elif MPE_PLATFORM_LINUX
    Display *nativeDisplay = glfwGetX11Display();
    eglDisplay = eglGetDisplay(nativeDisplay);
#elif MPE_PLATFORM_OSX
    EGLNativeWindowType nativeWindow = macOSContext::GetNativeWindow(SYS_Window);
    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#else
    MPE_ASSERT(false, "PLATFORM NOT SUPPORTED.");
#endif
    if (eglDisplay == EGL_NO_DISPLAY)
    {
        std::cerr << "Failed to get EGL display: " << eglGetError() << std::endl;
        glfwDestroyWindow(SYS_Window);
        glfwTerminate();
        MPE_ASSERT(false, "Failed to get EGL display.");
        return;
    }

    if (!eglInitialize(eglDisplay, nullptr, nullptr))
    {
        std::cerr << "Failed to initialize EGL: " << eglGetError() << std::endl;
        glfwDestroyWindow(SYS_Window);
        glfwTerminate();
        MPE_ASSERT(false, "Failed to initialize EGL.");
        return;
    }

#ifdef MPE_PLATFORM_OSX

    // List all available configurations for debugging
    EGLint numConfigsAvailable;
    eglGetConfigs(eglDisplay, nullptr, 0, &numConfigsAvailable);
    std::cout << "Number of available configurations: " << numConfigsAvailable << std::endl;

    EGLConfig allConfigs[numConfigsAvailable];
    eglGetConfigs(eglDisplay, allConfigs, numConfigsAvailable, &numConfigsAvailable);

    for (int i = 0; i < numConfigsAvailable; ++i)
    {
        EGLint redSize, greenSize, blueSize, alphaSize, depthSize, renderableType;
        eglGetConfigAttrib(eglDisplay, allConfigs[i], EGL_RED_SIZE, &redSize);
        eglGetConfigAttrib(eglDisplay, allConfigs[i], EGL_GREEN_SIZE, &greenSize);
        eglGetConfigAttrib(eglDisplay, allConfigs[i], EGL_BLUE_SIZE, &blueSize);
        eglGetConfigAttrib(eglDisplay, allConfigs[i], EGL_ALPHA_SIZE, &alphaSize);
        eglGetConfigAttrib(eglDisplay, allConfigs[i], EGL_DEPTH_SIZE, &depthSize);
        eglGetConfigAttrib(eglDisplay, allConfigs[i], EGL_RENDERABLE_TYPE, &renderableType);

        MPE_INFO("Config {0}: R={1} G={2} B={3} A={4} Depth={5} Type={6}", i, redSize, greenSize, blueSize, alphaSize, depthSize, renderableType);
    }

    const char *eglExtensions = eglQueryString(eglDisplay, EGL_EXTENSIONS);
    MPE_INFO("EGL Extensions: {0}", eglExtensions);

#endif

    EGLint configAttribs[] = {EGL_SURFACE_TYPE,
                              EGL_WINDOW_BIT,
                              EGL_RENDERABLE_TYPE,
                              EGL_OPENGL_ES3_BIT,
                              EGL_RED_SIZE,
                              8,
                              EGL_GREEN_SIZE,
                              8,
                              EGL_BLUE_SIZE,
                              8,
                              EGL_ALPHA_SIZE,
                              8,
                              EGL_DEPTH_SIZE,
                              24,
                              EGL_NONE};

    EGLConfig eglConfig;
    EGLint numConfigs;
    if (!eglChooseConfig(eglDisplay, configAttribs, &eglConfig, 1, &numConfigs) || numConfigs == 0)
    {
        std::cerr << "Failed to choose EGL config: " << eglGetError() << std::endl;
        eglTerminate(eglDisplay);
        glfwDestroyWindow(SYS_Window);
        glfwTerminate();
        MPE_ASSERT(false, "Failed to choose EGL config.");
        return;
    }

#ifdef MPE_PLATFORM_WINDOWS
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, glfwGetWin32Window(SYS_Window), nullptr);
#elif MPE_PLATFORM_LINUX
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType) glfwGetX11Window(SYS_Window), nullptr);
#elif MPE_PLATFORM_OSX
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, nativeWindow, nullptr);
#elif MPE_PLATFORM_RPI4
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, glfwGetEGLDisplay(SYS_Window), nullptr);
#endif
    if (eglSurface == EGL_NO_SURFACE)
    {
        std::cerr << "Failed to create EGL window surface: " << eglGetError() << std::endl;
        eglTerminate(eglDisplay);
        glfwDestroyWindow(SYS_Window);
        glfwTerminate();
        return;
    }

#ifdef MPE_PLATFORM_OSX
    // CURRENTLY ANGLE SUPPORTS ONLY OPENGL ES 3.0
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_CONTEXT_MINOR_VERSION, 0, EGL_NONE};
#else
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_CONTEXT_MINOR_VERSION, 1, EGL_NONE};
#endif
    eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs);
    if (eglContext == EGL_NO_CONTEXT)
    {
        std::cerr << "Failed to create EGL context: " << eglGetError() << std::endl;
        eglDestroySurface(eglDisplay, eglSurface);
        eglTerminate(eglDisplay);
        glfwDestroyWindow(SYS_Window);
        glfwTerminate();
        MPE_ASSERT(false, "Failed to create EGL context.");
        return;
    }

    if (!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext))
    {
        std::cerr << "Failed to make EGL context current: " << eglGetError() << std::endl;
        eglDestroyContext(eglDisplay, eglContext);
        eglDestroySurface(eglDisplay, eglSurface);
        eglTerminate(eglDisplay);
        glfwDestroyWindow(SYS_Window);
        glfwTerminate();
        MPE_ASSERT(false, "Failed to make EGL context current.");
        return;
    }

#ifdef MPE_PLATFORM_OSX
    const char *glExtensions = reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));
    MPE_INFO("GL Extensions: {0}", glExtensions);
#endif
}

void OpenGLESContext::SwapBuffers()
{
    eglSwapBuffers(eglDisplay, eglSurface);
}
}