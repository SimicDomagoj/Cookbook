#pragma once

#include"models/listinputviewmodel.h"
#include<vector>

class RecipeListController;

class ListView
{
public:
    ListView(RecipeListController& controller);
    virtual void show() = 0;
    virtual void setList(std::vector<ListInputViewModel> list) = 0;
    virtual void close() = 0;
    virtual ~ListView();
protected:
    RecipeListController& controller;
};
