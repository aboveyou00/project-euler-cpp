#pragma once
#include <iostream>

template <typename T>
using ActionPtr = void(*)(T);

template <typename T>
using PredicatePtr = bool(*)(T);

template <typename T = uint64_t>
class sieveEratosthenes
{
public:
    sieveEratosthenes(T upTo = 100000)
    {
        generateInitial(upTo);
    }
    ~sieveEratosthenes()
    {
    }

    template <typename TAction = ActionPtr<T>>
    void generate(T upTo, TAction handler)
    {
        return generate([handler, upTo](uint64_t val)
        {
            if (val < upTo)
            {
                handler(val);
                return true;
            }

            return false;
        });
    }

    template <typename TPredicate = PredicatePtr<T>>
    void generate(TPredicate handler)
    {
        for (auto it = m_primes.begin(); it != m_primes.end(); it++)
        {
            if (!handler(*it))
            {
                return;
            }
        }

        std::cout << "WARNING: Reached end of sieve of eratosthenes buffer. Using less efficient algorithm to continue boundlessly." << std::endl;

        T counter = m_primes.at(m_primes.size() - 1) + 2;

        while (true)
        {
            auto realSqrt = sqrt(counter);
            auto upTo = (T)floor(realSqrt);
            if (realSqrt == upTo)
            {
                counter += 2;
                continue;
            }

            bool isPrime = true;
            for (auto it = m_primes.begin(); *it <= upTo; it++)
            {
                if (counter % *it == 0)
                {
                    isPrime = false;
                    break;
                }
            }

            if (isPrime)
            {
                m_primes.push_back(counter);
                if (!handler(counter))
                {
                    return;
                }
            }

            counter += 2;
        }
    }

private:
    std::vector<T> m_primes;

    void generateInitial(T upTo)
    {
        bool *isPrime = new bool[upTo];
        std::fill(isPrime, isPrime + upTo, true);
        isPrime[0] = false;
        isPrime[1] = false;

        auto maxToCheck = (T)floor(sqrt(upTo));

        for (T q = 2; q <= maxToCheck; q++)
        {
            if (!isPrime[q])
            {
                continue;
            }

            for (T val = q * 2; val < upTo; val += q)
            {
                isPrime[val] = false;
            }
        }

        for (T q = 2; q < upTo; q++)
        {
            if (!isPrime[q])
            {
                continue;
            }

            m_primes.push_back(q);
        }

        delete[] isPrime;
    }
};
