#include "database/Database.h"

#include <iostream>

int main()
{
    Database db;
    if (!db.open("database_test.db"))
    {
        std::cerr << "Failed to open database." << std::endl;
        return 1;
    }

    if(db.createTables())
    {
        std::cout << "Tables created successfully." << std::endl;
    }
    else
    {
        std::cerr << "Failed to create tables." << std::endl;
        return 1;
    }

    db.close();
    return 0;
}