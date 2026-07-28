#pragma once

#include <string>

#include <sqlite3.h>

class Database
{

public:

    Database();

    ~Database();

    bool open(const std::string& filename);

    void close();

    bool createTables();

    bool initialize();

    bool initDefaultData();

    sqlite3* getConnection();

    bool beginTransaction();

    bool commit();

    bool rollback();

private:

    sqlite3* db_;   

};

