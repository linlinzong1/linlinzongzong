#include "database/Database.h"
#include "repository/TransactionRepository.h"
#include "service/TransactionService.h"

#include <iostream>

int main()
{
    Database db;
    
    db.open("test.db");

    db.createTables();

    TransactionRepository repo(db);
    TransactionService service(repo);

    Transaction t(0, 1, 50.0, 1, "2026-07-23", "测试消费");

    service.addTransaction(t);

    auto list = service.getAllTransactions();

    for(auto& item: list)
    {
        item.print();
    }

    return 0;

}
