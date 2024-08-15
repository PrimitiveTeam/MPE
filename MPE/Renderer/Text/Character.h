#pragma once

#include "MPE/Renderer/Textures/TextTexture.h"

#include <glm/glm.hpp>

namespace MPE
{
struct Character
{
    // Reference to the texture
    REF<TextTexture> m_texture;
    // Size of glyph
    glm::ivec2 m_size;
    // Offset from baseline to left/top of glyph
    glm::ivec2 m_bearing;
    // Offset to advance to next glyph
    unsigned int m_advance;
};
}