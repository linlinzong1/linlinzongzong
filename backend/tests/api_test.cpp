#include "database/Database.h"
#include "repository/TransactionRepository.h"
#include "service/TransactionService.h"
#include "api/TransactionController.h"

#include "httplib.h"

#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>


int main()
{

    Database db;


    assert(
        db.open("api_test.db")
    );


    assert(db.createTables());

    sqlite3* conn = db.getConnection();


    sqlite3_exec(
        conn,
        "INSERT INTO category(name,type) VALUES('餐饮',1);",
        nullptr,
        nullptr,
        nullptr
    );



    TransactionRepository repo(db);


    TransactionService service(repo);



    httplib::Server server;


    TransactionController controller(service);


    controller.registerRoutes(server);



    //启动服务器线程

    std::thread server_thread([&](){

        server.listen(
            "localhost",
            8081
        );

    });


    //等待服务器启动

    std::this_thread::sleep_for(
        std::chrono::milliseconds(200)
    );



    httplib::Client client(
        "localhost",
        8081
    );



    //====================
    // 测试POST
    //====================


    auto post_result =
        client.Post(
            "/transactions",
            R"(
            {
                "type":1,
                "amount":50,
                "categoryId":1,
                "date":"2026-07-27",
                "note":"API测试"
            }
            )",
            "application/json"
        );



    assert(post_result);


    assert(
        post_result->status == 201
    );


    std::cout
        <<"POST test passed"
        <<std::endl;



    //====================
    // 测试GET
    //====================


    auto get_result =
        client.Get(
            "/transactions"
        );


    assert(get_result);


    assert(
        get_result->status == 200
    );


    std::cout
        <<"GET test passed"
        <<std::endl;




    //====================
    // 测试DELETE
    //====================


    auto delete_result =
        client.Delete(
            "/transactions/1"
        );


    assert(delete_result);



    assert(
        delete_result->status == 200
    );


    std::cout
        <<"DELETE test passed"
        <<std::endl;



    server.stop();


    server_thread.join();



    db.close();


    std::cout
        <<"All API tests passed."
        <<std::endl;


    return 0;
}