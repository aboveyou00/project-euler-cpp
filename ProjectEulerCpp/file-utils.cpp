#include "stdafx.h"

#include <fstream>
#include <sstream>

std::string readFile(std::string name)
{
    std::ifstream file(name);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
