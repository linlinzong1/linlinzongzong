#pragma once

#include <vector>
#include <optional>

#include "model/Transaction.h"
#include "model/Statistics.h"
#include "database/Database.h"

class TransactionRepository
{

public:

    TransactionRepository(Database& database);

    bool add(const Transaction& transactions);

    std::vector<Transaction> findAll();

    bool remove(int id);

    bool update(const Transaction& transactions);

    std::optional<Transaction> findById(int id);

    sqlite3* getConnection() const{return database_.getConnection();}

    Statistics getStatistics();

private:

    Database& database_; //引用成员变量，Respository不拥有Database，只是使用它

};
