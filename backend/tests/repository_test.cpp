#include "database/Database.h"
#include "repository/TransactionRepository.h"

#include <cassert>
#include <iostream>


int main()
{

    Database db;


    assert(
        db.open("repository_test.db")
    );


    assert(
        db.initialize()
    );



    TransactionRepository repo(db);



    //====================
    // 测试新增
    //====================

    Transaction t(
        0,
        1,
        50.0,
        1,
        "2026-07-27",
        "测试消费"
    );


    bool addResult = repo.add(t);


    assert(addResult);



    //====================
    // 测试查询
    //====================


    auto list = repo.findAll();


    assert(list.size() == 1);


    assert(
        list[0].getAmount() == 50.0
    );


    std::cout 
        << "Add and Find test passed"
        << std::endl;

    //====================
    // 测试按ID查询
    //====================

    auto result = 
    repo.findById(1);

    assert(result.has_value());

    assert(result->getAmount()==50);

    std::cout
    << "FindById test passed"
    << std::endl;

    //====================
    // 测试删除
    //====================


    int id = list[0].getId();


    bool deleteResult =
        repo.remove(id);


    assert(deleteResult);



    auto afterDelete =
        repo.findAll();



    assert(
        afterDelete.empty()
    );


    std::cout
        << "Delete test passed"
        << std::endl;



    db.close();


    return 0;
}