#define GLFW_EXPOSE_NATIVE_WIN32

// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <GLFW/glfw3native.h>
// #include <iostream>
// #include <windows.h>

// // use this include with path "C:\Dev\vcpkg\installed\x64-windows\include\GLFW\glfw3native.h"
// #include "C:\Dev\vcpkg\installed\x64-windows\include\GLFW\glfw3native.h"

// // Include EGL for OpenGL ES context management
// #include <EGL/egl.h>

// // Error callback function for GLFW
// void glfwErrorCallback(int error, const char* description)
// {
//     std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
// }

// // Main function
// int main()
// {
//     // Set the GLFW error callback
//     glfwSetErrorCallback(glfwErrorCallback);

//     // Initialize GLFW
//     if (!glfwInit())
//     {
//         std::cerr << "Failed to initialize GLFW" << std::endl;
//         return -1;
//     }

//     // Prevent GLFW from creating an OpenGL context
//     glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

//     // Create a GLFW window
//     GLFWwindow* window = glfwCreateWindow(800, 600, "ANGLE with GLFW", nullptr, nullptr);
//     if (!window)
//     {
//         std::cerr << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }

//     EGLDisplay eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
//     if (eglDisplay == EGL_NO_DISPLAY)
//     {
//         std::cerr << "Failed to get EGL display" << std::endl;
//         glfwDestroyWindow(window);
//         glfwTerminate();
//         return -1;
//     }

//     // Initialize EGL
//     if (!eglInitialize(eglDisplay, nullptr, nullptr))
//     {
//         std::cerr << "Failed to initialize EGL" << std::endl;
//         glfwDestroyWindow(window);
//         glfwTerminate();
//         return -1;
//     }

//     // Choose an EGLConfig
//     EGLint configAttribs[] = {EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_NONE};

//     EGLConfig eglConfig;
//     EGLint numConfigs;
//     if (!eglChooseConfig(eglDisplay, configAttribs, &eglConfig, 1, &numConfigs) || numConfigs == 0)
//     {
//         std::cerr << "Failed to choose EGL config" << std::endl;
//         eglTerminate(eglDisplay);
//         glfwDestroyWindow(window);
//         glfwTerminate();
//         return -1;
//     }

//     // Create an EGLSurface using the GLFW window
//     EGLSurface eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, glfwGetWin32Window(window), nullptr);
//     if (eglSurface == EGL_NO_SURFACE)
//     {
//         std::cerr << "Failed to create EGL surface" << std::endl;
//         eglTerminate(eglDisplay);
//         glfwDestroyWindow(window);
//         glfwTerminate();
//         return -1;
//     }

//     // Create an EGLContext
//     EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2,  // OpenGL ES 2.0
//                                EGL_NONE};

//     EGLContext eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs);
//     if (eglContext == EGL_NO_CONTEXT)
//     {
//         std::cerr << "Failed to create EGL context" << std::endl;
//         eglDestroySurface(eglDisplay, eglSurface);
//         eglTerminate(eglDisplay);
//         glfwDestroyWindow(window);
//         glfwTerminate();
//         return -1;
//     }

//     // Make the EGL context current
//     if (!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext))
//     {
//         std::cerr << "Failed to make EGL context current" << std::endl;
//         eglDestroyContext(eglDisplay, eglContext);
//         eglDestroySurface(eglDisplay, eglSurface);
//         eglTerminate(eglDisplay);
//         glfwDestroyWindow(window);
//         glfwTerminate();
//         return -1;
//     }

//     // Initialize GLAD for OpenGL ES
//     if (!gladLoadGLES2Loader((GLADloadproc) eglGetProcAddress))
//     {
//         std::cerr << "Failed to initialize GLAD" << std::endl;
//         eglDestroyContext(eglDisplay, eglContext);
//         eglDestroySurface(eglDisplay, eglSurface);
//         eglTerminate(eglDisplay);
//         glfwDestroyWindow(window);
//         glfwTerminate();
//         return -1;
//     }

//     // Main loop
//     while (!glfwWindowShouldClose(window))
//     {
//         // Set the viewport
//         int width, height;
//         glfwGetFramebufferSize(window, &width, &height);
//         glViewport(0, 0, width, height);

//         // Clear the color buffer
//         glClearColor(0.1f, 0.2f, 0.3f, 1.0f);  // Set a clear color
//         glClear(GL_COLOR_BUFFER_BIT);

//         // Swap buffers
//         eglSwapBuffers(eglDisplay, eglSurface);

//         // Poll for and process events
//         glfwPollEvents();
//     }

//     // Clean up EGL resources
//     eglDestroyContext(eglDisplay, eglContext);
//     eglDestroySurface(eglDisplay, eglSurface);
//     eglTerminate(eglDisplay);

//     // Clean up GLFW resources
//     glfwDestroyWindow(window);
//     glfwTerminate();

//     return 0;
// }

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <iostream>
#include <windows.h>
#include <thread>

int main()
{
    // Get the native display handle (HDC) for the entire screen
    EGLNativeDisplayType nativeDisplay = GetDC(nullptr);

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
