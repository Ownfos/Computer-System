#ifndef UTILITY_H
#define UTILITY_H

#include <exception>
#include <string>

namespace waffle
{
    void PrintNestedException(const std::exception& e, int level = 0);

    std::wstring ExePath();
}

#endif
