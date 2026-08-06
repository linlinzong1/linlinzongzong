#include "database/Database.h"
#include "repository/CategoryRepository.h"

#include <cassert>
#include <iostream>


int main()
{

    Database db;


    assert(
        db.open("category_test.db")
    );


    db.createTables();



    CategoryRepository repo(db);



    auto list =
        repo.findByType(1);



    std::cout
        <<"count:"
        <<list.size()
        <<std::endl;



    Category c(
        1,
        "奶茶",
        1
    );



    assert(
        repo.add(c)
    );



    auto result =
        repo.findByType(1);



    assert(
        result.size()>0
    );


    std::cout
        <<"Category test passed"
        <<std::endl;


    db.close();


    return 0;
}