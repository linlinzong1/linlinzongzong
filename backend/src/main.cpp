#include "service/TransactionService.h"


int main()
{

    Database db;


    db.open(
        "linlinzongzong.db"
    );


    db.createTables();



    TransactionRepository repo(db);



    TransactionService service(repo);



    Transaction t(
        0,
        1,
        35.5,
        1,
        "2026-07-22",
        "午饭"
    );



    service.addTransaction(t);



    auto list =
        service.getAllTransactions();



    for(auto& item:list)
    {
        item.print();
    }


    return 0;
}