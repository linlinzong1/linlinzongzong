#pragma once

#include <string>
#include <mutex>


class Logger
{

public:

    enum Level
    {
        INFO,
        WARNING,
        ERROR,
        DEBUG
    };


    static void info(
        const std::string& msg
    );


    static void warning(
        const std::string& msg
    );


    static void error(
        const std::string& msg
    );


    static void debug(
        const std::string& msg
    );


private:

    static void write(
        Level level,
        const std::string& msg
    );


    static std::mutex mutex_;

};