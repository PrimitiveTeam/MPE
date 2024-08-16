
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
        monitor.m_monitor = monitors[i];
        monitor.m_mode = glfwGetVideoMode(monitor.m_monitor);
        SYS_Monitors.push_back(monitor);

        MPE_CORE_INFO("Monitor {0}: {1}x{2} @ {3}Hz", i, monitor.m_mode->width, monitor.m_mode->height, monitor.m_mode->refreshRate);
    }
}

}