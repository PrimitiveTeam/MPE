#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/GraphicalContextProps.h"

#include <string>

namespace MPE
{
struct MPE_API OpenGLContextProps : public GraphicalContextProps
{
    int MajorVersion;
    int MinorVersion;

    std::string Vendor;
    std::string Renderer;
    int ShaderTypeAmount;

    virtual std::string ToString() const override;
};
}