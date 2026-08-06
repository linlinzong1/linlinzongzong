#pragma once
#include <string>
#include <utility>  // for std::pair

namespace DateUtils {
    std::string today();
    bool isValidDate(const std::string& date);
    std::pair<std::string, std::string> getDateRange(
        const std::string& granularity, const std::string& baseDate);
}