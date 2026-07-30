#include "model/Category.h"

Category::Category(
    int id,
    const std::string& name,
    int type
)
:
id_(id),
name_(name),
type_(type)
{

}
int Category::getId() const
{
    return id_;
}

std::string Category::getName() const
{
    return name_;
}

int Category::getType() const
{
    return type_;
}
