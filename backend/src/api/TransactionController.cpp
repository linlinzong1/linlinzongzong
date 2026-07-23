#include "api/TransactionController.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TransactionController::TransactionController(TransactionService& service)
    : service_(service)
{
}

void TransactionController::registerRoutes(httplib::Server& server)
{
    server.Get("/transactions", [&](const httplib::Request& req, httplib::Response& res)
    {
        auto list = service_.getAllTransactions();
        json result = json::array();
        for (auto& item : list)
        {
            json obj;
            obj["id"] = item.getId();
            obj["amount"] = item.getAmount();
            obj["note"] = item.getNote();

            result.push_back(obj);
        }
        res.set_content(result.dump(), "application/json");
    });
}