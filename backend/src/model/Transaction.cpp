#include "model/Transaction.h"

#include "utils/Logger.h"

#include <iostream>

Transaction::Transaction()
{

    id_=0;
    type_=0;
    amount_=0.0;
    categoryId_=0;

}

Transaction::Transaction(
    int id,
    int type,
    double amount,
    int categoryId,
    const std::string& date,
    const std::string& note,
    const std::string& categoryName
)
{
    
    id_=id;
    type_=type;
    amount_=amount;
    categoryId_=categoryId;
    date_=date;
    note_=note;
    categoryName_ = categoryName;

}

int Transaction::getId() const
{
    return id_;
}

int Transaction::getType() const
{
    return type_;
}

double Transaction::getAmount() const
{
    return amount_;
}

int Transaction::getCategoryId() const
{
    return categoryId_;
}

std::string Transaction::getDate() const
{
    return date_;
}

std::string Transaction::getNote() const
{
    return note_;
}

std::string Transaction::getCategoryName() const
{
    return categoryName_;
}

void Transaction::print() const
{
   
    Logger::debug("Amount: " + std::to_string(amount_));
    
    Logger::debug("Note: " + std::string(note_));
}