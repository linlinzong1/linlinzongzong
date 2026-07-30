#include "service/TransactionService.h"

#include <iostream>

#include "utils/Logger.h"

#include "utils/DateUtils.h"

TransactionService::TransactionService(TransactionRepository& repository)
    : repository_(repository)
{
}

bool TransactionService::addTransaction(const Transaction& transaction)
{
    
    if (transaction.getAmount() <= 0) {
        Logger::error(
            "Invalid transaction amount: " 
            + std::to_string(transaction.getAmount())
        );
        return false;
    }

    if(!DateUtils::isValidDate(
        transaction.getDate()
    ))
    {
        Logger::error(
            "Invalid date"
        );
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
    Logger::debug("DEBUG delete service id: " + std::to_string(id));

    if(id <= 0) {
        Logger::error("Invalid transaction ID: " + std::to_string(id));
        return false;
    }
    return repository_.remove(id);
}

bool TransactionService::updateTransaction(const Transaction& transaction){
    if(transaction.getId() <= 0)
    {
        Logger::error("Invalid transaction ID");

        return false;
    }

    if(transaction.getAmount() <= 0)
    {
        Logger::error("Invalid amount");

        return false;
    }

    return repository_.update(transaction);

}
