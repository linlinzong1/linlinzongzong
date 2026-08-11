#include "utils/Logger.h"

#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>


std::mutex Logger::mutex_;



static std::string getTime()
{

    auto now =
    std::chrono::system_clock::now();


    auto t =
    std::chrono::system_clock::to_time_t(now);


    std::stringstream ss;


    ss 
    << std::put_time(
        std::localtime(&t),
        "%Y-%m-%d %H:%M:%S"
    );


    return ss.str();

}



void Logger::write(
    Level level,
    const std::string& msg
)
{

    std::lock_guard<std::mutex> lock(
        mutex_
    );


    std::string levelText;


    switch(level)
    {

        case INFO:
            levelText="INFO";
            break;

        case WARNING:
            levelText="WARNING";
            break;

        case ERROR:
            levelText="ERROR";
            break;

        case DEBUG:
            levelText="DEBUG";
            break;

    }


    std::string line =
        getTime()
        +" ["
        +levelText
        +"] "
        +msg;


    std::cout
        << line
        << std::endl;



    std::ofstream file(
        "../../logs/app.log",
        std::ios::app
    );


    if(file.is_open())
    {
        file
        << line
        << std::endl;
    }

}



void Logger::info(
const std::string& msg)
{
    write(INFO,msg);
}


void Logger::warning(
const std::string& msg)
{
    write(WARNING,msg);
}



void Logger::error(
const std::string& msg)
{
    write(ERROR,msg);
}



void Logger::debug(
const std::string& msg)
{
    write(DEBUG,msg);
}
