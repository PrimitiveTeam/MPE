#include "RendererUtilities.h"
#include "MPE/MPEPCH.h"

#include "RenderPrimitive.h"

namespace MPE
{
RendererUtilities::RendererUtilities(glm::vec4 color) : SYS_COLOR(color) {}

RendererUtilities::~RendererUtilities() {}

void RendererUtilities::DrawClearColorScene()
{
    RenderPrimitive::SetClearColor(SYS_COLOR);
    RenderPrimitive::Clear();
}
}