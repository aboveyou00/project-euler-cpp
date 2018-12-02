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
    static const uint64_t value = sumOfEvenFibUpTo<indexOfLastFibBelow<4000000>::value>::value;
};

template <>
struct euler<3>
{
public:
    static const uint64_t value = largestPrimeFactor(600851475143);
};

template <>
struct euler<4>
{
public:
    static uint32_t value();
};

template <>
struct euler<5>
{
public:
    static const uint64_t value = smallestMultiple<uint64_t>(20);
};

template <>
struct euler<6>
{
private:
    static const uint32_t upTo = 100;
    static const uint64_t sumSq = sumSquares<upTo>::value;
    static const uint64_t sqSum = squareSum<upTo>::value;
public:
    static const uint64_t value = sqSum - sumSq;
};

template <>
struct euler<14>
{
public:
    static uint32_t value();
};

template <>
struct euler<18>
{
public:
    static uint64_t value();
};

template <>
struct euler<67>
{
public:
    static uint64_t value();
};

template <>
struct euler<81>
{
public:
    static uint64_t value();
};

template <>
struct euler<82>
{
public:
    static uint64_t value();
};

template <>
struct euler<83>
{
public:
    static uint64_t value();
};
