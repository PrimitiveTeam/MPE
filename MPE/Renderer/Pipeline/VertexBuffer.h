#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Pipeline/BufferLayout.h"

namespace MPE
{
class MPE_API VertexBuffer
{
  private:
  public:
    virtual ~VertexBuffer() = default;

    // virtual void SetData() = 0;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual const BufferLayout &GetLayout() const = 0;
    virtual void SetLayout(const BufferLayout &layout) = 0;

    static REF<VertexBuffer> Create(float *vertices, uint32_t size);
};
}