#pragma once

#include "MPE/Core/_CORE.h"

namespace MPE
{
class MPE_API IComponentPropertyEditor
{
  public:
    virtual ~IComponentPropertyEditor() = default;
    virtual void Draw() = 0;
    virtual bool IsModified() const = 0;
    virtual void ApplyChanges() = 0;
};
}