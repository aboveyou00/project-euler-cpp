#pragma once

#include "fib.h"
#include "sum-of-multiples-euler1.h"
#include "sum-squares-euler6.h"
#include "pythag-triplet-product-euler9.h"
#include "lattice-paths-euler15.h"

template <std::uint32_t problemIdx>
struct euler
{
};

template <>
struct euler<1>
{
public:
    static const uint64_t value = sumOfMultiples<3, 1000>::value + sumOfMultiples<5, 1000>::value - sumOfMultiples<15, 1000>::value;
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
struct euler<7>
{
public:
    static uint64_t value();
};

template <>
struct euler<8>
{
public:
    static uint64_t value();
};

template <>
struct euler<9>
{
public:
    static const uint64_t value = pythagTripletProduct(1000);
};

template <>
struct euler<10>
{
public:
    static uint64_t value();
};

template <>
struct euler<11>
{
public:
    static uint32_t value();
};

template <>
struct euler<12>
{
public:
    static uint64_t value();
};

template <>
struct euler<14>
{
public:
    static uint32_t value();
};

template <>
struct euler<15>
{
public:
    static const uint64_t value = latticePaths<20, 20>::value;
};

template <>
struct euler<17>
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
struct euler<22>
{
public:
    static uint32_t value();
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
