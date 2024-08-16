#include "OpenGLTexture2D.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/Vendor/STB/stb_image.h"

#include "Platform/OpenGL/Utilities/OpenGLUtilities.h"

namespace MPE
{
OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : m_width(width), m_height(height)
{
    MPE_CORE_WARN("CREATING TEXTURE...");

    m_internalFormat = GL_RGBA8;
    m_dataFormat = GL_RGBA;

#ifdef MPE_PLATFORM_OSX
    glGenTextures(1, &m_textTextureId);

    glCheckError();

    glBindTexture(GL_TEXTURE_2D, m_textTextureId);

    glCheckError();

    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_dataFormat, GL_UNSIGNED_BYTE, nullptr);

    glCheckError();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glCheckError();

    // NOTE: Do not unbind the texture
    // glBindTexture(GL_TEXTURE_2D, 0);
#else
    glCreateTextures(GL_TEXTURE_2D, 1, &m_textTextureId);
    glTextureStorage2D(m_textTextureId, 1, m_internalFormat, m_width, m_height);

    glTextureParameteri(m_textTextureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_textTextureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_textTextureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_textTextureId, GL_TEXTURE_WRAP_T, GL_REPEAT);
#endif

    glCheckError();
    MPE_CORE_ASSERT(m_textTextureId, "TEXTURE NOT CREATED");
    MPE_CORE_INFO("TEXTURE CREATED: {0}x{1} | ID: {2}", m_width, m_height, m_textTextureId);
}

OpenGLTexture2D::OpenGLTexture2D(const std::string &filepath) : m_filepath(filepath)
{
    MPE_CORE_WARN("CREATING TEXTURE...");

    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc *data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    MPE_CORE_ASSERT(data, "FAILED TO LOAD IMAGE AS TEXTURE");
    m_width = width;
    m_height = height;

    GLenum OpenGLInternalFormat = 0, OpenGLDataFormat = 0;
    switch (channels)
    {
        case 3:
            OpenGLInternalFormat = GL_RGB8;
            OpenGLDataFormat = GL_RGB;
            MPE_CORE_WARN("TEXTURE IMAGE FORMAT: RGB8/RGB");
            break;
        case 4:
            OpenGLInternalFormat = GL_RGBA8;
            OpenGLDataFormat = GL_RGBA;
            MPE_CORE_WARN("TEXTURE IMAGE FORMAT: RGB8/RGBA");
            break;
        default:
            MPE_CORE_ERROR("IMAGE FORMAT FOR TEXTURE IS INVALID");
            MPE_CORE_ASSERT(OpenGLInternalFormat || OpenGLDataFormat, "IMAGE FORMAT FOR TEXTURE IS NOT SUPPORTED");
            return;
    }

    m_internalFormat = OpenGLInternalFormat;
    m_dataFormat = OpenGLDataFormat;

#ifdef MPE_PLATFORM_OSX
    glGenTextures(1, &m_textTextureId);

    glCheckError();

    glBindTexture(GL_TEXTURE_2D, m_textTextureId);

    glCheckError();

    // TODO: Investigate if this is needed
    // glBindTexture(GL_TEXTURE_2D, m_textTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_dataFormat, GL_UNSIGNED_BYTE, data);

    glCheckError();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glCheckError();

    // NOTE: Do not unbind the texture
    // glBindTexture(GL_TEXTURE_2D, 0);
#else

    glCreateTextures(GL_TEXTURE_2D, 1, &m_textTextureId);
    glTextureStorage2D(m_textTextureId, 1, m_internalFormat, m_width, m_height);

    glTextureParameteri(m_textTextureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_textTextureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_textTextureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_textTextureId, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(m_textTextureId, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);

#endif
    glCheckError();

    stbi_image_free(data);

    MPE_CORE_ASSERT(m_textTextureId, "TEXTURE NOT CREATED");
    MPE_CORE_INFO("TEXTURE CREATED: {0}x{1} | ID: {2}", m_width, m_height, m_textTextureId);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
    MPE_CORE_WARN("DELETING TEXTURE: {0}x{1} | ID: {2}", m_width, m_height, m_textTextureId);
    glDeleteTextures(1, &m_textTextureId);
}

void OpenGLTexture2D::SetData(void *data, uint32_t size)
{
    uint32_t bpp = m_dataFormat == GL_RGBA ? 4 : 3;
    std::string dataErrStr = "DATA IS NOT SET TO ENTIRE TEXTURE: " + std::to_string(size) + " | " + std::to_string(m_width * m_height * bpp) +
                             " == " + std::to_string(m_width * m_height * bpp);
    MPE_CORE_ASSERT(size == m_width * m_height * bpp, dataErrStr);

#ifdef MPE_PLATFORM_OSX
    glBindTexture(GL_TEXTURE_2D, m_textTextureId);

    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_dataFormat, GL_UNSIGNED_BYTE, data);
    // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);

    // NOTE: Do not unbind the texture
    // glBindTexture(GL_TEXTURE_2D, 0);
#else
    glTextureSubImage2D(m_textTextureId, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
#endif

    glCheckError();
}

void OpenGLTexture2D::Bind(uint32_t slot) const
{
#ifdef MPE_PLATFORM_OSX
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textTextureId);
#else
    glBindTextureUnit(slot, m_textTextureId);
#endif
}

void OpenGLTexture2D::Unbind(uint32_t slot) const
{
#ifdef MPE_PLATFORM_OSX
    glBindTexture(GL_TEXTURE_2D, 0);
#else
    glBindTextureUnit(slot, 0);
#endif
}
}