#pragma once

template <typename T>
constexpr T pythagTripletProduct(T sum)
{
    auto maxC = sum / 2;
    if (maxC % 2 == 0)
    {
        maxC--;
    }

    for (T c = maxC; c > 1; c -= 2)
    {
        for (T b = c - 1; b > (c - 1) / 2; b--)
        {
            T a = sum - (c + b);
            if ((a * a) + (b * b) == (c * c))
            {
                return a * b * c;
            }
        }
    }

    return 0;
}
