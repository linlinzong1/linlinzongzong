#include "service/TransactionService.h"

#include <iostream>

TransactionService::TransactionService(TransactionRepository& repository)
    : repository_(repository)
{
}

bool TransactionService::addTransaction(const Transaction& transaction)
{
    
    if (transaction.getAmount() <= 0) {
        std::cerr << "Invalid transaction amount: " << transaction.getAmount() << std::endl;
        return false;
    }

    return repository_.add(transaction);

}


std::vector<Transaction> TransactionService::getAllTransactions()
{
    return repository_.findAll();
}

bool TransactionService::deleteTransaction(int id)
{
    if(id <= 0) {
        std::cerr << "Invalid transaction ID: " << id << std::endl;
        return false;
    }
    return repository_.remove(id);
}
