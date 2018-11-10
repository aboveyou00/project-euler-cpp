#pragma once

#include <cstdint>

template <std::uint32_t idx>
struct fib
{
public:
    static const std::uint64_t value = fib<idx - 2>::value + fib<idx - 1>::value;
};

template <>
struct fib<0>
{
public:
    static const std::uint64_t value = 1;
};

template <>
struct fib<1>
{
public:
    static const std::uint64_t value = 2;
};

template <std::uint64_t upperBound, std::uint32_t checkIdx = 64>
struct indexOfLastFibBelow
{
public:
    static const std::uint32_t value = fib<checkIdx>::value > upperBound ? indexOfLastFibBelow<upperBound, checkIdx - 1>::value : checkIdx;
};

template <std::uint64_t upperBound>
struct indexOfLastFibBelow<upperBound, 0>
{
public:
    static const std::uint32_t value = 0;
};

template <std::uint32_t idx>
struct sumOfEvenFibUpTo
{
public:
    static const std::uint64_t value = (fib<idx>::value % 2 == 0 ? fib<idx>::value : 0) + sumOfEvenFibUpTo<idx - 1>::value;
};

template <>
struct sumOfEvenFibUpTo<0>
{
public:
    static const std::uint64_t value = fib<0>::value % 2 == 0 ? fib<0>::value : 0;
};
