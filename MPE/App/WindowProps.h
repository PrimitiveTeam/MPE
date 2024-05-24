#pragma once

#include "MPE/Core/_CORE.h"

#include <string>

namespace MPE
{
struct MPE_API WindowProps
{
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    WindowProps(const std::string &title = "MERE PRIMITIVE ENGINE", unsigned int width = 1280, unsigned int height = 720);
};
}