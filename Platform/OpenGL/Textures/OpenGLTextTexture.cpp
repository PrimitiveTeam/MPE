#include "OpenGLTextTexture.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/Vendor/STB/stb_image.h"
#include "Platform/OpenGL/Utilities/OpenGLUtilities.h"

namespace MPE
{
OpenGLTextTexture::OpenGLTextTexture(uint32_t width, uint32_t height) : WIDTH(width), HEIGHT(height), SYS_RENDERER_ID(0)
{
    MPE_CORE_WARN("CREATING TEXTURE...");

    INTERNAL_FORMAT = GL_R8;
    DATA_FORMAT = GL_RED;

#ifdef MPE_PLATFORM_OSX
    MPE_ASSERT(false, "NOT IMPLEMENTED YET");
#else
    glCreateTextures(GL_TEXTURE_2D, 1, &SYS_RENDERER_ID);

    glCheckError();

    glTextureStorage2D(SYS_RENDERER_ID, 1, INTERNAL_FORMAT, WIDTH, HEIGHT);

    glCheckError();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glCheckError();
#endif

    MPE_CORE_ASSERT(SYS_RENDERER_ID, "TEXTURE NOT CREATED");
    MPE_CORE_INFO("TEXTURE CREATED: {0}x{1} | ID: {2}", WIDTH, HEIGHT, SYS_RENDERER_ID);
}

OpenGLTextTexture::OpenGLTextTexture(const std::string &filepath) : FILEPATH(filepath)
{
    MPE_ASSERT(false, "NOT IMPLEMENTED YET");
}

OpenGLTextTexture::~OpenGLTextTexture()
{
    MPE_CORE_WARN("DELETING TEXTURE: {0}x{1} | ID: {2}", WIDTH, HEIGHT, SYS_RENDERER_ID);
    glDeleteTextures(1, &SYS_RENDERER_ID);
}

void OpenGLTextTexture::SetData(void *data, uint32_t size)
{
    uint32_t bpp = 0;
    bpp = DATA_FORMAT == GL_RED ? 1 : 0;
    std::string dataErrStr = "DATA IS NOT SET TO ENTIRE TEXTURE: " + std::to_string(size) + " | " + std::to_string(WIDTH * HEIGHT * bpp) +
                             " == " + std::to_string(WIDTH * HEIGHT * bpp);
    MPE_CORE_ASSERT(size == WIDTH * HEIGHT * bpp, dataErrStr);

    glTextureSubImage2D(SYS_RENDERER_ID, 0, 0, 0, WIDTH, HEIGHT, DATA_FORMAT, GL_UNSIGNED_BYTE, data);
}

void OpenGLTextTexture::Bind(uint32_t slot) const
{
#ifdef MPE_PLATFORM_OSX
    glActiveTexture(GL_TEXTURE0 + slot);
#else
    glBindTextureUnit(slot, SYS_RENDERER_ID);
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