
#include "WindowMonitors.h"

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"

namespace MPE
{

WindowMonitors::WindowMonitors()
{
    UpdateMonitors();
}

void WindowMonitors::UpdateMonitors()
{
    int count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);

    for (int i = 0; i < count; i++)
    {
        Monitor monitor;
        monitor.monitor = monitors[i];
        monitor.mode = glfwGetVideoMode(monitor.monitor);
        m_monitors.push_back(monitor);

        MPE_CORE_INFO("Monitor {0}: {1}x{2} @ {3}Hz", i, monitor.mode->width, monitor.mode->height, monitor.mode->refreshRate);
    }
}

}