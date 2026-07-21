#include "database/Database.h"

#include <iostream>

Database::Database()
{
    db_=nullptr;
}

Database::~Database()
{
    close();
}

bool Database::open(const std::string& filename)
{
    int result;

    result=sqlite3_open(filename.c_str(), &db_);

    if(result!=SQLITE_OK)
    {
        std::cerr<<"Failed to open database: "<<sqlite3_errmsg(db_)<<std::endl;
        return false;
    }

    std::cout<<"Database opened successfully."<<std::endl;

    return true;
}

void Database::close()
{
    if(db_)
    {
        sqlite3_close(db_);
        db_=nullptr;
        std::cout<<"Database closed successfully."<<std::endl;
    }
}

bool Database::createTables()
{
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS transactions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            type INTEGER NOT NULL,
            amount REAL NOT NULL,
            category_id INTEGER NOT NULL,
            date TEXT NOT NULL,
            note TEXT
        );

        CREATE TABLE IF NOT EXISTS categoriy (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            type INTEGER NOT NULL
        );

    )";

    char* error=nullptr;

    int result=sqlite3_exec(db_, sql, nullptr, nullptr, &error);

    if(result!=SQLITE_OK)
    {
        std::cerr<<"Failed to create tables: "<<error<<std::endl;
        sqlite3_free(error);
        return false;
    }

    return true;

}

sqlite3* Database::getConnection()
{
    return db_;
}