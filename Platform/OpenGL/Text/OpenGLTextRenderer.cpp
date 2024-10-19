#include "OpenGLTextRenderer.h"

#include "Platform/OpenGL/Shaders/OpenGLShader.h"
#include "MPE/App/App.h"
#include "Platform/OpenGL/Utilities/OpenGLUtilities.h"

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

// To use glm::to_string
#if !defined(MPE_PLATFORM_OSX)
#    define GLM_ENABLE_EXPERIMENTAL
#endif

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <map>

#include <glad/glad.h>
#include "MPE/Vendor/GLM/GLM.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <filesystem>

namespace MPE
{
OpenGLTextRenderer::OpenGLTextRenderer(const std::string& shaderPath, const std::string& fontPath, int fontSize)
{
    m_shaderPath = shaderPath;
    m_fontPath = fontPath;
    m_fontSize = fontSize;
    // m_mainCamera = camera;

    // Enable pixel alignment by default
    m_pixelAlign = true;

    m_shader = Shader::Create(m_shaderPath, true);

    this->InitializeFont();
}

OpenGLTextRenderer::~OpenGLTextRenderer()
{
    FT_Done_Face(m_Face);
    FT_Done_FreeType(m_FT);
}

void OpenGLTextRenderer::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowResizeEvent>(MPE_BIND_EVENT_FUNCTION(OpenGLTextRenderer::OnWindowResize));
}

void OpenGLTextRenderer::InitializeFont()
{
    // Initialize FreeType
    if (FT_Init_FreeType(&m_FT))
    {
        MPE_CORE_ASSERT(false, "Could not init FreeType Library");
        return;
    }

    // Check if path to font exists using io
    if (!std::filesystem::exists(m_fontPath))
    {
        MPE_CORE_ASSERT(false, "Font file does not exist");
        return;
    }

    // Load font
    if (FT_New_Face(m_FT, m_fontPath.c_str(), 0, &m_Face))
    {
        MPE_CORE_ASSERT(false, "Failed to load font");
        return;
    }

    FT_Set_Pixel_Sizes(m_Face, 0, m_fontSize);

    LoadCharacters();

    this->UpdateProjection(App::GetApp().GetWindow().get()->GetWidth(), App::GetApp().GetWindow().get()->GetHeight());

    // PURE METHOD
    {
        // glCreateVertexArrays(1, &vao);
        // glBindVertexArray(vao);

        // glCreateBuffers(1, &buffer);

        // glNamedBufferStorage(buffer, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_STORAGE_BIT);
        // glVertexArrayVertexBuffer(vao, 0, buffer, 0, sizeof(GLfloat) * 4);
        // glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);
        // glVertexArrayAttribBinding(vao, 0, 0);
        // glEnableVertexArrayAttrib(vao, 0);
    }

    // API METHOD
    {
        m_VAO = VertexArray::Create();

        m_VAO->Bind();

        m_VBO = VertexBuffer::Create(sizeof(float) * 6 * 4);

        m_VBO->Bind();
        m_VBO->SetLayout({{ShaderDataType::Vec4, "UNI_TEXTURE_COORDS"}});

        m_VAO->AddVertexBuffer(m_VBO);

        m_VAO->Unbind();
        m_VBO->Unbind();

        // TODO: Investigate drawing text using index buffer
        // uint32_t indices[6] = {0, 1, 2, 2, 3, 0};
        // uint32_t indices[6] = {0, 1, 2, 0, 2, 3};
        // auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        // m_VAO->SetIndexBuffer(indexBuffer);
    }
}

void OpenGLTextRenderer::UnInitializeFont()
{
    m_shader->Unbind();
    FT_Done_Face(m_Face);
    FT_Done_FreeType(m_FT);

    // Make sure to remove all references to the textures and characters
    m_characters.clear();
}

void OpenGLTextRenderer::UpdateProjection(float screenWidth, float screenHeight)
{
    // GLint vp[4];
    // glGetIntegerv (GL_VIEWPORT, vp);
    // printf("Viewport: %d %d %d %d\n\n\n", vp[0], vp[1], vp[2], vp[3]);

    // TODO: Modify this to use the built-in camera as currently the viewport/camera must be pixel perfect to render text
    glm::mat4 projection = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight);

    // printf("Projection: %s\n\n", glm::to_string(projection).c_str());
    // printf("Camera Projection Matrix: %s\n\n", glm::to_string(m_MainCamera->GetProjectionMatrix()).c_str());
    // printf("Camera View Projection Matrix: %s\n\n", glm::to_string(m_MainCamera->GetProjectionViewMatrix()).c_str());
    // printf("Camera View Matrix: %s\n\n", glm::to_string(m_MainCamera->GetViewMatrix()).c_str());

    // transformation can still be used as well as scaling, but scaling does not work well
    // glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    // projection = projection * (transform * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f)));

    // printf("Final Projection: %s\n\n", glm::to_string(projection).c_str());
    // glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(projection));
    m_shader->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLShader>(m_shader)->InjectUniformMat4("UNI_PROJECTION_MATRIX", projection);
}

