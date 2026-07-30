#ifndef DATE_UTILS_H
#define DATE_UTILS_H

#include <string>

class DateUtils
{
public:
    static std::string today();
    static bool isValidDate(
        const std::string& date
    );
};

#endif