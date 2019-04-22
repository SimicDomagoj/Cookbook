#include"shoppinglistfilter.h"
#include<algorithm>

ShoppingListFilter::ShoppingListFilter() {}

bool ShoppingListFilter::filter(const ShoppingList &object) const
{
    std::vector<std::string> items = object.getItems();
    if(id != 0 && object.getId() != id)
    {
        return false;
    }
    if(item != "" && std::find_if(items.begin(), items.end(), [&] (const std::string& s) { return s.find(item) != std::string::npos; }) == items.end())
    {
        return false;
    }
    return true;
}

uint32_t ShoppingListFilter::getId() const
{
    return id;
}

void ShoppingListFilter::setId(const uint32_t value)
{
    id = value;
}

std::string ShoppingListFilter::getItem() const
{
    return item;
}

void ShoppingListFilter::setItem(const std::string &value)
{
    item = value;
}
