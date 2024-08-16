#include "WindowProps.h"
#include "MPEPCH.h"

namespace MPE
{
WindowProps::WindowProps(const std::string &title, int width, int height, int windowPositionX, int windowPositionY)
    : m_title(title),
      m_width(width),
      m_height(height),
      m_windowPositionX(windowPositionX),
      m_windowPositionY(windowPositionY),
      m_previousWidth(width),
      m_previousHeight(height),
      m_previousWindowPositionX(windowPositionX),
      m_previousWindowPositionY(windowPositionY)
{
}
}