#import <Cocoa/Cocoa.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <iostream>
#include <thread>

// Function to perform rendering
void Render()
{
    // Clear the screen with a color
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, const char *argv[])
{
    // macOS-specific initialization
    NSApplication *app = [NSApplication sharedApplication];
    NSWindow *window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 640, 480)
                                                   styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO];
    [window setTitle:@"MetalANGLE - OpenGL ES 3.0"];
    [window makeKeyAndOrderFront:nil];

    // Obtain the native window handle
    NSView *contentView = [window contentView];
    [contentView setWantsLayer:YES];  // Make sure the view is layer-backed
    EGLNativeWindowType nativeWindow = (EGLNativeWindowType) contentView.layer;
    EGLNativeDisplayType nativeDisplay = EGL_DEFAULT_DISPLAY;

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

    // Choose an EGLConfig
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
                              16,
                              EGL_NONE};

    EGLConfig eglConfig;
    EGLint numConfigs;
    if (!eglChooseConfig(eglDisplay, configAttribs, &eglConfig, 1, &numConfigs) || numConfigs != 1)
    {
        std::cerr << "Failed to choose EGL config: " << eglGetError() << std::endl;
        return -1;
    }

    // Create an EGL rendering context
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    EGLContext eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs);
    if (eglContext == EGL_NO_CONTEXT)
    {
        std::cerr << "Failed to create EGL context: " << eglGetError() << std::endl;
        return -1;
    }

    // Create an EGL surface
    EGLSurface eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, nativeWindow, nullptr);
    if (eglSurface == EGL_NO_SURFACE)
    {
        std::cerr << "Failed to create EGL surface: " << eglGetError() << std::endl;
        return -1;
    }

    // Make the EGL context current
    if (!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext))
    {
        std::cerr << "Failed to make EGL context current: " << eglGetError() << std::endl;
        return -1;
    }

    // Main rendering loop
    while (![app isRunning])
    {
        Render();

        // Swap buffers
        eglSwapBuffers(eglDisplay, eglSurface);

        // Add a sleep or delay for your loop, if necessary
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    // Clean up
    eglDestroySurface(eglDisplay, eglSurface);
    eglDestroyContext(eglDisplay, eglContext);
    eglTerminate(eglDisplay);

    return 0;
}
