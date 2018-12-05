#pragma once

template <unsigned int TCol, unsigned int TRow>
struct latticePaths
{
public:
    static const unsigned long long value = latticePaths<TCol - 1, TRow>::value + latticePaths<TCol, TRow - 1>::value;
};

template <unsigned int TCol>
struct latticePaths<TCol, 0>
{
public:
    static const unsigned long long value = 1;
};

template <unsigned int TRow>
struct latticePaths<0, TRow>
{
public:
    static const unsigned long long value = 1;
};

template <>
struct latticePaths<1, 1>
{
public:
    static const unsigned long long value = 2;
};
