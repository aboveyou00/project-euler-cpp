#pragma once

template <uint64_t num, uint64_t upTo>
struct sumOfMultiples
{
public:
    static const uint64_t value = num * (((upTo - 1) / num) * (((upTo - 1) / num) + 1)) / 2;
};
