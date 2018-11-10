#pragma once

#include <cstdint>

template <std::uint32_t upTo>
struct sumSquares
{
public:
    static const std::uint64_t value = (upTo * upTo) + sumSquares<upTo - 1>::value;
};

template <>
struct sumSquares<0>
{
public:
    static const std::uint64_t value = 0;
};

template <std::uint32_t upTo>
struct sum
{
    static const std::uint64_t value = sum<upTo - 1>::value + upTo;
};

template <>
struct sum<0>
{
    static const std::uint64_t value = 0;
};

template <std::uint32_t upTo>
struct squareSum
{
public:
    static const std::uint64_t value = sum<upTo>::value * sum<upTo>::value;
};

template <>
struct squareSum<0>
{
public:
    static const std::uint64_t value = 0;
};
