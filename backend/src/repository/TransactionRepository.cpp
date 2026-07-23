#include "repository/TransactionRepository.h"

#include <iostream>

//构造函数
TransactionRepository::TransactionRepository(Database& database)
    : database_(database)
{

}

//添加账单
bool TransactionRepository::add(const Transaction& transactions)
{
    sqlite3* db = database_.getConnection();

    const char* sql = "INSERT INTO transactions "
    "(type, amount, category_id, date, note)" 
    "VALUES (?, ?, ?, ?, ?);";


    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false; 
    }

    //绑定参数
    sqlite3_bind_int(stmt, 1, transactions.getType());
    sqlite3_bind_double(stmt, 2, transactions.getAmount());
    sqlite3_bind_int(stmt, 3, transactions.getCategoryId());

    std::string date = transactions.getDate();

    sqlite3_bind_text(stmt, 4, date.c_str(), -1, SQLITE_TRANSIENT);
    std::string note = transactions.getNote();
    sqlite3_bind_text(stmt, 5, note.c_str(), -1, SQLITE_TRANSIENT);

    result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    if (result != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    return true;

}

//查询所有账单
std::vector<Transaction>
TransactionRepository::findAll()
{

    std::vector<Transaction> resultList;

    sqlite3* db = database_.getConnection();

    const char* sql = "SELECT id, type, amount, "
    "category_id, date, note "
    "FROM transactions;";

    sqlite3_stmt* stmt;


    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);


    if (result != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return resultList; 
    }

    while(
        sqlite3_step(stmt) == SQLITE_ROW
    )
    {

        int id = sqlite3_column_int(stmt, 0);
        int type = sqlite3_column_int(stmt, 1);
        double amount = sqlite3_column_double(stmt, 2);
        int categoryId = sqlite3_column_int(stmt, 3);
        const unsigned char* dateText = sqlite3_column_text(stmt, 4);
        std::string date = dateText ? reinterpret_cast<const char*>(dateText) : "";


        const unsigned char* noteText = sqlite3_column_text(stmt, 5);
        std::string note = noteText ? reinterpret_cast<const char*>(noteText) : "";

        Transaction transactions(
            id,
            type,
            amount,
            categoryId,
            date,
            note
        );
        resultList.push_back(transactions);

    }

    sqlite3_finalize(stmt);

    return resultList;

}

//删除账单
bool TransactionRepository::remove(int id)
{
    sqlite3* db = database_.getConnection();

    const char* sql = "DELETE FROM transactions WHERE id = ?;";

    sqlite3_stmt* stmt;

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (result != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false; 
    }

    sqlite3_bind_int(stmt, 1, id);

    result = sqlite3_step(stmt);
    if(result != SQLITE_DONE
    )
    {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;

}
