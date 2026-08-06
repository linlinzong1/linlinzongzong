#include "api/CategoryController.h"

#include "utils/Logger.h"

#include "model/Category.h"

#include <nlohmann/json.hpp>


using json = nlohmann::json;



CategoryController::CategoryController(
    CategoryService& service
)
:
service_(service)
{

}





void CategoryController::registerRoutes(
    httplib::Server& server
)
{

    Logger::debug(
        "Registering Category routes"
    );



    /*
        查询分类

        GET /categories?type=1

    */
    server.Get(
        "/categories",
        [this](
            const httplib::Request& req,
            httplib::Response& res
        )
        {

            getCategories(
                req,
                res
            );

        }
    );




    /*
        新增分类

        POST /categories

        {
            "name":"奶茶",
            "type":1
        }

    */

    server.Post(
        "/categories",
        [this](
            const httplib::Request& req,
            httplib::Response& res
        )
        {

            addCategory(
                req,
                res
            );

        }
    );


}





void CategoryController::getCategories(
    const httplib::Request& req,
    httplib::Response& res
)
{

    if(!req.has_param("type"))
    {

        res.status=400;


        res.set_content(
            R"({"message":"missing type"})",
            "application/json"
        );


        return;

    }



    int type =
        std::stoi(
            req.get_param_value("type")
        );



    auto categories =
        service_.getCategoriesByType(type);



    json result =
        json::array();



    for(auto& c:categories)
    {

        result.push_back(
            {
                {
                    "id",
                    c.getId()
                },

                {
                    "name",
                    c.getName()
                },

                {
                    "type",
                    c.getType()
                }

            }
        );

    }



    res.set_content(
        result.dump(),
        "application/json"
    );

}







void CategoryController::addCategory(
    const httplib::Request& req,
    httplib::Response& res
)
{


    try
    {

        auto body =
            json::parse(
                req.body
            );



        Category category(
            body["id"],

            body["name"],

            body["type"]

        );



        bool result =
            service_.addCategory(
                category
            );



        if(result)
        {

            res.status=201;


            res.set_content(
                R"({"success":true})",
                "application/json"
            );

        }
        else
        {

            res.status=400;


            res.set_content(
                R"({"success":false})",
                "application/json"
            );

        }


    }
    catch(...)
    {

        res.status=400;


        res.set_content(
            R"({"message":"invalid json"})",
            "application/json"
        );

    }

}