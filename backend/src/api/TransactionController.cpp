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
        auto transactions = service_.getAllTransactions();
        json result = json::array();
        for (auto& t : transactions)
        {
            json item;
            item["id"] = t.getId();
            item["type"] = t.getType();
            item["amount"] = t.getAmount();
            item["categoryId"] = t.getCategoryId();
            item["date"] = t.getDate();
            item["note"] = t.getNote();

            result.push_back(item);
        }
        res.set_content(result.dump(), "application/json");
    });
}