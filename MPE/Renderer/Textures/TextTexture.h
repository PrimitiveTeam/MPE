#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Textures/Texture.h"

namespace MPE
{
class MPE_API TextTexture : public Texture
{
  public:
    static REF<TextTexture> Create(uint32_t width, uint32_t height);
    static REF<TextTexture> Create(const std::string &filepath);
};
}