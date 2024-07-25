#include "OpenGLESTexture2D.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/Vendor/STB/stb_image.h"

namespace MPE
{
OpenGLESTexture2D::OpenGLESTexture2D(uint32_t width, uint32_t height) : WIDTH(width), HEIGHT(height)
{
    INTERNAL_FORMAT = GL_RGBA8;
    DATA_FORMAT = GL_RGBA;

    glGenTextures(1, &SYS_RENDERER_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, INTERNAL_FORMAT, WIDTH, HEIGHT, 0, DATA_FORMAT, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(SYS_RENDERER_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(SYS_RENDERER_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(SYS_RENDERER_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(SYS_RENDERER_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLESTexture2D::OpenGLESTexture2D(const std::string &filepath) : FILEPATH(filepath)
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

    glGenTextures(1, &SYS_RENDERER_ID);
    // TODO: Investigate if this is needed
    // glBindTexture(GL_TEXTURE_2D, SYS_RENDERER_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, OpenGLInternalFormat, WIDTH, HEIGHT, 0, OpenGLDataFormat, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_image_free(data);
}

OpenGLESTexture2D::~OpenGLESTexture2D()
{
    glDeleteTextures(1, &SYS_RENDERER_ID);
}

void OpenGLESTexture2D::SetData(void *data, uint32_t size)
{
    uint32_t bpp = DATA_FORMAT == GL_RGBA ? 4 : 3;
    MPE_CORE_ASSERT(size == WIDTH * HEIGHT * bpp, "DATA IS NOT SET TO ENTIRE TEXTURE");

    glTexSubImage2D(SYS_RENDERER_ID, 0, 0, 0, WIDTH, HEIGHT, DATA_FORMAT, GL_UNSIGNED_BYTE, data);
}

void OpenGLESTexture2D::Bind(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
}

}