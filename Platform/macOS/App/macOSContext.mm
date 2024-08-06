#include "macOSContext.h"
#include "MPE/Log/GlobalLog.h"

#define GLFW_EXPOSE_NATIVE_COCOA

#include <GLFW/glfw3native.h>
#include <GLES3/gl31.h>

namespace MPE
{
    EGLNativeWindowType macOSContext::GetNativeWindow(GLFWwindow* window)
    {
        NSWindow* nsWindow = static_cast<NSWindow*>(glfwGetCocoaWindow(window));
        if (!nsWindow)
        {
            std::cerr << "Failed to get NSWindow from GLFWwindow" << std::endl;
            return nullptr;
        }

        NSView* contentView = [nsWindow contentView];
        [contentView setWantsLayer:YES];  // Make sure the view is layer-backed
        return (EGLNativeWindowType)[contentView layer];
    }
}
