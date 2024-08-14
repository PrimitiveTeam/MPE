#include "OpenGLESTextTexture.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/Vendor/STB/stb_image.h"
#include "Platform/OpenGLES/Utilities/OpenGLESUtilities.h"

namespace MPE
{
OpenGLESTextTexture::OpenGLESTextTexture(uint32_t width, uint32_t height) : WIDTH(width), HEIGHT(height), SYS_RENDERER_ID(0)
{
    MPE_CORE_WARN("CREATING TEXTURE...");

    INTERNAL_FORMAT = GL_R8;
    DATA_FORMAT = GL_RED;

    glGenTextures(1, &SYS_RENDERER_ID);

    glCheckError();

    glBindTexture(GL_TEXTURE_2D, SYS_RENDERER_ID);

    glCheckError();

    // TODO: Investigate => potentially not necessary
    glTexImage2D(GL_TEXTURE_2D, 0, INTERNAL_FORMAT, WIDTH, HEIGHT, 0, DATA_FORMAT, GL_UNSIGNED_BYTE, nullptr);

    glCheckError();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glCheckError();

    MPE_CORE_ASSERT(SYS_RENDERER_ID, "TEXTURE NOT CREATED");
    MPE_CORE_INFO("TEXTURE CREATED: {0}x{1} | ID: {2}", WIDTH, HEIGHT, SYS_RENDERER_ID);
}

OpenGLESTextTexture::OpenGLESTextTexture(const std::string &filepath) : FILEPATH(filepath)
{
    MPE_ASSERT(false, "NOT IMPLEMENTED YET");
}

OpenGLESTextTexture::~OpenGLESTextTexture()
{
    MPE_CORE_WARN("DELETING TEXTURE: {0}x{1} | ID: {2}", WIDTH, HEIGHT, SYS_RENDERER_ID);
    glDeleteTextures(1, &SYS_RENDERER_ID);
}

void OpenGLESTextTexture::SetData(void *data, uint32_t size)
{
    uint32_t bpp = 0;
    bpp = DATA_FORMAT == GL_RED ? 1 : 0;
    std::string dataErrStr = "DATA IS NOT SET TO ENTIRE TEXTURE: " + std::to_string(size) + " | " + std::to_string(WIDTH * HEIGHT * bpp) +
                             " == " + std::to_string(WIDTH * HEIGHT * bpp);
    MPE_CORE_ASSERT(size == WIDTH * HEIGHT * bpp, dataErrStr);

    glBindTexture(GL_TEXTURE_2D, SYS_RENDERER_ID);

    glTexImage2D(GL_TEXTURE_2D, 0, INTERNAL_FORMAT, WIDTH, HEIGHT, 0, DATA_FORMAT, GL_UNSIGNED_BYTE, data);

    glCheckError();
}

void OpenGLESTextTexture::Bind(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, SYS_RENDERER_ID);
}

void OpenGLESTextTexture::Unbind(uint32_t slot) const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
}