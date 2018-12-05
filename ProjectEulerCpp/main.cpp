// ProjectEulerCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "euler.h"

int main()
{
    std::cout << "Euler[2] = " << euler<2>::value << std::endl;
    std::cout << "Euler[3] = " << euler<3>::value << std::endl;
    std::cout << "Euler[4] = " << euler<4>::value() << std::endl;
    std::cout << "Euler[5] = " << euler<5>::value << std::endl;
    std::cout << "Euler[6] = " << euler<6>::value << std::endl;
    std::cout << "Euler[14] = " << euler<14>::value() << std::endl;
    std::cout << "Euler[15] = " << euler<15>::value << std::endl;
    std::cout << "Euler[18] = " << euler<18>::value() << std::endl;
    std::cout << "Euler[67] = " << euler<67>::value() << std::endl;
    std::cout << "Euler[81] = " << euler<81>::value() << std::endl;
    std::cout << "Euler[82] = " << euler<82>::value() << std::endl;
    std::cout << "Euler[83] = " << euler<83>::value() << std::endl;

    return 0;
}
