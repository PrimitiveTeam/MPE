#pragma once

#include "MPE/Core/_CORE.h"

namespace MPE
{
namespace ECS
{
// Whenever metadata is marked as dirty, the mesh needs to be regenerated
class MPE_EDITOR_API MeshMetadata
{
  public:
    // Check if the mesh needs regeneration
    virtual bool IsDirty() const final { return m_dirty; }
    // Clear the dirty flag after regeneration
    virtual void ClearAllDirty() = 0;

    virtual ~MeshMetadata() = default;

  protected:
    bool m_dirty = false;
};
}
}