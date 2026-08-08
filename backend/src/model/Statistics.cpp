#include "model/Statistics.h"



Statistics::Statistics()
{

    income_ = 0;

    expense_ = 0;

}



void Statistics::addIncome(
    double amount
)
{

    income_ += amount;

}



void Statistics::addExpense(
    double amount
)
{

    expense_ += amount;

}



double Statistics::getIncome() const
{

    return income_;

}



double Statistics::getExpense() const
{

    return expense_;

}



double Statistics::getBalance() const
{

    return income_ - expense_;

}



void Statistics::addExpenseCategory(
    const CategoryAmount& category
)
{

    expenseCategories.push_back(category);

}



void Statistics::addIncomeCategory(const CategoryAmount& category)
{

    incomeCategories.push_back(category);

}




const std::vector<CategoryAmount>&
Statistics::getExpenseCategories() const
{

    return expenseCategories;

}



const std::vector<CategoryAmount>&
Statistics::getIncomeCategories() const
{

    return incomeCategories;

}