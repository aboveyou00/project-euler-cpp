#include "stdafx.h"
#include "euler.h"

uint32_t numberLetterCount(uint32_t number)
{
    if (number >= 1000000)
    {
        throw std::exception("Not implemented");
    }
    else if (number >= 1000)
    {
        auto thousands = number / 1000;
        auto hundreds = number - (thousands * 1000);
        return numberLetterCount(thousands) + "thousand"s.length() + (hundreds == 0 ? 0 : numberLetterCount(hundreds));
    }
    else if (number >= 100)
    {
        auto hundreds = number / 100;
        auto tens = number - (hundreds * 100);
        return numberLetterCount(hundreds) + "hundred"s.length() + (tens == 0 ? 0 : "and"s.length() + numberLetterCount(tens));
    }
    else if (number > 20 && number < 100 && number % 10 != 0)
    {
        auto tens = (number / 10) * 10;
        auto ones = number - tens;
        return numberLetterCount(tens) + numberLetterCount(ones);
    }
    switch (number)
    {
    case 0:
        return "zero"s.length();
    case 1:
        return "one"s.length();
    case 2:
        return "two"s.length();
    case 3:
        return "three"s.length();
    case 4:
        return "four"s.length();
    case 5:
        return "five"s.length();
    case 6:
        return "six"s.length();
    case 7:
        return "seven"s.length();
    case 8:
        return "eight"s.length();
    case 9:
        return "nine"s.length();
    case 10:
        return "ten"s.length();
    case 11:
        return "eleven"s.length();
    case 12:
        return "twelve"s.length();
    case 13:
        return "thirteen"s.length();
    case 14:
        return "fourteen"s.length();
    case 15:
        return "fifteen"s.length();
    case 16:
        return "sixteen"s.length();
    case 17:
        return "seventeen"s.length();
    case 18:
        return "eighteen"s.length();
    case 19:
        return "nineteen"s.length();
    case 20:
        return "twenty"s.length();
    case 30:
        return "thirty"s.length();
    case 40:
        return "forty"s.length();
    case 50:
        return "fifty"s.length();
    case 60:
        return "sixty"s.length();
    case 70:
        return "seventy"s.length();
    case 80:
        return "eighty"s.length();
    case 90:
        return "ninety"s.length();
    default:
        throw std::exception("WTF? How did this happen?");
    }
}
uint32_t numberLetterCountSum(uint32_t start, uint32_t end)
{
    uint32_t sum = 0;
    for (auto q = start; q <= end; q++)
    {
        sum += numberLetterCount(q);
    }
    return sum;
}

uint32_t euler<17>::value()
{
    return numberLetterCountSum(1, 1000);
}
