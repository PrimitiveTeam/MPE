#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Platform/OpenGLES/Textures/OpenGLESTexture.h"
#include "MPE/Renderer/Textures/Texture2D.h"

// #include <GLES3/gl3.h>
#include <glad/glad.h>

namespace MPE
{
class MPE_API OpenGLESTexture2D : public Texture2D
{
  public:
    OpenGLESTexture2D(uint32_t width, uint32_t height);
    OpenGLESTexture2D(const std::string& filepath);
    virtual ~OpenGLESTexture2D();

    virtual uint32_t GetWidth() const override { return WIDTH; };
    virtual uint32_t GetHeight() const override { return HEIGHT; };

    virtual void SetData(void* data, uint32_t size) override;

    virtual void Bind(uint32_t slot = 0) const override;

  private:
    std::string FILEPATH;
    uint32_t WIDTH;
    uint32_t HEIGHT;
    uint32_t SYS_RENDERER_ID;

    GLenum INTERNAL_FORMAT;
    GLenum DATA_FORMAT;
};
}