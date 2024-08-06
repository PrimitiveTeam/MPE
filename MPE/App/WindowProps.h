#pragma once

#include "MPE/Core/_CORE.h"

#include <string>

namespace MPE
{
struct MPE_API WindowProps
{
    std::string Title;
    int Width;
    int Height;
    int WindowPositionX;
    int WindowPositionY;
    int PreviousWidth;
    int PreviousHeight;
    int PreviousWindowPositionX;
    int PreviousWindowPositionY;

    WindowProps(const std::string &title = "MERE PRIMITIVE ENGINE", int width = 1280, int height = 720, int windowPositionX = 0, int windowPositionY = 0);
};
}