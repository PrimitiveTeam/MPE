#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <iostream>
#include <thread>

#ifdef MPE_PLATFORM_WINDOWS
#    include <windows.h>
#    define GLFW_EXPOSE_NATIVE_WIN32
#elif MPE_PLATFORM_LINUX
#    include <X11/Xlib.h>
#endif

int main()
{
#ifdef MPE_PLATFORM_WINDOWS
    // Get the native display handle (HDC) for the entire screen
    EGLNativeDisplayType nativeDisplay = GetDC(nullptr);
#elif MPE_PLATFORM_LINUX
    // Get the native display handle (Display) for the entire screen
    EGLNativeDisplayType nativeDisplay = XOpenDisplay(nullptr);
#endif

    // Obtain the EGL display connection
    EGLDisplay eglDisplay = eglGetDisplay(nativeDisplay);
    if (eglDisplay == EGL_NO_DISPLAY)
    {
        std::cerr << "Failed to get EGL display: " << eglGetError() << std::endl;
        return -1;
    }

    // Initialize the EGL display connection
    if (!eglInitialize(eglDisplay, nullptr, nullptr))
    {
        std::cerr << "Failed to initialize EGL: " << eglGetError() << std::endl;
        return -1;
    }

    // Choose an appropriate EGL configuration
    EGLint configAttribs[] = {
        EGL_SURFACE_TYPE,    EGL_PBUFFER_BIT,  // Offscreen rendering (pbuffer)
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_DEPTH_SIZE, 24, EGL_NONE};

    EGLConfig eglConfig;
    EGLint numConfigs;
    if (!eglChooseConfig(eglDisplay, configAttribs, &eglConfig, 1, &numConfigs) || numConfigs == 0)
    {
        std::cerr << "Failed to choose EGL config: " << eglGetError() << std::endl;
        eglTerminate(eglDisplay);
        return -1;
    }

    // Create an EGL pbuffer surface
    EGLint surfaceAttribs[] = {EGL_WIDTH, 640, EGL_HEIGHT, 480, EGL_NONE};
    EGLSurface eglSurface = eglCreatePbufferSurface(eglDisplay, eglConfig, surfaceAttribs);
    if (eglSurface == EGL_NO_SURFACE)
    {
        std::cerr << "Failed to create EGL surface: " << eglGetError() << std::endl;
        eglTerminate(eglDisplay);
        return -1;
    }

    // Create an OpenGL ES 2.0 context
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
    EGLContext eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs);
    if (eglContext == EGL_NO_CONTEXT)
    {
        std::cerr << "Failed to create EGL context: " << eglGetError() << std::endl;
        eglDestroySurface(eglDisplay, eglSurface);
        eglTerminate(eglDisplay);
        return -1;
    }

    // Make the context current
    if (!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext))
    {
        std::cerr << "Failed to make EGL context current: " << eglGetError() << std::endl;
        eglDestroyContext(eglDisplay, eglContext);
        eglDestroySurface(eglDisplay, eglSurface);
        eglTerminate(eglDisplay);
        return -1;
    }

    // Clear the color buffer
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap buffers (even though this is offscreen, we follow the usual pattern)
    eglSwapBuffers(eglDisplay, eglSurface);

    std::cout << "EGL setup and context creation successful." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Clean up resources
    eglDestroyContext(eglDisplay, eglContext);
    eglDestroySurface(eglDisplay, eglSurface);
    eglTerminate(eglDisplay);

    return 0;
}
