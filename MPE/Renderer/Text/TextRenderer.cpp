#include "TextRenderer.h"

#include <glad/glad.h>

namespace MPE
{
void TextRenderer::RenderAllASCII(float x, float y, float scale, const glm::vec4& color)
{
    // Starting x position for rendering
    float startX = x;
    // Starting y position for rendering
    float startY = y;
    // float x = startX;
    // float y = startY;

    // Loop through all ASCII characters
    for (GLubyte c = 0; c < 128; c++)
    {
        std::string character(1, static_cast<char>(c));
        this->RenderText(character, x, y, scale, color);

        // Move to the next position
        // Advance x position for next character
        x += 40.0f;

        // Create a new line if necessary
        // 16 characters per row
        if (c % 16 == 15)
        {
            x = startX;
            // Advance to the next line
            y -= 60.0f;
        }
    }
}
}