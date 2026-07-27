#include "database/Database.h"

#include <cassert>
#include <iostream>
#include <cstdio>


int main()
{
    // 删除旧测试数据库，保证每次测试环境干净
    std::remove("database_test.db");


    Database db;


    //========================
    // 1. 测试数据库打开
    //========================

    assert(
        db.open("database_test.db")
    );


    std::cout
        << "Database open test passed."
        << std::endl;



    //========================
    // 2. 测试建表
    //========================

    assert(
        db.createTables()
    );


    std::cout
        << "Create tables test passed."
        << std::endl;



    sqlite3* conn = db.getConnection();



    //========================
    // 3. 测试 category 表
    //========================


    sqlite3_stmt* stmt;


    int result = sqlite3_prepare_v2(
        conn,
        "SELECT name FROM sqlite_master "
        "WHERE type='table' AND name='category';",
        -1,
        &stmt,
        nullptr
    );


    assert(result == SQLITE_OK);


    bool categoryExist = false;


    if(sqlite3_step(stmt)==SQLITE_ROW)
    {
        categoryExist = true;
    }


    sqlite3_finalize(stmt);


    assert(categoryExist);


    std::cout
        << "Category table test passed."
        << std::endl;



    //========================
    // 4. 测试 transactions 表
    //========================


    result = sqlite3_prepare_v2(
        conn,
        "SELECT name FROM sqlite_master "
        "WHERE type='table' AND name='transactions';",
        -1,
        &stmt,
        nullptr
    );


    assert(result == SQLITE_OK);



    bool transactionExist = false;


    if(sqlite3_step(stmt)==SQLITE_ROW)
    {
        transactionExist = true;
    }


    sqlite3_finalize(stmt);



    assert(transactionExist);



    std::cout
        << "Transactions table test passed."
        << std::endl;




    //========================
    // 5. 测试外键开启
    //========================


    result = sqlite3_prepare_v2(
        conn,
        "PRAGMA foreign_keys;",
        -1,
        &stmt,
        nullptr
    );


    assert(result == SQLITE_OK);



    int foreignKeyEnabled = 0;


    if(sqlite3_step(stmt)==SQLITE_ROW)
    {
        foreignKeyEnabled =
            sqlite3_column_int(stmt,0);
    }


    sqlite3_finalize(stmt);



    assert(
        foreignKeyEnabled == 1
    );



    std::cout
        << "Foreign key test passed."
        << std::endl;



    db.close();



    std::cout
        << "All database tests passed."
        << std::endl;



    return 0;
}