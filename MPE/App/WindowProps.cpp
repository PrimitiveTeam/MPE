#include "WindowProps.h"
#include "MPEPCH.h"

namespace MPE
{
WindowProps::WindowProps(const std::string &title, int width, int height, int windowPositionX, int windowPositionY)
    : title(title),
      width(width),
      height(height),
      windowPositionX(windowPositionX),
      windowPositionY(windowPositionY),
      previousWidth(width),
      previousHeight(height),
      previousWindowPositionX(windowPositionX),
      previousWindowPositionY(windowPositionY)
{
}
}