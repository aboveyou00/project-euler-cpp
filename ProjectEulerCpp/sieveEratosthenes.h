#pragma once

template <typename T>
using ActionPtr = void(*)(T);

template <typename T>
using PredicatePtr = bool(*)(T);

template <typename T = uint64_t>
class sieveEratosthenes
{
public:
    sieveEratosthenes()
    {
        emptyCache();
    }
    ~sieveEratosthenes()
    {
    }

    void generate(T upTo, ActionPtr<T> handler)
    {
        return generate([handler, upTo](uint64_t val)
        {
            handler(val);
            return val < upTo;
        });
    }

    template <typename TPredicate = PredicatePtr>
    void generate(TPredicate handler)
    {
        for (auto it = m_primes.begin(); it != m_primes.end(); it++)
        {
            if (!handler(*it))
            {
                return;
            }
        }

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

    void emptyCache()
    {
        m_primes.clear();
        m_primes.push_back(2);
        m_primes.push_back(3);
        m_primes.push_back(5);
        m_primes.push_back(7);
        m_primes.push_back(11);
        m_primes.push_back(13);
        m_primes.push_back(17);
        m_primes.push_back(19);
        m_primes.push_back(23);
        m_primes.push_back(29);
    }

private:
    std::vector<T> m_primes;
};
