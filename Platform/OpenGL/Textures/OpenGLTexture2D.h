#pragma once

#include "MPE/Core/_CORE.h"
#include "Platform/OpenGL/Textures/OpenGLTexture.h"
#include "MPE/Renderer/Textures/Texture2D.h"

#include <glad/glad.h>

namespace MPE
{
class MPE_API OpenGLTexture2D : public Texture2D
{
  public:
    OpenGLTexture2D(uint32_t width, uint32_t height);
    OpenGLTexture2D(const std::string& filepath);
    virtual ~OpenGLTexture2D();

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