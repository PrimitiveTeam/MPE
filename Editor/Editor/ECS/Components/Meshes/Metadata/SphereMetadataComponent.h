#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/ECS/ECS.h"
#include "MeshMetadata.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
namespace ECS
{
const unsigned char MINIMUM_SECTORS = 2;
const unsigned char MINIMUM_STACKS = 2;

class MPE_EDITOR_API SphereMetadataComponent : public MeshMetadata
{
  public:
    SphereMetadataComponent(float radius = 1.0f, uint32_t sectors = 36, uint32_t stacks = 18, bool smooth = true, unsigned char upAxis = 3)
    {
        MPE_ASSERT(radius > 0, "Sphere radius must be greater than 0");
        this->m_radius = radius;

        MPE_ASSERT(sectors >= MINIMUM_SECTORS, "Sphere sectors must be greater than or equal to 2");
        this->m_sectors = sectors;

        MPE_ASSERT(stacks >= MINIMUM_STACKS, "Sphere stacks must be greater than or equal to 2");
        this->m_stacks = stacks;

        this->m_smooth = smooth;

        MPE_ASSERT(upAxis >= 1 && upAxis <= 3, "Sphere up axis must be between 1 and 3");
        this->m_upAxis = upAxis;
        this->m_previousUpAxis = upAxis;
    }

    float GetRadius() const { return m_radius; }
    uint32_t GetSectors() const { return m_sectors; }
    uint32_t GetStacks() const { return m_stacks; }
    bool GetSmooth() const { return m_smooth; }
    unsigned char GetUpAxis() const { return m_upAxis; }
    unsigned char GetPreviousUpAxis() const { return m_previousUpAxis; }
    bool IsBaseDirty() const { return m_baseDirty; }
    bool IsUpAxisDirty() const { return m_upAxisDirty; }
    bool IsSmoothDirty() const { return m_smoothDirty; }
    bool IsReverseNormals() const { return m_reverseNormals; }

    void SetRadius(float radius)
    {
        if (m_radius != radius)
        {
            m_radius = radius;
            m_baseDirty = true;
            m_dirty = true;
        }
    }

    void SetSectors(uint32_t sectors)
    {
        if (m_sectors != sectors)
        {
            m_sectors = sectors;
            m_baseDirty = true;
            m_dirty = true;
        }
    }

    void SetStacks(uint32_t stacks)
    {
        if (m_stacks != stacks)
        {
            m_stacks = stacks;
            m_baseDirty = true;
            m_dirty = true;
        }
    }

    void SetSmooth(bool smooth)
    {
        if (m_smooth != smooth)
        {
            m_smooth = smooth;
            m_dirty = true;
            m_smoothDirty = true;
        }
    }

    void SetUpAxis(unsigned char upAxis)
    {
        if (m_upAxis != upAxis)
        {
            m_upAxis = upAxis;
            m_dirty = true;
            m_upAxisDirty = true;
        }
    }

    void ResetPreviousUpAxis() { m_previousUpAxis = m_upAxis; }

    virtual void ClearAllDirty()
    {
        m_dirty = false;
        m_baseDirty = false;
        m_smoothDirty = false;
        m_upAxisDirty = false;
    }

    void ReverseNormals()
    {
        m_dirty = true;
        m_reverseNormals = true;
    }

  private:
    float m_radius;
    uint32_t m_sectors;
    uint32_t m_stacks;
    bool m_smooth;
    unsigned char m_upAxis;
    unsigned char m_previousUpAxis;
    bool m_baseDirty = false;
    bool m_upAxisDirty = false;
    bool m_smoothDirty = false;
    bool m_reverseNormals = false;
};
}
}