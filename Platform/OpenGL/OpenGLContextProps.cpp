#include "OpenGLContextProps.h"
#include "MPEPCH.h"

namespace MPE
{
std::string OpenGLContextProps::ToString() const
{
    std::string OpenGlInfo = "OpenGL Info:\n";
    OpenGlInfo += "\tOpenGL Version: " + std::to_string(MajorVersion) + "." + std::to_string(MinorVersion) + "\n";
    OpenGlInfo += "\tVendor: " + Vendor + "\n";
    OpenGlInfo += "\tRenderer: " + Renderer + "\n";
    OpenGlInfo += "\tHardcode shader type limit: " + std::to_string(ShaderTypeAmount);

    return OpenGlInfo;
}
}