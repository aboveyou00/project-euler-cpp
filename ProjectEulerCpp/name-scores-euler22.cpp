#include "stdafx.h"
#include "euler.h"
#include <algorithm>

uint32_t computeNameScoresSum(std::string input)
{
    std::vector<std::string> names;

    bool isInName = false;
    size_t nameBeginIdx = 0;
    for (size_t idx = 0; idx <= input.size(); idx++)
    {
        auto chr = (idx < input.size() ? input.at(idx) : ',');
        if (chr >= 'A' && chr <= 'Z')
        {
            if (!isInName)
            {
                nameBeginIdx = idx;
                isInName = true;
            }
        }
        else
        {
            if (isInName)
            {
                names.push_back(input.substr(nameBeginIdx, idx - nameBeginIdx));
                isInName = false;
            }
        }
    }

    std::sort(names.begin(), names.end());

    int32_t totalScore = 0;
    for (size_t idx = 0; idx < names.size(); idx++)
    {
        auto name = names[idx];
        
        uint32_t nameScore = 0;
        for (size_t q = 0; q < name.length(); q++)
        {
            nameScore += (name.at(q) - 'A') + 1;
        }
        nameScore *= idx + 1;

        totalScore += nameScore;
    }

    return totalScore;
}

uint32_t euler<22>::value()
{
    auto input = readFile("euler22.txt");
    return computeNameScoresSum(input);
}
