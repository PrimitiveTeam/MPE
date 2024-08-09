#ifdef MPE_PLATFORM_WINDOWS
#    include <windows.h>
#    define GLFW_EXPOSE_NATIVE_WIN32
#elif MPE_PLATFORM_LINUX
#    ifdef MPE_USE_X11
#        include <X11/Xlib.h>
#        define GLFW_EXPOSE_NATIVE_X11
#    elif MPE_USE_WAYLAND
// throw assert error
MPE_ASSERT(false);
#        include <wayland-client.h>
#        define GLFW_EXPOSE_NATIVE_WAYLAND
#    endif
#endif

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <iostream>

// Error callback function for GLFW
void glfwErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

int main()
{
    // Set the GLFW error callback
    glfwSetErrorCallback(glfwErrorCallback);

    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Prevent GLFW from creating an OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "ANGLE with GLFW", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

#ifdef MPE_PLATFORM_WINDOWS
    // Obtain the EGL display connection using the native display from GLFW
    EGLDisplay eglDisplay = eglGetDisplay(GetDC(glfwGetWin32Window(window)));
#elif MPE_PLATFORM_LINUX
    // Obtain the EGL display connection using the native display from GLFW
    Display* nativeDisplay = glfwGetX11Display();
    EGLDisplay eglDisplay = eglGetDisplay(nativeDisplay);
#endif
    if (eglDisplay == EGL_NO_DISPLAY)
    {
        std::cerr << "Failed to get EGL display: " << eglGetError() << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Initialize the EGL display connection
    if (!eglInitialize(eglDisplay, nullptr, nullptr))
    {
        std::cerr << "Failed to initialize EGL: " << eglGetError() << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Choose an appropriate EGL configuration
    EGLint configAttribs[] = {
        EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,  // Create a window surface
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_DEPTH_SIZE, 24, EGL_NONE};

    EGLConfig eglConfig;
    EGLint numConfigs;
    if (!eglChooseConfig(eglDisplay, configAttribs, &eglConfig, 1, &numConfigs) || numConfigs == 0)
    {
        std::cerr << "Failed to choose EGL config: " << eglGetError() << std::endl;
        eglTerminate(eglDisplay);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

#ifdef MPE_PLATFORM_WINDOWS
    // Create an EGL window surface
    EGLSurface eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, glfwGetWin32Window(window), nullptr);
#elif MPE_PLATFORM_LINUX
    // Create an EGL window surface
    EGLSurface eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType) glfwGetX11Window(window), nullptr);
#endif
    if (eglSurface == EGL_NO_SURFACE)
    {
        std::cerr << "Failed to create EGL window surface: " << eglGetError() << std::endl;
        eglTerminate(eglDisplay);
        glfwDestroyWindow(window);
        glfwTerminate();
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
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Make the context current
    if (!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext))
    {
        std::cerr << "Failed to make EGL context current: " << eglGetError() << std::endl;
        eglDestroyContext(eglDisplay, eglContext);
        eglDestroySurface(eglDisplay, eglSurface);
        eglTerminate(eglDisplay);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Set the viewport
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        // Clear the color buffer
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers
        eglSwapBuffers(eglDisplay, eglSurface);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up EGL resources
    eglDestroyContext(eglDisplay, eglContext);
    eglDestroySurface(eglDisplay, eglSurface);
    eglTerminate(eglDisplay);

    // Clean up GLFW resources
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
