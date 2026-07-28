#include "database/Database.h"

#include "repository/TransactionRepository.h"

#include "service/TransactionService.h"

#include "api/TransactionController.h"

#include "utils/Logger.h"

#include "config/Config.h"

#include "httplib.h"



int main()
{

    //=========================
    // 1. 加载配置
    //=========================

    Config config;


    if(!config.load(
        "../config/app.conf"
    ))
    {
        Logger::error(
            "Config load failed"
        );

        return 1;
    }



    //=========================
    // 2. 初始化数据库
    //=========================

    Database db;


    if(!db.open(
        config.get("database")
    ))
    {
        Logger::error(
            "Database open failed"
        );

        return 1;
    }

    if(!db.initialize())
    {
        Logger::error(
            "Database initialization failed"
        );

        return 1;
    }



    //=========================
    // 3. 初始化业务层
    //=========================

    TransactionRepository repo(db);


    TransactionService service(repo);


    TransactionController controller(service);



    //=========================
    // 4. 初始化HTTP服务器
    //=========================

    httplib::Server server;

    server.set_default_headers({
        {"Access-Control-Allow-Origin", "*"},
        {"Access-Control-Allow-Headers", "Content-Type"},
        {"Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS"}
    });

    server.Options(
    R"(/.*)",
    [](const httplib::Request& req,
       httplib::Response& res)
        {
            res.status = 200;
        }
    );


    controller.registerRoutes(server);



    Logger::info(
        "Server running on port "
        + std::to_string(
            config.getInt("port")
        )
    );



    //=========================
    // 5. 启动服务器
    //=========================

    bool running = server.listen(
    config.get("host").c_str(),
    config.getInt("port")
    );


    if(!running)
    {
        Logger::error(
            "Server start failed"
        );

        return 1;
    }

    return 0;
}