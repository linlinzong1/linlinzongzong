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

namespace DateUtils {

std::pair<std::string, std::string> getDateRange(const std::string& granularity, const std::string& baseDate) {
    std::tm tm = {};
    std::istringstream ss(baseDate);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    time_t raw = mktime(&tm);

    char start[11], end[11];

    if (granularity == "year") {
        // 当年1月1日
        std::tm startTm = tm;
        startTm.tm_mon = 0; startTm.tm_mday = 1;
        mktime(&startTm);
        // 下一年1月1日
        std::tm endTm = tm;
        endTm.tm_year += 1;
        endTm.tm_mon = 0; endTm.tm_mday = 1;
        mktime(&endTm);
        std::strftime(start, sizeof(start), "%Y-%m-%d", &startTm);
        std::strftime(end, sizeof(end), "%Y-%m-%d", &endTm);
    } else if (granularity == "month") {
        // 当月1日
        std::tm startTm = tm;
        startTm.tm_mday = 1;
        mktime(&startTm);
        // 下月1日
        std::tm endTm = tm;
        if (endTm.tm_mon == 11) { endTm.tm_year++; endTm.tm_mon = 0; }
        else endTm.tm_mon++;
        endTm.tm_mday = 1;
        mktime(&endTm);
        std::strftime(start, sizeof(start), "%Y-%m-%d", &startTm);
        std::strftime(end, sizeof(end), "%Y-%m-%d", &endTm);
    } else if (granularity == "week") {
        // 周一作为一周开始 (0=周日, 1=周一)
        int wday = tm.tm_wday;
        int offset = (wday == 0) ? 6  : wday - 1;
        time_t startRaw = raw - offset * 86400;
        time_t endRaw = startRaw + 7 * 86400;
        
        struct tm startTm, endTm;
        localtime_r(&startRaw, &startTm);
        localtime_r(&endRaw, &endTm);

        std::strftime(start, sizeof(start), "%Y-%m-%d", &startTm);
        std::strftime(end, sizeof(end), "%Y-%m-%d", &endTm);
    } else {
        // 默认按月
        return getDateRange("month", baseDate);
    }
    return {start, end};
}

}