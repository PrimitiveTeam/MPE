#pragma once

#include "MPE/Core/_CORE.h"

#include <GLFW/glfw3.h>
#include <EGL/egl.h>

namespace MPE
{
    class macOSContext
    {
        public:
        static EGLNativeWindowType GetNativeWindow(GLFWwindow* window);
    };
}