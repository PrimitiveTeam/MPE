
#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/App/WindowProps.h"

#include <GLFW/glfw3.h>

namespace MPE
{
// Create a monitor struct to store available monitors. Also, we will use GLFWMonitor to get the available monitors.
struct Monitor
{
    GLFWmonitor *monitor;
    const GLFWvidmode *mode;
};

class MPE_API WindowMonitors
{
  public:
    WindowMonitors();

    void UpdateMonitors();

    std::vector<Monitor> GetMonitors() { return m_monitors; }

  private:
    std::vector<Monitor> m_monitors;
};
}