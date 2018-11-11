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

template <typename T>
inline constexpr T largestPrimeFactor(T num)
{
    T nextPrime = 2;
    while (true)
    {
        while (num % nextPrime == 0)
        {
            if (num == nextPrime) return nextPrime;
            num /= nextPrime;
        }
        nextPrime++;
    }
}

template <typename T>
inline constexpr T smallestMultiple(T upTo)
{
    T current = 1;
    for (T q = 1; q <= upTo; q++)
    {
        for (T w = 1; w <= q; w++)
        {
            T val = current * w;
            if (val % q == 0)
            {
                current = val;
                break;
            }
        }
    }
    return current;
}
