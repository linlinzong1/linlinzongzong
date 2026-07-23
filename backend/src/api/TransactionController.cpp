#include "api/TransactionController.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TransactionController::TransactionController(TransactionService& service)
    : service_(service)
{
}

void TransactionController::registerRoutes(httplib::Server& server)
{

    std::cout << "DEBUG: Registering routes for TransactionController" << std::endl;    
    

    //查询所有交易记录
    server.Get("/transactions", [&](const httplib::Request& req, httplib::Response& res)
    {
        try
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
        }

        catch (const std::exception& e)
        {
            json error;
            error["success"] = false;
            error["message"] = std::string("Failed to retrieve transactions: ") + e.what();

            res.status = 500; // Internal Server Error

            res.set_content(error.dump(), "application/json");
        }
    });

    //新增交易记录
    server.Post("/transactions", [&](const httplib::Request& req, httplib::Response& res)
    {
        std::cout << "DEBUG: POST /transactions received" << std::endl;  
        try
        {
            auto body = json::parse(req.body);

            int type = body.at("type").get<int>();
            double amount = body.at("amount").get<double>();
            int categoryId = body.at("categoryId").get<int>();
            std::string date = body.at("date").get<std::string>();
            std::string note = body.value("note", ""); 

            if(amount <= 0)
            {
                json error;
                error["success"] = false;
                error["message"] = "Amount must be greater than 0.";

                res.status = 400;

                res.set_content(error.dump(), "application/json");
                return;
            }

            if(date.empty())
            {
                json error;
                error["success"] = false;
                error["message"] = "Date cannot be empty.";

                res.status = 400;

                res.set_content(error.dump(), "application/json");
                return;
            }

            Transaction transaction(0, type, amount, categoryId, date, note);

            std::cout << "DEBUG before service" << std::endl;

            bool success = service_.addTransaction(transaction);

            std::cout << "DEBUG after service" << std::endl;

            json response;

            if(success)
            {
                response["success"] = true;
                response["message"] = "Transaction added successfully.";
                res.status = 201; // Created
            }
            else
            {
                response["success"] = false;
                response["message"] = "Failed to add transaction.";

                res.status = 500; // Internal Server Error
            }

            res.set_content(response.dump(), "application/json");

        }

        catch(const nlohmann::json::out_of_range& e)
        {
            json error;
            error["success"] = false;
            error["message"] = std::string("Missing required fields: ") + e.what();

            res.status = 400; // Bad Request

            res.set_content(error.dump(), "application/json");
        }

        catch (const nlohmann::json::exception& e)
        {
            json error;
            error["success"] = false;
            error["message"] = std::string("Invalid JSON format: ") + e.what();

            res.status = 400; // Bad Request

            res.set_content(error.dump(), "application/json");
        }

        catch (const std::exception& e)
        {
            json error;
            error["success"] = false;
            error["message"] = std::string("Failed to add transaction: ") + e.what();

            res.status = 500; // Internal Server Error

            res.set_content(error.dump(), "application/json");
        }
        
    });
}