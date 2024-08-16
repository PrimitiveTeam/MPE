#include "OpenGLTextTexture.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/Vendor/STB/stb_image.h"
#include "Platform/OpenGL/Utilities/OpenGLUtilities.h"

namespace MPE
{
OpenGLTextTexture::OpenGLTextTexture(uint32_t width, uint32_t height) : m_width(width), m_height(height), m_textTextureId(0)
{
    MPE_CORE_WARN("CREATING TEXTURE...");

    m_internalFormat = GL_R8;
    m_dataFormat = GL_RED;

#ifdef MPE_PLATFORM_OSX
    glGenTextures(1, &m_textTextureId);

    glCheckError();

    glBindTexture(GL_TEXTURE_2D, m_textTextureId);

    glCheckError();

    // TODO: Investigate => potentially not necessary
    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_dataFormat, GL_UNSIGNED_BYTE, nullptr);

    glCheckError();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glCheckError();

    // NOTE: Do not unbind the texture
    // glBindTexture(GL_TEXTURE_2D, 0);
#else
    glCreateTextures(GL_TEXTURE_2D, 1, &m_textTextureId);

    glCheckError();

    glTextureStorage2D(m_textTextureId, 1, m_internalFormat, m_width, m_height);

    glCheckError();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glCheckError();
#endif

    MPE_CORE_ASSERT(m_textTextureId, "TEXTURE NOT CREATED");
    MPE_CORE_INFO("TEXTURE CREATED: {0}x{1} | ID: {2}", m_width, m_height, m_textTextureId);
}

OpenGLTextTexture::OpenGLTextTexture(const std::string &filepath) : m_filepath(filepath)
{
    MPE_ASSERT(false, "NOT IMPLEMENTED YET");
}

OpenGLTextTexture::~OpenGLTextTexture()
{
    MPE_CORE_WARN("DELETING TEXTURE: {0}x{1} | ID: {2}", m_width, m_height, m_textTextureId);
    glDeleteTextures(1, &m_textTextureId);
}

void OpenGLTextTexture::SetData(void *data, uint32_t size)
{
    uint32_t bpp = 0;
    bpp = m_dataFormat == GL_RED ? 1 : 0;
    std::string dataErrStr = "DATA IS NOT SET TO ENTIRE TEXTURE: " + std::to_string(size) + " | " + std::to_string(m_width * m_height * bpp) +
                             " == " + std::to_string(m_width * m_height * bpp);
    MPE_CORE_ASSERT(size == m_width * m_height * bpp, dataErrStr);

#ifdef MPE_PLATFORM_OSX
    glBindTexture(GL_TEXTURE_2D, m_textTextureId);

    // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_dataFormat, GL_UNSIGNED_BYTE, data);
// glTexImage2D(GL_TEXTURE_2D, 0, m_dataFormat, m_width, m_height, 0, m_dataFormat, GL_UNSIGNED_BYTE, data);

// NOTE: Do not unbind the texture
// glBindTexture(GL_TEXTURE_2D, 0);
#else
    glTextureSubImage2D(m_textTextureId, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
#endif

    glCheckError();
}

void OpenGLTextTexture::Bind(uint32_t slot) const
{
#ifdef MPE_PLATFORM_OSX
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textTextureId);
#else
    glBindTextureUnit(slot, m_textTextureId);
#endif
}

void OpenGLTextTexture::Unbind(uint32_t slot) const
{
#ifdef MPE_PLATFORM_OSX
    glBindTexture(GL_TEXTURE_2D, 0);
#else
    glBindTextureUnit(slot, 0);
#endif
}
}