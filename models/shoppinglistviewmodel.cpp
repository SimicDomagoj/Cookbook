#include "shoppinglistviewmodel.h"

ShoppingListViewModel::ShoppingListViewModel() {}

uint32_t ShoppingListViewModel::getId() const
{
    return id;
}

void ShoppingListViewModel::setId(const uint32_t value)
{
    id = value;
}

std::string ShoppingListViewModel::getName() const
{
    return name;
}

void ShoppingListViewModel::setName(const std::string& value)
{
    name = value;
}

std::vector<std::string> ShoppingListViewModel::getItems() const
{
    return items;
}

void ShoppingListViewModel::setItems(const std::vector<std::string>& value)
{
    items = value;
}
