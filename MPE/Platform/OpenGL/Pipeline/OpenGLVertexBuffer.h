#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Pipeline/VertexBuffer.h"
#include "MPE/Renderer/Pipeline/BufferLayout.h"

namespace MPE
{
class MPE_API OpenGLVertexBuffer : public VertexBuffer
{
  private:
    uint32_t SYS_Renderer_ID;
    BufferLayout SYS_LAYOUT;

  public:
    OpenGLVertexBuffer(float *vertices, uint32_t size);
    virtual ~OpenGLVertexBuffer();

    // virtual void SetData() = 0;

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual const BufferLayout &GetLayout() const override { return SYS_LAYOUT; };
    virtual void SetLayout(const BufferLayout &layout) override { SYS_LAYOUT = layout; };
};
}