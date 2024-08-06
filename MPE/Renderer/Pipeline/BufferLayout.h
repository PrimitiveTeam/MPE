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
    std::string Title;
    ShaderDataType Type;
    uint32_t Size;
    uint32_t Offset;
    bool Normalized;

    BufferElement() {}

    BufferElement(ShaderDataType type, const std::string &title, bool normalized = false)
        : Title(title), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
    {
    }

    uint32_t GetComponentCount() const
    {
        switch (Type)
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

    BufferLayout(const std::initializer_list<BufferElement> &elements) : SYS_ELEMENTS(elements) { CalculateOffsetAndStride(); }

    inline uint32_t GetStride() const { return SYS_STRIDE; }
    inline const std::vector<BufferElement> &GetElements() const { return SYS_ELEMENTS; }

    std::vector<BufferElement>::iterator begin() { return SYS_ELEMENTS.begin(); }
    std::vector<BufferElement>::iterator end() { return SYS_ELEMENTS.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return SYS_ELEMENTS.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return SYS_ELEMENTS.end(); }

  private:
    void CalculateOffsetAndStride()
    {
        uint32_t offset = 0;
        SYS_STRIDE = 0;
        for (auto &element : SYS_ELEMENTS)
        {
            element.Offset = offset;
            offset += element.Size;
            SYS_STRIDE += element.Size;
        }
    }

  private:
    std::vector<BufferElement> SYS_ELEMENTS;
    uint32_t SYS_STRIDE = 0;
};
}