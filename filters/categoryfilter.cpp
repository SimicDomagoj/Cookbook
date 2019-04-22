#include "categoryfilter.h"

CategoryFilter::CategoryFilter() {}

bool CategoryFilter::filter(const Category &object) const
{
    if(id != 0 && object.id != id)
    {
        return false;
    }
    if(object.name.find(name) == std::string::npos)
    {
        return false;
    }
    return true;
}

uint32_t CategoryFilter::getId() const
{
    return id;
}

void CategoryFilter::setId(const uint32_t value)
{
    id = value;
}

std::string CategoryFilter::getName() const
{
    return name;
}

void CategoryFilter::setName(const std::string &value)
{
    name = value;
}
