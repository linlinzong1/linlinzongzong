#pragma once

#include <vector>
#include <string>


struct CategoryAmount
{

    std::string name;

    double amount;

};



class Statistics
{

private:

    double income_;

    double expense_;

    std::vector<CategoryAmount> expenseCategories;

    std::vector<CategoryAmount> incomeCategories;


public:


    Statistics();

    void addIncome(double amount);

    void addExpense(double amount);

    double getIncome() const;

    double getExpense() const;


    double getBalance() const;

    void addExpenseCategory(
        const CategoryAmount& category
    );

    void addIncomeCategory(
        const CategoryAmount& category
    );

    const std::vector<CategoryAmount>&
    getExpenseCategories() const;



    const std::vector<CategoryAmount>&
    getIncomeCategories() const;


};