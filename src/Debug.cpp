#include "Debug.h"
#include "iostream"

void Debug::Log(const char *message)
{
    std::cout << "[LOG]" << message << std::endl;
}

void Debug::Log(int message)
{
    std::cout << "[LOG]" << message << std::endl;
}
