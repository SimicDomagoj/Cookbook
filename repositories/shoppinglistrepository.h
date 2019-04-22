#pragma once

#include"repositories/repository.h"
#include"models/shoppinglist.h"

class ShoppingListRepository : public Repository<ShoppingList>
{
public:
    ShoppingListRepository();
};
