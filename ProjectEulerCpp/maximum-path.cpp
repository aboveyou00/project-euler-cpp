#include "stdafx.h"
#include "maximum-path.h"
#include "euler.h"

#include <sstream>
#include <exception>

MaximumPath::MaximumPath(std::vector<std::vector<uint64_t>*> *data)
    : m_data(data)
{
}
MaximumPath::~MaximumPath()
{
    for (size_t q = 0; q < m_data->size(); q++)
    {
        delete m_data->at(q);
    }
    delete m_data;
    m_data = nullptr;
}

MaximumPath *MaximumPath::parse(std::string str)
{
    //Assumption: None of the parsed values will be 0
    //Assumption: None of the parsed values will overflow a 32-bit unsigned integer

    size_t idx = 0;
    uint64_t collected = 0;
    size_t requiredCols = 1;
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
        else if (chr == ' ' || chr == '\r' || chr == '\n')
        {
            if (collected != 0)
            {
                currentRow->push_back(collected);
                collected = 0;
            }
            if (chr == '\n' && currentRow->size() > 0)
            {
                if (currentRow->size() != requiredCols)
                {
                    throw std::exception("Parsed line with an unexpected number of values");
                }
                rows->push_back(currentRow);
                requiredCols++;
                currentRow = new std::vector<uint64_t>();
            }
        }
        else
        {
            throw std::exception("Unparsable character.");
        }
    }

    delete currentRow;
    return new MaximumPath(rows);
}

void MaximumPath::reduce()
{
    for (size_t w = m_data->size() - 1; w > 0; w--)
    {
        auto &row = m_data->at(w - 1);
        auto &below = m_data->at(w);
        for (size_t q = 0; q < row->size(); q++)
        {
            row->at(q) += max(below->at(q), below->at(q + 1));
        }
    }
}

uint64_t MaximumPath::tip() const
{
    return m_data->at(0)->at(0);
}

uint64_t euler<18>::value()
{
    auto input = readFile("euler18.txt");
    return MaximumPath::eval(input);
}

uint64_t euler<67>::value()
{
    auto input = readFile("euler67.txt");
    return MaximumPath::eval(input);
}
