#include "database/Database.h"
#include "repository/TransactionRepository.h"
#include "service/TransactionService.h"

#include <cassert>
#include <iostream>



int main()
{

    Database db;


    assert(
        db.open("service_test.db")
    );


    db.createTables();



    TransactionRepository repo(db);


    TransactionService service(repo);



    //=====================
    // 正常交易测试
    //=====================


    Transaction normal(
        0,
        1,
        100,
        1,
        "2026-07-27",
        "正常消费"
    );


    bool result =
        service.addTransaction(normal);



    assert(result);



    std::cout
        << "Normal transaction passed"
        << std::endl;



    //=====================
    // 非法金额测试
    //=====================


    Transaction invalid(
        0,
        1,
        -20,
        1,
        "2026-07-27",
        "错误消费"
    );


    bool invalidResult =
        service.addTransaction(invalid);



    assert(
        invalidResult == false
    );



    std::cout
        << "Invalid amount test passed"
        << std::endl;



    db.close();


    return 0;
}