void OpenGLTextRenderer::LoadCharacters()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(m_Face, c, FT_LOAD_RENDER))
        {
            MPE_CORE_ASSERT(false, fmt::format("ERROR::FREETYTPE: Failed to load Glyph {}", c));
            return;
        }

        // In ASCII, Glyphs like 'Glyph 0 (Null Character)', 'Glyph 13 (Carriage Return)', and 'Glyph 32 (Space Character)' have no bitmap data, therefore we
        // skip them This avoids OpenGL errors as well
        if (m_Face->glyph->bitmap.width == 0 || m_Face->glyph->bitmap.rows == 0)
        {
            MPE_CORE_WARN("Glyph {} has no height or weight. This is most likely expected.", c);

            // Handle glyphs with no bitmap, like space, using advance.x for spacing
            Character character = {nullptr, glm::ivec2(0, 0), glm::ivec2(0, 0), static_cast<unsigned int>(m_Face->glyph->advance.x)};
            m_characters.insert(std::pair<GLchar, Character>(c, character));
            continue;
        }

        // PURE METHOD
        // {
        //     GLuint texture;
        //     glCreateTextures(GL_TEXTURE_2D, 1, &texture);
        //     glTextureStorage2D(texture, 1, GL_R8, m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows);
        //     glTextureSubImage2D(texture, 0, 0, 0, m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE,
        //                         m_Face->glyph->bitmap.buffer);

        //     glBindTexture(GL_TEXTURE_2D, texture);
        //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //     glBindTexture(GL_TEXTURE_2D, 0);

        //     MPE_WARN("Current Texture ID: {}", texture);
        //     Character character = {texture, glm::ivec2(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
        //                            glm::ivec2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top), m_Face->glyph->advance.x};
        //     m_Characters.insert(std::pair<GLchar, Character>(c, character));
        // }

        // API METHOD
        {  // Create a texture from glyph bitmap
            auto texture = TextTexture::Create(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows);
            texture->SetData(m_Face->glyph->bitmap.buffer, m_Face->glyph->bitmap.width * m_Face->glyph->bitmap.rows);

            Character character = {texture, glm::ivec2(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
                                   glm::ivec2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top), (GLuint) m_Face->glyph->advance.x};
            m_characters.insert(std::pair<GLchar, Character>(c, character));

            texture->Unbind();
        }
    }
}

void OpenGLTextRenderer::RenderText(const std::string& text, float x, float y, float scale, const glm::vec4& color)
{
    m_shader->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLShader>(m_shader)->InjectUniformFloat4("UNI_TEXT_COLOR", color);

    float internal_x = x;
    float internal_y = y;
    float internal_scale = scale;

    m_VAO->Bind();
    m_VBO->Bind();

    // not sure this is needed
    // glActiveTexture(GL_TEXTURE0);
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = m_characters[*c];
        float xpos, ypos, h, w;

        if (m_pixelAlign)
        {
            xpos = round(internal_x + ch.bearing.x * internal_scale);
            ypos = round(internal_y - (ch.size.y - ch.bearing.y) * internal_scale);
            // h = round(ch.Size.y * internal_scale);
            // w = round(ch.Size.x * internal_scale);
        }
        else
        {
            xpos = internal_x + ch.bearing.x * internal_scale;
            ypos = internal_y - (ch.size.y - ch.bearing.y) * internal_scale;
            // w = ch.Size.x * internal_scale;
            // h = ch.Size.y * internal_scale;
        }

        // Scaling still has artifacting issues
        w = ch.size.x * internal_scale;
        h = ch.size.y * internal_scale;

        // Update VBO for each character
        float vertices[6 * 4] = {xpos, ypos + h, 0.0f, 0.0f, xpos,     ypos, 0.0f, 1.0f, xpos + w, ypos,     1.0f, 1.0f,

                                 xpos, ypos + h, 0.0f, 0.0f, xpos + w, ypos, 1.0f, 1.0f, xpos + w, ypos + h, 1.0f, 0.0f};

        // PURE METHOD
        // {
        //     glNamedBufferSubData(buffer, 0, sizeof(GLfloat) * 6 * 4, vertices);

        //     glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // }

        // API METHOD
        {
            m_VBO->SetData(vertices, sizeof(vertices));

            // There are characters with no bitmaps, so a nullptr is passed, we don't want to accidentally dereference a nullptr
            if (ch.texture != nullptr) ch.texture->Bind(0);
        }

        glDrawArrays(GL_TRIANGLES, 0, 6);

        internal_x += (ch.advance >> 6) * internal_scale;

        glCheckError();
    }
    glCheckError();

    m_VAO->Unbind();
    m_VBO->Unbind();
}

void OpenGLTextRenderer::SetFontSize(float fontSize)
{
    // If provided font size is the same as the current font size, do nothing
    if (m_fontSize == fontSize) return;

    m_fontSize = fontSize;

    this->UnInitializeFont();

    this->InitializeFont();
    this->UpdateProjection(App::GetApp().GetWindow().get()->GetWidth(), App::GetApp().GetWindow().get()->GetHeight());
}

bool OpenGLTextRenderer::OnWindowResize(WindowResizeEvent& e)
{
    this->UpdateProjection(e.GetWidth(), e.GetHeight());
    return true;
}
}