#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Textures/Texture.h"

namespace MPE
{
class MPE_API Texture2D : public Texture
{
  public:
    static REF<Texture2D> Create(uint32_t width, uint32_t height);
    static REF<Texture2D> Create(const std::string &filepath);
};
}