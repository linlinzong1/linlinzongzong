#ifndef DATABASE_H
#define DATABASE_H

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

    sqlite3* getConnection();

private:

    sqlite3* db_;   

};

#endif // DATABASE_H
