#include "stdafx.h"
#include "euler.h"

uint64_t largestSeriesProduct(std::string input, size_t digitCount)
{
    auto numbers = new uint64_t[digitCount];
    for (size_t q = 0; q < digitCount; q++)
    {
        numbers[q] = 0;
    }

    size_t numbersIdx = 0;
    size_t inputIdx = 0;

    uint64_t currentLargest = 0;

    while (inputIdx < input.length())
    {
        auto chr = input.at(inputIdx++);
        if (chr < '0' || chr > '9')
        {
            continue;
        }
        auto digit = chr - '0';

        for (size_t q = 0; q < digitCount; q++)
        {
            if (q == numbersIdx)
            {
                numbers[q] = digit;
            }
            else if (numbers[q] != 0)
            {
                numbers[q] *= digit;
            }
        }

        numbersIdx = (numbersIdx + 1) % digitCount;
        if (numbers[numbersIdx] > currentLargest)
        {
            currentLargest = numbers[numbersIdx];
        }
        numbers[numbersIdx] = 0;
    }

    delete[] numbers;
    return currentLargest;
}

uint64_t euler<8>::value()
{
    auto input = readFile("euler8.txt");
    return largestSeriesProduct(input, 13);
}
