#include "stdafx.h"
#include "collatz.h"

#include "euler.h"

#include <iostream>

const bool DEBUG_LOG_COLLATZ = false;

class CollatzCacher
{
public:
    CollatzCacher(size_t primaryStoreSize)
        : m_primaryStoreCount(primaryStoreSize), m_primaryStore(new uint32_t[primaryStoreSize]), m_others()
    {
        std::fill_n(m_primaryStore, m_primaryStoreCount, 0);
        this->put(1, 1);
    }
    ~CollatzCacher()
    {
        delete m_primaryStore;
        m_primaryStore = nullptr;
    }

    uint32_t get(uint32_t pos)
    {
        if (pos < m_primaryStoreCount)
        {
            return m_primaryStore[pos];
        }

        auto cached = m_others.find(pos);
        if (cached != m_others.end())
        {
            return cached->second;
        }

        return 0;
    }
    void put(uint32_t pos, uint32_t val)
    {
        if (pos < m_primaryStoreCount)
        {
            m_primaryStore[pos] = val;
            return;
        }

        m_others[pos] = val;
    }

private:
    size_t m_primaryStoreCount;
    uint32_t *m_primaryStore;
    std::map<uint32_t, uint32_t> m_others;
};

uint32_t collatzLength(uint32_t start, CollatzCacher &cacher)
{
    auto cached = cacher.get(start);
    if (cached != 0)
    {
        return cached;
    }

    auto value = collatzLength(start % 2 == 0 ? start / 2 : (start * 3) + 1, cacher) + 1;
    cacher.put(start, value);
    return value;
}

uint32_t maxCollatzLength(std::uint32_t upTo)
{
    CollatzCacher cacher(upTo * 30);
    uint32_t maxLenPos = 0;
    uint32_t maxLen = 0;
    for (uint32_t q = 1; q < upTo; q++)
    {
        auto len = collatzLength(q, cacher);
        if (len > maxLen)
        {
            maxLen = len;
            maxLenPos = q;
            if (DEBUG_LOG_COLLATZ)
            {
                std::cout << "  ... " << q << " (" << maxLen << ")" << std::endl;
            }
        }
    }
    return maxLenPos;
}

std::uint32_t euler<14>::value()
{
    //837799
    return maxCollatzLength(1000000);
}
