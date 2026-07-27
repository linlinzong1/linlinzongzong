#ifndef TRANSACTION_SERVICE_H
#define TRANSACTION_SERVICE_H

#include "repository/TransactionRepository.h"

class TransactionService
{

public:
    TransactionService(TransactionRepository& repository);

    bool addTransaction(const Transaction& transaction);

    std::vector<Transaction> getAllTransactions();

    bool deleteTransaction(int id);

    bool updateTransaction(const Transaction& transaction);

private:

    TransactionRepository& repository_; //引用成员变量，Service不拥有Repository，只是使用它

};

#endif // TRANSACTION_SERVICE_H 