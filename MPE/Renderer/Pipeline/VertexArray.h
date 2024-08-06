#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Pipeline/IndexBuffer.h"
#include "MPE/Renderer/Pipeline/VertexBuffer.h"
#include "MPE/Renderer/Pipeline/BufferLayout.h"

namespace MPE
{
class MPE_API VertexArray
{
  public:
    virtual ~VertexArray() = default;

    // virtual void SetData() = 0;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const REF<VertexBuffer> &vertexBuffer) = 0;
    virtual void SetIndexBuffer(const REF<IndexBuffer> &indexBuffer) = 0;

    virtual const std::vector<REF<VertexBuffer>> &GetVertexBuffers() const = 0;
    virtual const REF<IndexBuffer> &GetIndexBuffer() const = 0;
    // virtual const std::vector<std::shared_ptr<IndexBuffer>>& GetIndexBuffers() const = 0;

    static REF<VertexArray> Create();
};
}