#include "repository/CategoryRepository.h"
#include "database/Database.h"

#include "utils/Logger.h"

#include <sqlite3.h>

CategoryRepository::CategoryRepository(
    Database& db
)
:
db_(db)
{

}

std::vector<Category> CategoryRepository::findByType(int type)
{
    std::vector<Category> categories;

    const char* sql = 
    R"(
    SELECT id,name,type
    FROM category
    WHERE type=?;
    )";

    sqlite3_stmt* stmt;

    if(
        sqlite3_prepare_v2(
            db_.getConnection(),
            sql,
            -1,
            &stmt,
            nullptr
        )
        != SQLITE_OK
    )
    {

        Logger::error(
            "Failed to prepare category query"
        );


        return categories;
    }



    sqlite3_bind_int(
        stmt,
        1,
        type
    );



    while(
        sqlite3_step(stmt)
        == SQLITE_ROW
    )
    {
        int categoryId =
            sqlite3_column_int(
                stmt,
                0
            );


        std::string name =
            reinterpret_cast<const char*>(
                sqlite3_column_text(
                    stmt,
                    1
                )
            );


        int categoryType =
            sqlite3_column_int(
                stmt,
                2
            );

        Logger::debug(
            "id="
            +id
            +
            " name="
            + name
            +
            " type="
            + std::to_string(categoryType)
        );

        categories.emplace_back(
            id,
            name,
            categoryType
        );

    }



    sqlite3_finalize(stmt);


    return categories;

}






bool CategoryRepository::add(
    const Category& category
)
{


    const char* sql =
    R"(
    INSERT INTO category
    (
        id,
        name,
        type
    )
    VALUES
    (?,?);
    )";



    sqlite3_stmt* stmt;



    if(
        sqlite3_prepare_v2(
            db_.getConnection(),
            sql,
            -1,
            &stmt,
            nullptr
        )
        != SQLITE_OK
    )
    {

        Logger::error(
            "Failed to prepare insert category"
        );


        return false;
    }




    sqlite3_bind_text(
        stmt,
        1,
        category.getName().c_str(),
        -1,
        SQLITE_TRANSIENT
    );



    sqlite3_bind_int(
        stmt,
        2,
        category.getType()
    );



    bool success =
        sqlite3_step(stmt)
        == SQLITE_DONE;



    if(!success)
    {

        Logger::error(
            "Failed to insert category"
        );

    }



    sqlite3_finalize(stmt);



    return success;


}
