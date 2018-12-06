#include "stdafx.h"
#include "euler.h"
#include "sieveEratosthenes.h"

uint64_t sumPrimes(uint64_t upTo)
{
    sieveEratosthenes<> sieve(upTo + (upTo / 4));

    uint64_t sum = 0;
    sieve.generate(upTo, [&sum](uint64_t prime)
    {
        sum += prime;
    });

    return sum;
}

uint64_t euler<10>::value()
{
    return sumPrimes(2000000);
}
