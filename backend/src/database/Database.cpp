#include "database/Database.h"
#include "utils/Logger.h"

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
        Logger::error("Failed to open database: " + std::string(sqlite3_errmsg(db_)));
        return false;
    }

    Logger::info("Database opened successfully: " + filename);

    return true;
}

void Database::close()
{
    if(db_)
    {
        sqlite3_close(db_);
        db_=nullptr;
        Logger::info("Database closed successfully.");
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
        Logger::error("Failed to create tables: " + std::string(error));
        sqlite3_free(error);
        return false;
    }

    return true;

}

sqlite3* Database::getConnection()
{
    return db_;
}