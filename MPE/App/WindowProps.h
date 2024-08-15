#pragma once

#include "MPE/Core/_CORE.h"

#include <string>

namespace MPE
{
struct MPE_API WindowProps
{
    std::string m_title;
    int m_width;
    int m_height;
    int m_windowPositionX;
    int m_windowPositionY;
    int m_previousWidth;
    int m_previousHeight;
    int m_previousWindowPositionX;
    int m_previousWindowPositionY;

    WindowProps(const std::string &title = "MERE PRIMITIVE ENGINE", int width = 1280, int height = 720, int windowPositionX = 0, int windowPositionY = 0);
};
}