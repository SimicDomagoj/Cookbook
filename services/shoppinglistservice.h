#pragma once

#include"services/service.h"
#include"models/shoppinglist.h"
#include"filters/shoppinglistfilter.h"

class ShoppingListService : public Service<ShoppingList>
{
public:
    ShoppingListService();
    ShoppingList get(uint32_t id) const override;
    std::vector<ShoppingList> get(const Filter<ShoppingList>& filter = ShoppingListFilter()) const override;
    ShoppingList getRandom(const Filter<ShoppingList>& filter = ShoppingListFilter()) const override;
};

