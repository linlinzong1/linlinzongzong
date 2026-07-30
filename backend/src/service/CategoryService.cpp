#include "service/CategoryService.h"

#include "utils/Logger.h"

CategoryService::CategoryService(
    CategoryRepository& repository
)
:
repository_(repository)
{

}



std::vector<Category>
CategoryService::getCategoriesByType(
    int type
)
{

    if(type != 1 && type != 2)
    {

        Logger::error(
            "Invalid category type"
        );


        return {};
    }


    return repository_.findByType(type);

}





bool CategoryService::addCategory(
    const Category& category
)
{

    if(
        category.getName().empty()
    )
    {

        Logger::error(
            "Category name empty"
        );


        return false;
    }



    if(
        category.getType()!=1
        &&
        category.getType()!=2
    )
    {

        Logger::error(
            "Invalid category type"
        );


        return false;
    }



    return repository_.add(category);

}