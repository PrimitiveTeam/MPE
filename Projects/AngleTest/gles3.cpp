#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <EGL/egl.h>
#include <GLES3/gl31.h>  // Include GLES3 header for OpenGL ES 3.1 functions
#include <iostream>
#include <windows.h>

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

    // Obtain the EGL display connection using the native display from GLFW
    EGLDisplay eglDisplay = eglGetDisplay(GetDC(glfwGetWin32Window(window)));
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
    EGLint configAttribs[] = {EGL_SURFACE_TYPE,
                              EGL_WINDOW_BIT,  // Create a window surface
                              EGL_RENDERABLE_TYPE,
                              EGL_OPENGL_ES2_BIT | EGL_OPENGL_ES3_BIT,  // Request ES2 or ES3 capabilities
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
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Create an EGL window surface
    EGLSurface eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, glfwGetWin32Window(window), nullptr);
    if (eglSurface == EGL_NO_SURFACE)
    {
        std::cerr << "Failed to create EGL window surface: " << eglGetError() << std::endl;
        eglTerminate(eglDisplay);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Create an OpenGL ES 3.1 context
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_CONTEXT_MINOR_VERSION, 1, EGL_NONE};
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
        glClearColor(1.0f, 1.0f, 0.8f, 1.0f);
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
