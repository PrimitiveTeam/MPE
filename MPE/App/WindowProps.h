#pragma once

#include "MPE/Core/_CORE.h"

#include <string>

namespace MPE
{
struct MPE_API WindowProps
{
    std::string title;
    int width;
    int height;
    int windowPositionX;
    int windowPositionY;
    int previousWidth;
    int previousHeight;
    int previousWindowPositionX;
    int previousWindowPositionY;

    WindowProps(const std::string &title = "MERE PRIMITIVE ENGINE", int width = 1280, int height = 720, int windowPositionX = 0, int windowPositionY = 0);
};
}