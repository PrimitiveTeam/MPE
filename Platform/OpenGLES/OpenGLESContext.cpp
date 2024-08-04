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

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <EGL/egl.h>
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

    EGLint configAttribs[] = {EGL_SURFACE_TYPE,
                              EGL_WINDOW_BIT,
                              EGL_RENDERABLE_TYPE,
                              EGL_OPENGL_ES2_BIT | EGL_OPENGL_ES3_BIT,
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
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, glfwGetCocoaWindow(SYS_Window), nullptr);
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

    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_CONTEXT_MINOR_VERSION, 1, EGL_NONE};
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

#ifdef MPE_PLATFORM_WINDOWS
    glfwMakeContextCurrent(SYS_Window);
#endif

    int OpenGLVersionMajor;
    int OpenGLVersionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersionMinor);

    SYS_Props.MajorVersion = OpenGLVersionMajor;
    SYS_Props.MinorVersion = OpenGLVersionMinor;

#ifdef MPE_PLATFORM_WINDOWS
    MPE_CORE_ASSERT(OpenGLVersionMajor > 3 || (OpenGLVersionMajor == 3 && OpenGLVersionMinor >= 0), "MPE REQUIRES OPENGL VERSION 3.0 OR GREATER FOR OPENGLES.");
#elif MPE_PLATFORM_OSX
    MPE_CORE_ASSERT(OpenGLVersionMajor >= 3 || (OpenGLVersionMajor >= 3 && OpenGLVersionMinor >= 2), "MPE REQUIRES OPENGL VERSION 3.1 FOR macOS.");
#elif MPE_PLATFORM_RPI4
    MPE_CORE_ASSERT(OpenGLVersionMajor >= 3 || (OpenGLVersionMajor >= 3 && OpenGLVersionMinor >= 2), "MPE REQUIRES OPENGL VERSION 3.1 FOR raspiOS.");
#endif

    SYS_Props.Vendor = std::string(reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
    SYS_Props.Renderer = std::string(reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
    SYS_Props.ShaderTypeAmount = OPENGL_SHADER_TYPE_AMOUNT;

    MPE_CORE_INFO('\n' + SYS_Props.ToString());
}

void OpenGLESContext::SwapBuffers()
{
    eglSwapBuffers(eglDisplay, eglSurface);
}
}