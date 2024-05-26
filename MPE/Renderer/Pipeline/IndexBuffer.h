#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"

namespace MPE
{
class MPE_API IndexBuffer
{
  private:
  public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual uint32_t GetCount() const = 0;

    static REF<IndexBuffer> Create(uint32_t *indices, uint32_t size);
};
}