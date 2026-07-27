#include "database/Database.h"

#include "repository/TransactionRepository.h"

#include "service/TransactionService.h"

#include "api/TransactionController.h"

#include "utils/Logger.h"


#include "httplib.h"



int main()
{

    Database db;


    if (!db.open(
        "linlinzongzong.db"
    ))
    {
        Logger::error("Failed to open database.");
        return 1;
    }


    db.createTables();

    TransactionRepository repo(db);

    TransactionService service(repo);

    httplib::Server server;

    TransactionController controller(service);

    controller.registerRoutes(server);

    Logger::debug("Server is running on http://localhost:8080");

    server.listen(
        "0.0.0.0",
        8080
    );


    return 0;
}