#include "service/TransactionService.h"

#include <iostream>

TransactionService::TransactionService(TransactionRepository& repository)
    : repository_(repository)
{
}

bool TransactionService::addTransaction(const Transaction& transactions)
{
    
    if (transactions.getAmount() <= 0) {
        std::cerr << "Invalid transaction amount: " << transactions.getAmount() << std::endl;
        return false;
    }

    return repository_.add(transactions);

}


std::vector<Transaction> TransactionService::getAllTransactions()
{
    return repository_.findAll();
}


bool TransactionService::deleteTransaction(int id)
{
    std::cout << "DEBUG delete service id: " << id << std::endl;

    if(id <= 0) {
        std::cerr << "Invalid transaction ID: " << id << std::endl;
        return false;
    }
    return repository_.remove(id);
}

bool TransactionService::updateTransaction(const Transaction& transactions){
    if(transactions.getId() <= 0)
    {
        std::cerr
        << "Invalid transaction ID"
        << std::endl;

        return false;
    }

    if(transactions.getAmount() <= 0)
    {
        std::cerr
        << "Invalid amount"
        << std::endl;

        return false;
    }

    return repository_.update(transactions);

}
