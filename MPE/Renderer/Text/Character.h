#pragma once

#include "MPE/Renderer/Textures/TextTexture.h"

#include <glm/glm.hpp>

namespace MPE
{
struct Character
{
    // Reference to the texture
    REF<TextTexture> texture;
    // Size of glyph
    glm::ivec2 size;
    // Offset from baseline to left/top of glyph
    glm::ivec2 bearing;
    // Offset to advance to next glyph
    unsigned int advance;
};
}