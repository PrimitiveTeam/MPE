#include "OpenGLESTexture2D.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/Vendor/STB/stb_image.h"

#include "Platform/OpenGLES/Utilities/OpenGLESUtilities.h"

namespace MPE
{
OpenGLESTexture2D::OpenGLESTexture2D(uint32_t width, uint32_t height) : WIDTH(width), HEIGHT(height)
{
    INTERNAL_FORMAT = GL_RGBA8;
    DATA_FORMAT = GL_RGBA;

    glGenTextures(1, &SYS_RENDERER_ID);

    glCheckError();

    glBindTexture(GL_TEXTURE_2D, SYS_RENDERER_ID);

    glCheckError();

    glTexImage2D(GL_TEXTURE_2D, 0, INTERNAL_FORMAT, WIDTH, HEIGHT, 0, DATA_FORMAT, GL_UNSIGNED_BYTE, nullptr);

    glCheckError();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glCheckError();
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

    glCheckError();

    glBindTexture(GL_TEXTURE_2D, SYS_RENDERER_ID);

    glCheckError();

    // TODO: Investigate if this is needed
    // glBindTexture(GL_TEXTURE_2D, SYS_RENDERER_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, INTERNAL_FORMAT, WIDTH, HEIGHT, 0, DATA_FORMAT, GL_UNSIGNED_BYTE, data);

    glCheckError();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glCheckError();

    stbi_image_free(data);
}

OpenGLESTexture2D::~OpenGLESTexture2D()
{
    MPE_CORE_WARN("DELETING TEXTURE: {0}x{1} | ID: {2}", WIDTH, HEIGHT, SYS_RENDERER_ID);
    glDeleteTextures(1, &SYS_RENDERER_ID);
}

void OpenGLESTexture2D::SetData(void *data, uint32_t size)
{
    uint32_t bpp = DATA_FORMAT == GL_RGBA ? 4 : 3;
    std::string dataErrStr = "DATA IS NOT SET TO ENTIRE TEXTURE: " + std::to_string(size) + " | " + std::to_string(WIDTH * HEIGHT * bpp) +
                             " == " + std::to_string(WIDTH * HEIGHT * bpp);
    MPE_CORE_ASSERT(size == WIDTH * HEIGHT * bpp, dataErrStr);

    glBindTexture(GL_TEXTURE_2D, SYS_RENDERER_ID);

    glTexImage2D(GL_TEXTURE_2D, 0, INTERNAL_FORMAT, WIDTH, HEIGHT, 0, DATA_FORMAT, GL_UNSIGNED_BYTE, data);

    glCheckError();
}

void OpenGLESTexture2D::Bind(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, SYS_RENDERER_ID);
}

void OpenGLESTexture2D::Unbind(uint32_t slot) const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
}