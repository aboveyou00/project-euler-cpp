#pragma once

#include "fib.h"
#include "sum-squares-euler6.h"

template <std::uint32_t problemIdx>
struct euler
{
};

template <>
struct euler<2>
{
public:
    static const std::uint64_t value = sumOfEvenFibUpTo<indexOfLastFibBelow<4000000>::value>::value;
};

template <>
struct euler<6>
{
private:
    static const std::uint32_t upTo = 100;
    static const std::uint64_t sumSq = sumSquares<upTo>::value;
    static const std::uint64_t sqSum = squareSum<upTo>::value;
public:
    static const std::uint64_t value = sqSum - sumSq;
};

template <>
struct euler<14>
{
public:
    static std::uint32_t value();
};

template <>
struct euler<18>
{
public:
    static std::uint64_t value();
};

template <>
struct euler<67>
{
public:
    static std::uint64_t value();
};

template <>
struct euler<81>
{
public:
    static std::uint64_t value();
};
