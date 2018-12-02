#include "stdafx.h"
#include "euler.h"

class MinPathSumTwoWays
{
private:
    MinPathSumTwoWays(std::vector<std::vector<uint64_t>*> *data)
        : m_data(data)
    {
    }
    ~MinPathSumTwoWays()
    {
        for (size_t q = 0; q < m_data->size(); q++)
        {
            delete m_data->at(q);
        }
        delete m_data;
        m_data = nullptr;
    }

public:
    static MinPathSumTwoWays *parse(std::string str)
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
        return new MinPathSumTwoWays(rows);
    }

    static inline uint64_t eval(std::string str)
    {
        auto mp = parse(str);
        mp->reduce();
        auto result = mp->tip();
        delete mp;
        return result;
    }

    void reduce()
    {
        auto width = m_data->at(0)->size();
        auto height = m_data->size();

        for (size_t w = height - 1; w > 0; w--)
        {
            auto &row = m_data->at(w - 1);
            auto &below = m_data->at(w);
            row->at(width - 1) += below->at(width - 1);
        }

        auto lastRow = m_data->at(height - 1);
        for (size_t q = width - 1; q > 0; q--)
        {
            lastRow->at(q - 1) += lastRow->at(q);
        }

        for (size_t w = height - 1; w > 0; w--)
        {
            auto &row = m_data->at(w - 1);
            auto &below = m_data->at(w);
            for (size_t q = width - 1; q > 0; q--)
            {
                row->at(q - 1) += min(below->at(q - 1), row->at(q));
            }
        }
    }
    uint64_t tip() const
    {
        return m_data->at(0)->at(0);
    }

private:
    std::vector<std::vector<uint64_t>*> *m_data;
};

std::uint64_t euler<81>::value()
{
    //Should be 2427
//    auto testVal = MinPathSumTwoWays::eval(R"HEREDOC(
//131,673,234,103,18
//201,96, 342,965,150
//630,803,746,422,111
//537,699,497,121,956
//805,732,524,37, 331
//)HEREDOC");
//    return testVal;

    auto input = readFile("path-sum-matrix.txt");
    return MinPathSumTwoWays::eval(input);
}
