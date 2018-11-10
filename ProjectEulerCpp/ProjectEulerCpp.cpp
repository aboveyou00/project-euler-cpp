// ProjectEulerCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "euler-meta.h"

int main()
{
    std::cout << "Euler[2] = " << euler<2>::value << std::endl;
    std::cout << "Euler[6] = " << euler<6>::value << std::endl;

    return 0;
}
