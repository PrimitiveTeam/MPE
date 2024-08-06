#include "WindowProps.h"
#include "MPEPCH.h"

namespace MPE
{
WindowProps::WindowProps(const std::string &title, int width, int height, int windowPositionX, int windowPositionY)
    : Title(title), Width(width), Height(height), WindowPositionX(windowPositionX), WindowPositionY(windowPositionY)
{
    PreviousWidth = width;
    PreviousHeight = height;
    PreviousWindowPositionX = windowPositionX;
    PreviousWindowPositionY = windowPositionY;
}
}