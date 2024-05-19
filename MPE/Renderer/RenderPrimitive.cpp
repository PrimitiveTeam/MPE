#include "RenderPrimitive.h"
#include "MPEPCH.h"

#include "MPE/Platform/OpenGL/OpenGLRendererAPI.h"

namespace MPE
{
RendererAPI *RenderPrimitive::SYS_API = new OpenGLRendererAPI;
}