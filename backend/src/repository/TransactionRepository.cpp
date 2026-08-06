#include "repository/TransactionRepository.h"
#include "database/Database.h"
#include "model/Statistics.h"

#include "utils/Logger.h"

#include <iostream>
#include <optional>

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
        Logger::error("Failed to prepare statement: "  + std::string(sqlite3_errmsg(db)));
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
        Logger::error("Failed to execute statement: " + std::string(sqlite3_errmsg(db)));
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

    const char* sql = R"(
        SELECT t.id, t.type, t.amount, t.category_id, t.date, t.note, c.name 
        As category_name
        FROM transactions t
        LEFT JOIN category c ON t.category_id = c.id;
    )";

    sqlite3_stmt* stmt;

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);


    if (result != SQLITE_OK) {
        Logger::error("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
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

        const unsigned char* nameText = sqlite3_column_text(stmt, 6);
        std::string categoryName = nameText ? reinterpret_cast<const char*>(nameText) : ""; 


        Transaction transactions(
            id,
            type,
            amount,
            categoryId,
            date,
            note,
            categoryName
        );
        resultList.push_back(transactions);

    }

    sqlite3_finalize(stmt);

    return resultList;

}

//根据ID查找账单
std::optional<Transaction> TransactionRepository::findById(int id)
{
    const char* sql = 
    R"(
        SELECT
            t.id,
            t.type,
            t.amount,
            t.category_id,
            t.date,
            t.note,
            c.name AS category_name
        FROM transactions t
        LEFT JOIN category c ON t.category_id = c.id
        WHERE t.id = ?;    
    )";

    sqlite3_stmt* stmt;

    int result = 
    sqlite3_prepare_v2(
        database_.getConnection(),
        sql, -1, &stmt, nullptr
    );
        if(result != SQLITE_OK){
            
            Logger::error(
                "Failed to prepare findById statement"
            );
            return std::nullopt;
        }
    sqlite3_bind_int(stmt, 1, id);
    if(sqlite3_step(stmt) == SQLITE_ROW){
        int id = sqlite3_column_int(stmt, 0);
        int type = sqlite3_column_int(stmt, 1);
        double amount = sqlite3_column_double(stmt, 2);
        int categoryId = sqlite3_column_int(stmt, 3);
        std::string date = (const char*)sqlite3_column_text(stmt, 4) ?: "";
        std::string note = (const char*)sqlite3_column_text(stmt, 5) ?: "";
        std::string categoryName = (const char*)sqlite3_column_text(stmt, 6) ?: "";

        Transaction transaction(id, type, amount, categoryId, date, note, categoryName);
        sqlite3_finalize(stmt);
        return transaction;
    }

    sqlite3_finalize(stmt);
    return std::nullopt;
}

//删除账单
bool TransactionRepository::remove(int id)
{
    sqlite3* db = database_.getConnection();

    const char* sql = "DELETE FROM transactions WHERE id = ?;";

    sqlite3_stmt* stmt;

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (result != SQLITE_OK) {
        Logger::error("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
        return false; 
    }

    sqlite3_bind_int(stmt, 1, id);

    result = sqlite3_step(stmt);
    if(result != SQLITE_DONE
    )
    {
        Logger::error("Failed to execute statement: " + std::string(sqlite3_errmsg(db)));
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;

}

//修改账单
bool TransactionRepository::update(const Transaction& transaction)
{
    Logger::debug("DEBUG update id=" + std::to_string(transaction.getId()));

    sqlite3* db = database_.getConnection();

    const char* sql = 
        "UPDATE transactions SET "
        "type=?, "
        "amount=?, "
        "category_id=?, "
        "date=?, "
        "note=?"
        "WHERE id=?;";
    
        sqlite3_stmt* stmt;

        int result = sqlite3_prepare_v2(
            db,
            sql,
            -1,
            &stmt,
            nullptr
        );

        if(result != SQLITE_OK)
        {
            Logger::error("Failes to prepare update statement: " + std::string(sqlite3_errmsg(db)));

            return false;
        }

        sqlite3_bind_int(
            stmt,
            1,
            transaction.getType()
        );

        sqlite3_bind_double(
            stmt,
            2,
            transaction.getAmount()
        );

        sqlite3_bind_int(
            stmt,
            3,
            transaction.getCategoryId()
        );

        std::string date = 
            transaction.getDate();

        sqlite3_bind_text(
            stmt,
            4,
            date.c_str(),
            -1,
            SQLITE_TRANSIENT
        );

        std::string note = 
            transaction.getNote();
            
        sqlite3_bind_text(
            stmt,
            5,
            note.c_str(),
            -1,
            SQLITE_TRANSIENT
        );

        sqlite3_bind_int(
            stmt,
            6,
            transaction.getId()
        );

        result = sqlite3_step(stmt);

        sqlite3_finalize(stmt);
        
        if (result != SQLITE_DONE)
        {
            Logger::error("Failed to update transaction: " + std::string(sqlite3_errmsg(db)));

            return false;
        }
        
    return true;

}

//统计账单
Statistics TransactionRepository::getStatistics()
{

    Statistics statistics;


    const char* sql =
    R"(
        SELECT
            type,
            SUM(amount)

        FROM transactions

        GROUP BY type;
    )";


    sqlite3_stmt* stmt;


    if(
        sqlite3_prepare_v2(
            database_.getConnection(),
            sql,
            -1,
            &stmt,
            nullptr
        )
        != SQLITE_OK
    )
    {

        Logger::error(
            "prepare statistics failed"
        );

        return statistics;
    }



    while(
        sqlite3_step(stmt)
        == SQLITE_ROW
    )
    {

        int type =
        sqlite3_column_int(
            stmt,
            0
        );


        double amount =
        sqlite3_column_double(
            stmt,
            1
        );


        if(type==1)
        {
            statistics.addExpense(amount);
        }


        if(type==2)
        {
            statistics.addIncome(amount);
        }

    }



    sqlite3_finalize(stmt);


    return statistics;

}
