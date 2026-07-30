#pragma once

#include "database/Database.h"
#include "model/Category.h"

#include <vector>

class CategoryRepository
{

public:
    CategoryRepository(Database& db);

    std::vector<Category> findByType(int type);

    bool add(const Category& category);

private:
    Database& db_;

};