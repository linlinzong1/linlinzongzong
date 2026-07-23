#include "database/Database.h"

#include "repository/TransactionRepository.h"

#include "service/TransactionService.h"

#include "api/TransactionController.h"


#include "httplib.h"



int main()
{

    Database db;


    if (!db.open(
        "linlinzongzong.db"
    ))
    {
        std::cerr << "Failed to open database." << std::endl;
        return 1;
    }


    db.createTables();



    TransactionRepository repo(db);



    TransactionService service(repo);



    httplib::Server server;



    TransactionController controller(service);



    controller.registerRoutes(server);

    std::cout << "Server is running on http://localhost:8080" << std::endl;

    server.listen(
        "0.0.0.0",
        8080
    );


    return 0;
}