#include"services/shoppinglistservice.h"

ShoppingListService::ShoppingListService() {}

ShoppingList ShoppingListService::get(uint32_t id) const
{
    return Service<ShoppingList>::get(id);
}

std::vector<ShoppingList> ShoppingListService::get(const Filter<ShoppingList>& filter) const
{
    return Service<ShoppingList>::get(filter);
}

ShoppingList ShoppingListService::getRandom(const Filter<ShoppingList>& filter) const
{
    return Service<ShoppingList>::getRandom(filter);
}
