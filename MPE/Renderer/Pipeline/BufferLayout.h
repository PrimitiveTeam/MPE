#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Log/GlobalLog.h"

namespace MPE
{
enum class MPE_API ShaderDataType : uint8_t
{
    None = 0,
    // BOOL
    Bool,
    // INTS
    Int1,
    Int2,
    Int3,
    Int4,
    // FLOATS
    Vec1,
    Vec2,
    Vec3,
    Vec4,
    // MATRICES
    Mat3,
    Mat4,
};

MPE_API uint32_t ShaderDataTypeSize(ShaderDataType type);

struct MPE_API BufferElement
{
    std::string title;
    ShaderDataType type;
    uint32_t size;
    uint32_t offset;
    bool normalized;

    BufferElement() {}

    BufferElement(ShaderDataType type, const std::string &title, bool normalized = false)
        : title(title), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
    {
    }

    uint32_t GetComponentCount() const
    {
        switch (type)
        {
            case ShaderDataType::None:
                MPE_CORE_ASSERT(0, "SHADER TYPE: NONE");
            case ShaderDataType::Bool:
                return 1;
            case ShaderDataType::Int1:
                return 1;
            case ShaderDataType::Int2:
                return 2;
            case ShaderDataType::Int3:
                return 3;
            case ShaderDataType::Int4:
                return 4;
            case ShaderDataType::Vec1:
                return 1;
            case ShaderDataType::Vec2:
                return 2;
            case ShaderDataType::Vec3:
                return 3;
            case ShaderDataType::Vec4:
                return 4;
            case ShaderDataType::Mat3:
                return 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4;
        }
        MPE_CORE_ASSERT(false, "UNKOWN SHADER DATA TYPE.");
        return 0;
    }
};

class MPE_API BufferLayout
{
  public:
    BufferLayout() {}

    BufferLayout(const std::initializer_list<BufferElement> &elements) : m_bufferElements(elements) { CalculateOffsetAndStride(); }

    inline uint32_t GetStride() const { return m_bufferStride; }
    inline const std::vector<BufferElement> &GetElements() const { return m_bufferElements; }

    std::vector<BufferElement>::iterator begin() { return m_bufferElements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_bufferElements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_bufferElements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_bufferElements.end(); }

  private:
    void CalculateOffsetAndStride()
    {
        uint32_t offset = 0;
        m_bufferStride = 0;
        for (auto &element : m_bufferElements)
        {
            element.offset = offset;
            offset += element.size;
            m_bufferStride += element.size;
        }
    }

  private:
    std::vector<BufferElement> m_bufferElements;
    uint32_t m_bufferStride = 0;
};
}