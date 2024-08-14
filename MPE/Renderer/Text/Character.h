#pragma once

#include "MPE/Renderer/Textures/TextTexture.h"

#include <glm/glm.hpp>

namespace MPE
{
struct Character
{
    // Reference to the texture
    REF<TextTexture> Texture;
    // Size of glyph
    glm::ivec2 Size;
    // Offset from baseline to left/top of glyph
    glm::ivec2 Bearing;
    // Offset to advance to next glyph
    unsigned int Advance;
};
}