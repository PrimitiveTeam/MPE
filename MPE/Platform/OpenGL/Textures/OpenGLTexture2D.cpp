#include "OpenGLTexture2D.h"
#include "MPE/MPEPCH.h"

#include "MPE/Log/GlobalLog.h"
#include "MPE/Vendor/STB/stb_image.h"

namespace MPE
{
OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : WIDTH(width), HEIGHT(height)
{
    INTERNAL_FORMAT = GL_RGBA8;
    DATA_FORMAT = GL_RGBA;

    glCreateTextures(GL_TEXTURE_2D, 1, &SYS_RENDERER_ID);
    glTextureStorage2D(SYS_RENDERER_ID, 1, INTERNAL_FORMAT, WIDTH, HEIGHT);

    glTextureParameteri(SYS_RENDERER_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(SYS_RENDERER_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(SYS_RENDERER_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(SYS_RENDERER_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLTexture2D::OpenGLTexture2D(const std::string &filepath) : FILEPATH(filepath)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc *data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    MPE_CORE_ASSERT(data, "FAILED TO LOAD IMAGE AS TEXTURE");
    WIDTH = width;
    HEIGHT = height;

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

    INTERNAL_FORMAT = OpenGLInternalFormat;
    DATA_FORMAT = OpenGLDataFormat;

    glCreateTextures(GL_TEXTURE_2D, 1, &SYS_RENDERER_ID);
    glTextureStorage2D(SYS_RENDERER_ID, 1, OpenGLInternalFormat, WIDTH, HEIGHT);

    glTextureParameteri(SYS_RENDERER_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(SYS_RENDERER_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(SYS_RENDERER_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(SYS_RENDERER_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(SYS_RENDERER_ID, 0, 0, 0, WIDTH, HEIGHT, OpenGLDataFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &SYS_RENDERER_ID);
}

void OpenGLTexture2D::SetData(void *data, uint32_t size)
{
    uint32_t bpp = DATA_FORMAT == GL_RGBA ? 4 : 3;
    MPE_CORE_ASSERT(size == WIDTH * HEIGHT * bpp, "DATA IS NOT SET TO ENTIRE TEXTURE");
    glTextureSubImage2D(SYS_RENDERER_ID, 0, 0, 0, WIDTH, HEIGHT, DATA_FORMAT, GL_UNSIGNED_BYTE, data);
}

void OpenGLTexture2D::Bind(uint32_t slot) const
{
    glBindTextureUnit(slot, SYS_RENDERER_ID);
}
}