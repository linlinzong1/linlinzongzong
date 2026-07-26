#ifndef TRANSACTION_REPOSITORY_H
#define TRANSACTION_REPOSITORY_H

#include <vector>

#include "model/Transaction.h"
#include "database/Database.h"

class TransactionRepository
{

public:

    TransactionRepository(Database& database);

    bool add(const Transaction& transactions);

    std::vector<Transaction> findAll();

    bool remove(int id);

    bool update(const Transaction& transactions);

private:

    Database& database_; //引用成员变量，Respository不拥有Database，只是使用它

};

#endif // TRANSACTION_REPOSITORY_H