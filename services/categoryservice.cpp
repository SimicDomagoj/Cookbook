#include"services/categoryservice.h"

CategoryService::CategoryService() {}

Category CategoryService::get(uint32_t id) const
{
    return Service<Category>::get(id);
}

std::vector<Category> CategoryService::get(const Filter<Category>& filter) const
{
    return Service<Category>::get(filter);
}

Category CategoryService::getRandom(const Filter<Category>& filter) const
{
    return Service<Category>::getRandom(filter);
}
