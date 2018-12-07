#include "stdafx.h"
#include "euler.h"

class LargestGridProduct
{
private:
    LargestGridProduct(std::vector<uint32_t> &data, uint32_t width)
        : m_width(width), m_height(data.size() / width)
    {
        auto height = m_height;
        if (data.size() != width * height)
        {
            throw std::exception("Incorrect number of elements for grid of that size.");
        }

        m_data = new uint32_t[width * height];

        for (size_t w = 0; w < height; w++)
        {
            for (size_t q = 0; q < width; q++)
            {
                this->data(q, w) = data.at((w * width) + q);
            }
        }
    }
    ~LargestGridProduct()
    {
        delete m_data;
    }

public:
    static LargestGridProduct *parse(std::string str)
    {
        //Assumption: None of the parsed values will overflow a 32-bit unsigned integer

        size_t idx = 0;
        bool isCollectingNumber = false;
        uint32_t collected = 0;
        size_t requiredCols = 0;
        size_t currentRowCount = 0;
        std::vector<uint32_t> numbers;

        while (idx <= str.length())
        {
            auto chr = (idx == str.length()) ? '\n' : str.at(idx);
            idx++;

            if (chr >= '0' && chr <= '9')
            {
                isCollectingNumber = true;
                collected = (collected * 10) + (chr - '0');
            }
            else if (chr == ' ' || chr == ',' || chr == '\r' || chr == '\n')
            {
                if (isCollectingNumber)
                {
                    numbers.push_back(collected);
                    currentRowCount++;
                    collected = 0;
                    isCollectingNumber = false;
                }
                if ((chr == '\r' || chr == '\n') && currentRowCount > 0)
                {
                    if (requiredCols == 0)
                    {
                        requiredCols = currentRowCount;
                    }
                    else if (currentRowCount != requiredCols)
                    {
                        throw std::exception("Parsed line with an unexpected number of values");
                    }
                    currentRowCount = 0;
                }
            }
            else
            {
                throw std::exception("Unparsable character.");
            }
        }

        return new LargestGridProduct(numbers, requiredCols);
    }

    static inline uint32_t eval(std::string str, uint32_t adjacentCount = 4)
    {
        auto mp = parse(str);
        auto result = mp->solve(adjacentCount);
        delete mp;
        return result;
    }

    uint32_t solve(uint32_t adjacentCount = 4)
    {
        uint32_t maxProduct = 0;

        for (size_t q = 0; q < m_width; q++)
        {
            for (size_t w = 0; w < m_height; w++)
            {
                if (w <= m_height - adjacentCount)
                {
                    uint32_t product = 1;
                    for (size_t e = 0; e < adjacentCount; e++)
                    {
                        product *= data(q, w + e);
                    }
                    if (product > maxProduct)
                    {
                        maxProduct = product;
                    }
                }

                if (q <= m_width - adjacentCount)
                {
                    uint32_t product = 1;
                    for (size_t e = 0; e < adjacentCount; e++)
                    {
                        product *= data(q + e, w);
                    }
                    if (product > maxProduct)
                    {
                        maxProduct = product;
                    }
                }

                if (q <= m_width - adjacentCount && w <= m_height - adjacentCount)
                {
                    {
                        uint32_t product = 1;
                        for (size_t e = 0; e < adjacentCount; e++)
                        {
                            product *= data(q + e, w + e);
                        }
                        if (product > maxProduct)
                        {
                            maxProduct = product;
                        }
                    }

                    {
                        uint32_t product = 1;
                        for (size_t e = 0; e < adjacentCount; e++)
                        {
                            product *= data(q + adjacentCount - 1 - e, w + e);
                        }
                        if (product > maxProduct)
                        {
                            maxProduct = product;
                        }
                    }
                }
            }
        }

        return maxProduct;
    }

private:
    template <typename T>
    T &at(size_t x, size_t y, T *data)
    {
        if (x > m_width || y > m_height)
        {
            throw std::exception("Index out of bounds!");
        }
        return data[x + (y * m_width)];
    }
    template <typename T>
    const T &at(size_t x, size_t y, T *data) const
    {
        if (x > m_width || y > m_height)
        {
            throw std::exception("Index out of bounds!");
        }
        return data[x + (y * m_width)];
    }

    uint32_t &data(size_t x, size_t y)
    {
        return this->at(x, y, m_data);
    }
    uint32_t data(size_t x, size_t y) const
    {
        return this->at(x, y, m_data);
    }

    uint32_t m_width, m_height;
    uint32_t *m_data;
};

uint32_t euler<11>::value()
{
    auto input = readFile("euler11.txt");
    return LargestGridProduct::eval(input);
}
