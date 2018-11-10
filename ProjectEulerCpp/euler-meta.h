#pragma once

#include "./fib.h"

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
