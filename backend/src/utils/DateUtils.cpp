#include "utils/DateUtils.h"

#include <ctime>
#include <regex>
#include <sstream>
#include <iomanip>

std::string DateUtils::today()
{
    time_t now = time(nullptr);
    tm* local = localtime(&now);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) 
        << (local->tm_year + 1900) << "-"
        << std::setw(2) << (local->tm_mon + 1) << "-"
        << std::setw(2) << local->tm_mday;
    return oss.str();
}

bool DateUtils::isValidDate(const std::string& date)
{
    std::regex pattern(
        R"(\d{4}-\d{2}-\d{2})"
    );

    return std::regex_match(
        date,
        pattern
    );
}