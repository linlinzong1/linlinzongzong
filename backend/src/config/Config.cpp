#include "config/Config.h"

#include <fstream>
#include <sstream>


bool Config::load(
    const std::string& filename
)
{

    std::ifstream file(filename);


    if(!file.is_open())
    {
        return false;
    }


    std::string line;


    while(std::getline(file,line))
    {

        if(line.empty())
            continue;


        if(line[0]=='#')
            continue;


        auto pos=line.find('=');


        if(pos==std::string::npos)
            continue;



        std::string key =
            line.substr(0,pos);


        std::string value =
            line.substr(pos+1);



        configs[key]=value;

    }


    return true;

}



std::string Config::get(
    const std::string& key
) const
{
    auto it = configs.find(key);

    if(it != configs.end())
    {
        return it->second;
    }


    return "";

}



int Config::getInt(
    const std::string& key
)
{
    std::string value=get(key);

    if(value.empty())
    {
        return 0;
    }

    return std::stoi(value);
}