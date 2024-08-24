#pragma once

#include "MPE/Core/_CORE.h"

namespace MPE
{
enum class MPE_API Properties : uint8_t
{
    None = 0,
    Tag = 1 << 0,
    Transform = 1 << 1,
    Hierarchy = 1 << 2
};

inline Properties operator|(Properties lhs, Properties rhs)
{
    return static_cast<Properties>(static_cast<std::underlying_type<Properties>::type>(lhs) | static_cast<std::underlying_type<Properties>::type>(rhs));
}

inline Properties& operator|=(Properties& lhs, Properties rhs)
{
    lhs = lhs | rhs;
    return lhs;
}

inline Properties operator&(Properties lhs, Properties rhs)
{
    return static_cast<Properties>(static_cast<std::underlying_type<Properties>::type>(lhs) & static_cast<std::underlying_type<Properties>::type>(rhs));
}

inline Properties& operator&=(Properties& lhs, Properties rhs)
{
    lhs = lhs & rhs;
    return lhs;
}

inline Properties operator~(Properties p)
{
    return static_cast<Properties>(~static_cast<std::underlying_type<Properties>::type>(p));
}

}