#pragma once

#include "repository/CategoryRepository.h"

class CategoryService
{

public:

    CategoryService(
        CategoryRepository& repository
    );


    std::vector<Category>
    getCategoriesByType(
        int type
    );


    bool addCategory(
        const Category& category
    );

private:

    CategoryRepository& repository_;

};