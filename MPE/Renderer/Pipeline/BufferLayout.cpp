#include "BufferLayout.h"
#include "MPE/MPEPCH.h"

namespace MPE
{
uint32_t MPE_API ShaderDataTypeSize(ShaderDataType type)
{
    switch (type)
    {
        case ShaderDataType::None:
            MPE_CORE_ASSERT(0, "SHADER TYPE: NONE");
        case ShaderDataType::Bool:
            return 1;
        case ShaderDataType::Int1:
            return 4;
        case ShaderDataType::Int2:
            return 4 * 2;
        case ShaderDataType::Int3:
            return 4 * 3;
        case ShaderDataType::Int4:
            return 4 * 4;
        case ShaderDataType::Vec1:
            return 4;
        case ShaderDataType::Vec2:
            return 4 * 2;
        case ShaderDataType::Vec3:
            return 4 * 3;
        case ShaderDataType::Vec4:
            return 4 * 4;
        case ShaderDataType::Mat3:
            return 4 * 3 * 3;
        case ShaderDataType::Mat4:
            return 4 * 4 * 4;
    }

    MPE_CORE_ASSERT(false, "UNKOWN SHADER DATA TYPE.");
    return 0;
}
}