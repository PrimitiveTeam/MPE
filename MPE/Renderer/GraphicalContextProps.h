#pragma once

#include "MPE/Core/_CORE.h"

#include <string>

namespace MPE
{
struct MPE_API GraphicalContextProps
{
    int MajorVersion;
    int MinorVersion;

    std::string Vendor;
    std::string Renderer;
    int ShaderTypeAmount;

    virtual std::string ToString() const = 0;
};
}