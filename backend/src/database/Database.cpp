#include "database/Database.h"
#include "utils/Logger.h"

#include <iostream>

Database::Database()
    :
    db_(nullptr)
{
    
}

Database::~Database()
{
    close();
}

bool Database::open(const std::string& filename)
{
    int result;

    result=sqlite3_open(filename.c_str(), &db_);

    

    if(result != SQLITE_OK)
    {
        Logger::error("Failed to open database: " + std::string(sqlite3_errmsg(db_)));
        return false;
    }

    result = sqlite3_exec(
        db_,
        "PRAGMA foreign_keys = ON;",
        nullptr,
        nullptr,
        nullptr
    );

    if(result != SQLITE_OK)
    {
        Logger::error(
            "Failed to enable foreign keys."
        );

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

        CREATE TABLE IF NOT EXISTS category
        (
            id INTEGER PRIMARY KEY AUTOINCREMENT,

            name TEXT NOT NULL,

            type INTEGER NOT NULL,

            UNIQUE(name, type)
        );

        


        CREATE TABLE IF NOT EXISTS transactions
        (
            id INTEGER PRIMARY KEY AUTOINCREMENT,

            type INTEGER NOT NULL,

            amount REAL NOT NULL,

            category_id INTEGER NOT NULL,

            date TEXT NOT NULL,

            note TEXT,

            create_at TEXT DEFAULT CURRENT_TIMESTAMP,

            updated_at TEXT DEFAULT CURRENT_TIMESTAMP,

            FOREIGN KEY(category_id)

            REFERENCES category(id)

            ON DELETE RESTRICT

        );

    )";


    char* error=nullptr;


    int result = sqlite3_exec(
        db_,
        sql,
        nullptr,
        nullptr,
        &error
    );


    if(result != SQLITE_OK)
    {
        Logger::error(
            "Failed to create tables: "
            + std::string(error)
        );

        sqlite3_free(error);

        return false;
    }

    Logger::info(
        "Database tables created successfully."
    );


    return true;
}

bool Database::initialize()
{
    return 
        createTables()
        &&
        initDefaultData();
}

bool Database::initDefaultData()
{

    const char* sql = R"(

    INSERT OR IGNORE INTO category
    (
        id,
        name,
        type
    )
    VALUES

    (1,'餐饮',1),

    (2,'交通',1),

    (3,'购物',1),

    (4,'娱乐',1),

    (5,'工资',2);


    )";


    char* error=nullptr;


    int result = sqlite3_exec(
        db_,
        sql,
        nullptr,
        nullptr,
        &error
    );


    if(result != SQLITE_OK)
    {

        Logger::error(
            "Failed to initialize category: "
            + std::string(error)
        );


        sqlite3_free(error);

        return false;
    }


    Logger::info(
        "Default categories initialized."
    );


    return true;
}

sqlite3* Database::getConnection()
{
    return db_;
}

bool Database::beginTransaction()
{
    return sqlite3_exec(
        db_,
        "BEGIN TRANSACTION;",
        nullptr,
        nullptr,
        nullptr
    ) == SQLITE_OK;
}

bool Database::commit()
{
    return sqlite3_exec(
        db_,
        "COMMIT;",
        nullptr,
        nullptr,
        nullptr
    ) == SQLITE_OK;
}

bool Database::rollback()
{
    return sqlite3_exec(
        db_,
        "ROLLBACK;",
        nullptr,
        nullptr,
        nullptr
    ) == SQLITE_OK;
}