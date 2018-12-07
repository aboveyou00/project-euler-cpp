#include "stdafx.h"
#include "euler.h"

uint32_t divisorCount(uint64_t num)
{
    if (num == 1)
    {
        return 1;
    }

    auto upTo = (uint64_t)floor(sqrt(num));
    uint32_t count = 2;
    if (upTo * upTo == num)
    {
        upTo--;
        count++;
    }

    for (size_t q = 2; q <= upTo; q++)
    {
        if (num % q == 0)
        {
            count += 2;
        }
    }
    return count;
}

uint64_t firstTriangleNumberWithMinimumDivisorCount(uint32_t minDivisorCount)
{
    uint64_t triangleNumber = 0;
    for (uint64_t triIdx = 1; ; triIdx++)
    {
        triangleNumber += triIdx;
        if (triangleNumber < 250 * 250)
        {
            continue;
        }

        auto count = divisorCount(triangleNumber);
        if (count >= minDivisorCount)
        {
            return triangleNumber;
        }
    }
}

uint64_t euler<12>::value()
{
    return firstTriangleNumberWithMinimumDivisorCount(501);
}
