#include "config/Config.h"

#include <cassert>
#include <iostream>


int main()
{

    Config config;


    assert(
        config.load(
            "../config/app.conf"
        )
    );


    assert(
        config.getInt("port")==8080
    );


    std::cout
    <<"Config test passed"
    <<std::endl;


}