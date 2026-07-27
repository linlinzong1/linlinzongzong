#include "utils/Logger.h"

#include <iostream>

void Logger::info(const std::string& message)
{
    std::cout << "[INFO] " << message << std::endl;
}

void Logger::error(const std::string& message)
{
    std::cerr << "[ERROR] " << message << std::endl;
}

void Logger::debug(const std::string& message)
{
    std::cout << "[DEBUG] " << message << std::endl;
}