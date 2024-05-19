#pragma once

#include "MPE/Core/_CORE.h"

namespace MPE
{
class MPE_API Texture
{
  private:
  public:
    virtual ~Texture() = default;

    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;

    virtual void SetData(void* data, uint32_t size) = 0;

    virtual void Bind(uint32_t slot = 0) const = 0;
};
}