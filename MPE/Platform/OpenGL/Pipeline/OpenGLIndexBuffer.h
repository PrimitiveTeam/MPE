#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Pipeline/IndexBuffer.h"

namespace MPE
{
class MPE_API OpenGLIndexBuffer : public IndexBuffer
{
  private:
    uint32_t SYS_Renderer_ID;
    uint32_t SYS_COUNT;

  public:
    OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
    virtual ~OpenGLIndexBuffer();

    // virtual void SetData() = 0;

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual uint32_t GetCount() const override { return SYS_COUNT; }
};
}