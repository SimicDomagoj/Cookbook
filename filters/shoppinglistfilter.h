#pragma once

#include"filters/filter.h"
#include"models/shoppinglist.h"
#include<string>
#include<vector>

class ShoppingListFilter : public Filter<ShoppingList>
{
public:
    ShoppingListFilter();
    bool filter(const ShoppingList& object) const override;
    uint32_t getId() const;
    void setId(const uint32_t value);
    std::string getItem() const;
    void setItem(const std::string &value);
protected:
    uint32_t id{ 0 };
    std::string item{ "" };
};
