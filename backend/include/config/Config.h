#pragma once

#include <string>
#include <unordered_map>


class Config
{

private:

    std::unordered_map<std::string,std::string> configs;


public:

    bool load(
        const std::string& filename
    );


    std::string get(
        const std::string& key
    ) const;


    int getInt(
        const std::string& key
    );


};