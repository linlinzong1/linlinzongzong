#pragma once

#include <string>

class Category
{

private:
    int id_;

    std::string name_;

    int type_;

public:

    Category(
        int id,

        const std::string& name,

        int type
    );
    int getId() const;

    std::string getName() const;

    int getType() const;

};