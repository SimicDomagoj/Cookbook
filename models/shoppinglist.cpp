#include "shoppinglist.h"

ShoppingList::ShoppingList() {}

uint32_t ShoppingList::getId() const
{
    return id;
}

void ShoppingList::setId(const uint32_t value)
{
    id = value;
}

std::string ShoppingList::getName() const
{
    return name;
}

void ShoppingList::setName(const std::string& value)
{
    name = value;
}

std::vector<std::string> ShoppingList::getItems() const
{
    return items;
}

void ShoppingList::setItems(const std::vector<std::string>& value)
{
    items = value;
}
