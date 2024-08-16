#pragma once

#include "MPE/Core/_CORE.h"
#include "Platform/OpenGLES/Textures/OpenGLESTexture.h"
#include "MPE/Renderer/Textures/TextTexture.h"

#include <GLES3/gl31.h>

namespace MPE
{
class MPE_API OpenGLESTextTexture : public TextTexture
{
  public:
    OpenGLESTextTexture(uint32_t width, uint32_t height);
    OpenGLESTextTexture(const std::string& filepath);
    virtual ~OpenGLESTextTexture();

    virtual uint32_t GetWidth() const override { return m_width; };
    virtual uint32_t GetHeight() const override { return m_height; };
    virtual uint32_t GetID() const override { return m_textTextureId; };

    virtual void SetData(void* data, uint32_t size) override;

    virtual void Bind(uint32_t slot = 0) const override;
    virtual void Unbind(uint32_t slot = 0) const override;

  private:
    std::string m_filepath;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_textTextureId;

    GLenum m_internalFormat;
    GLenum m_dataFormat;
};
}