#include "stdafx.h"
#include "euler.h"

class MinPathSumThreeWays
{
private:
    MinPathSumThreeWays(std::vector<std::vector<uint64_t>*> *data)
    {
        auto width = data->at(0)->size();
        auto height = data->size();

        m_width = width;
        m_height = height;

        m_orig = new uint64_t[width * height];
        m_data = new uint64_t[width * height];

        for (size_t w = 0; w < height; w++)
        {
            auto row = data->at(w);
            for (size_t q = 0; q < height; q++)
            {
                this->orig(q, w) = row->at(q);
                this->data(q, w) = 0;
            }
        }
    }
    ~MinPathSumThreeWays()
    {
        delete[] m_orig;
        delete[] m_data;
    }

public:
    static MinPathSumThreeWays *parse(std::string str)
    {
        //Assumption: None of the parsed values will be 0
        //Assumption: None of the parsed values will overflow a 32-bit unsigned integer

        size_t idx = 0;
        uint64_t collected = 0;
        size_t requiredCols = 0;
        auto rows = new std::vector<std::vector<uint64_t>*>();
        auto currentRow = new std::vector<uint64_t>();

        while (idx <= str.length())
        {
            auto chr = (idx == str.length()) ? '\n' : str.at(idx);
            idx++;

            if (chr >= '0' && chr <= '9')
            {
                collected = (collected * 10) + (chr - '0');
            }
            else if (chr == ' ' || chr == ',' || chr == '\r' || chr == '\n')
            {
                if (collected != 0)
                {
                    currentRow->push_back(collected);
                    collected = 0;
                }
                if ((chr == '\r' || chr == '\n') && currentRow->size() > 0)
                {
                    if (requiredCols == 0)
                    {
                        requiredCols = currentRow->size();
                    }
                    else if (currentRow->size() != requiredCols)
                    {
                        throw std::exception("Parsed line with an unexpected number of values");
                    }
                    rows->push_back(currentRow);
                    currentRow = new std::vector<uint64_t>();
                }
            }
            else
            {
                throw std::exception("Unparsable character.");
            }
        }

        delete currentRow;
        return new MinPathSumThreeWays(rows);
    }

    static inline uint64_t eval(std::string str)
    {
        auto mp = parse(str);
        mp->reduce();
        auto result = mp->answer();
        delete mp;
        return result;
    }

    void reduce()
    {
        for (size_t w = 0; w < m_height; w++)
        {
            data(m_width - 1, w) = orig(m_width - 1, w);
        }

        for (size_t q = m_width - 1; q > 0; )
        {
            q--;

            data(q, 0) = orig(q, 0) + data(q + 1, 0);
            for (size_t w = 1; w < m_height; w++)
            {
                data(q, w) = orig(q, w) + min(data(q + 1, w), data(q, w - 1));
            }

            for (size_t w = m_height - 1; w > 0; )
            {
                w--;

                data(q, w) = min(data(q, w), orig(q, w) + data(q, w + 1));
            }
        }
    }
    uint64_t answer() const
    {
        uint64_t min = std::numeric_limits<uint64_t>::max();
        for (size_t w = 0; w < m_height; w++)
        {
            auto val = data(0, w);
            if (val < min)
            {
                min = val;
            }
        }
        return min;
    }

private:
    uint64_t &at(size_t x, size_t y, uint64_t *data)
    {
        return data[x + (y * m_width)];
    }
    uint64_t at(size_t x, size_t y, uint64_t *data) const
    {
        return data[x + (y * m_width)];
    }

    uint64_t &orig(size_t x, size_t y)
    {
        return this->at(x, y, m_orig);
    }
    uint64_t orig(size_t x, size_t y) const
    {
        return this->at(x, y, m_orig);
    }
    uint64_t &data(size_t x, size_t y)
    {
        return this->at(x, y, m_data);
    }
    uint64_t data(size_t x, size_t y) const
    {
        return this->at(x, y, m_data);
    }

    uint32_t m_width, m_height;
    uint64_t *m_orig;
    uint64_t *m_data;
};

std::uint64_t euler<82>::value()
{
    //Should be 994
    //    auto testVal = MinPathSumThreeWays::eval(R"HEREDOC(
    //131,673,234,103,18
    //201,96, 342,965,150
    //630,803,746,422,111
    //537,699,497,121,956
    //805,732,524,37, 331
    //)HEREDOC");
    //    return testVal;

    auto input = readFile("path-sum-matrix.txt");
    return MinPathSumThreeWays::eval(input);
}
