#pragma once

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
    static const std::uint64_t value = (upTo * (upTo + 1)) / 2;
};

template <>
struct sum<0>
{
    static const std::uint64_t value = 0;
};

template <std::uint32_t upTo>
struct squareSum
{
private:
    static const std::uint64_t sum = sum<upTo>::value;
public:
    static const std::uint64_t value = sum * sum;
};

template <>
struct squareSum<0>
{
public:
    static const std::uint64_t value = 0;
};
