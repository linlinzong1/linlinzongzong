#pragma once

#include "repository/TransactionRepository.h"
#include "model/Statistics.h"

class TransactionService
{

public:
    TransactionService(TransactionRepository& repository);

    bool addTransaction(const Transaction& transaction);

    std::vector<Transaction> getAllTransactions();

    bool deleteTransaction(int id);

    bool updateTransaction(const Transaction& transaction);

    Statistics getStatistics(
        std::string granularity,
        std::string date
    );

private:

    TransactionRepository& repository_; //引用成员变量，Service不拥有Repository，只是使用它

};
