#pragma once

#include "service/CategoryService.h"

#include "httplib.h"

class CategoryController
{

public:

    CategoryController(CategoryService& service);

    void registerRoutes(httplib::Server& server);

private:

    CategoryService& service_;

private:

    void getCategories(
        const httplib::Request& req,
        httplib::Response& res
    );

    void addCategory(
        const httplib::Request& req,
        httplib::Response& res
    );

};