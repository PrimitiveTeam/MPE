#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Pipeline/VertexBuffer.h"
#include "MPE/Renderer/Pipeline/BufferLayout.h"

namespace MPE
{
class MPE_API OpenGLESVertexBuffer : public VertexBuffer
{
  public:
    OpenGLESVertexBuffer(float *vertices, uint32_t size);
    OpenGLESVertexBuffer(uint32_t size);
    virtual ~OpenGLESVertexBuffer();

    // virtual void SetData() = 0;

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual const BufferLayout &GetLayout() const override { return SYS_LAYOUT; };
    virtual void SetLayout(const BufferLayout &layout) override { SYS_LAYOUT = layout; };

    virtual uint32_t GetSize() const override { return m_Size; }

    virtual void SetData(const void *data, uint32_t size) override;

  private:
    uint32_t SYS_Renderer_ID;
    BufferLayout SYS_LAYOUT;
    uint32_t m_Size;
};
}