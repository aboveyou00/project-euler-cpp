#pragma once

template <typename T>
inline constexpr T min(T lhs, T rhs)
{
    return lhs < rhs ? lhs : rhs;
}

template <typename T>
inline constexpr T max(T lhs, T rhs)
{
    return lhs > rhs ? lhs : rhs;
}
