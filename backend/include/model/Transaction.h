#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {

public:

    Transaction();

    Transaction(
        int id,
        int type,
        double amount,
        int categoryId,
        const std::string& date,
        const std::string& note
    );

    int getId() const;
    int getType() const;
    double getAmount() const;
    int getCategoryId() const;
    std::string getDate() const;
    std::string getNote() const;

    void print() const;

private:

    int id_;
    int type_;
    double amount_;
    int categoryId_;
    std::string date_;
    std::string note_;

};

#endif