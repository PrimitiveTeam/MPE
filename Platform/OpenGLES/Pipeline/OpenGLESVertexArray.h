#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"

namespace MPE
{
class MPE_API OpenGLESVertexArray : public VertexArray
{
  public:
    OpenGLESVertexArray();
    virtual ~OpenGLESVertexArray();

    // virtual void SetData() = 0;

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(const REF<VertexBuffer> &vertexBuffer) override;
    virtual void SetIndexBuffer(const REF<IndexBuffer> &indexBuffer) override;

    virtual const std::vector<REF<VertexBuffer>> &GetVertexBuffers() const override { return SYS_VERTEXBUFFERS; }
    virtual const REF<IndexBuffer> &GetIndexBuffer() const override { return SYS_INDEXBUFFER; }
    // virtual const std::vector<std::shared_ptr<IndexBuffer>>& GetIndexBuffers() const override { return SYS_INDEXBUFFERS; }

  private:
    uint32_t SYS_Renderer_ID;
    std::vector<REF<VertexBuffer>> SYS_VERTEXBUFFERS;

    REF<IndexBuffer> SYS_INDEXBUFFER;
    // std::vector<std::shared_ptr<IndexBuffer>> SYS_INDEXBUFFERS;
};
}