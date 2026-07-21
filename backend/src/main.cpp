#include "database/Database.h"
#include "repository/TransactionRepository.h"


int main()
{

    Database db;

    db.open("linlinzongzong.db");

    db.createTables();


    TransactionRepository repo(db);


    Transaction t(
        0,
        1,
        35.5,
        1,
        "2026-07-21",
        "午饭"
    );


    repo.add(t);



    auto list = repo.findAll();


    for(auto& item:list)
    {
        item.print();
    }


    return 0;
}