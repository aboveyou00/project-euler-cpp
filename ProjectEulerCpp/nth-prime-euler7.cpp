#include "stdafx.h"
#include "euler.h"
#include "sieveEratosthenes.h"

uint64_t nthPrime(uint64_t n)
{
    sieveEratosthenes<> sieve;

    auto primeCount = 0;
    uint64_t lastPrime;
    sieve.generate([n, &primeCount, &lastPrime](uint64_t prime)
    {
        lastPrime = prime;
        return (++primeCount != n);
    });

    return lastPrime;
}

uint64_t euler<7>::value()
{
    return nthPrime(10001);
}
