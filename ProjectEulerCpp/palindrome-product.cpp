#include "stdafx.h"
#include "euler.h"

#include <sstream>

bool isPalindrome(uint32_t number)
{
    std::stringstream buffer;
    buffer << number;
    std::string numberStr = buffer.str();
    for (size_t idx = 0; idx <= numberStr.size() / 2; idx++)
    {
        if (numberStr[idx] != numberStr[numberStr.size() - (1 + idx)])
        {
            return false;
        }
    }
    return true;
}

bool isPalindrome(uint32_t number, uint32_t *cache)
{
    if (cache[number] != -1)
    {
        return cache[number] == 1;
    }

    auto result = isPalindrome(number);
    cache[number] = result ? 1 : 0;
    return result;
}

uint32_t euler<4>::value()
{
    const uint32_t bufferSize = 999 * 999;
    uint32_t *buffer = new uint32_t[bufferSize];
    std::fill_n(buffer, bufferSize, -1);

    uint32_t largestPalindrome = 0;

    for (uint32_t q = 100; q < 1000; q++)
    {
        for (uint32_t w = q; w < 1000; w++)
        {
            uint32_t val = q * w;
            if (val > largestPalindrome && isPalindrome(val, buffer))
            {
                largestPalindrome = val;
            }
        }
    }

    delete buffer;
    return largestPalindrome;
}
