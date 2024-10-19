#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/ECS/ECS.h"
#include "MeshMetadata.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
namespace ECS
{
class MPE_EDITOR_API GridMetadataComponent : public MeshMetadata
{
  public:
    GridMetadataComponent(float gridSize, float gridSpacing)
    {
        MPE_ASSERT(gridSize > 0, "Grid size must be greater than 0.");
        MPE_ASSERT(gridSpacing > 0, "Grid spacing must be greater than 0.");

        m_gridSize = gridSize;
        m_gridSpacing = gridSpacing;
    }

    float GetGridSize() const { return m_gridSize; }
    float GetGridSpacing() const { return m_gridSpacing; }

    bool IsGridSizeDirty() const { return m_gridSizeDirty; }
    bool IsGridSpacingDirty() const { return m_gridSpacingDirty; }

    void SetGridSize(float gridSize)
    {
        if (gridSize <= 0)
        {
            MPE_CORE_ERROR("Grid size must be greater than 0.");
            return;
        }
        if (gridSize == m_gridSize) return;

        m_gridSize = gridSize;
        m_gridSizeDirty = true;
        m_dirty = true;
    }

    void SetGridSpacing(float gridSpacing)
    {
        if (gridSpacing <= 0)
        {
            MPE_CORE_ERROR("Grid spacing must be greater than 0.");
            return;
        }
        if (gridSpacing == m_gridSpacing) return;

        m_gridSpacing = gridSpacing;
        m_gridSpacingDirty = true;
        m_dirty = true;
    }

    virtual void ClearAllDirty()
    {
        m_dirty = false;
        m_gridSizeDirty = false;
        m_gridSpacingDirty = false;
    }

  private:
    float m_gridSize;
    float m_gridSpacing;

    bool m_gridSizeDirty = false;
    bool m_gridSpacingDirty = false;
};
}
}