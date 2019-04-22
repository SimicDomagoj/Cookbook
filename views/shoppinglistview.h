#pragma once

#include<vector>
#include<string>

class ShoppingListController;

class ShoppingListView
{
public:
    ShoppingListView(ShoppingListController& controller);
    virtual void show() = 0;
    virtual void setList(std::vector<std::string>& list) = 0;
    virtual void close() = 0;
    virtual void enableEditing() = 0;
    virtual void disableEditing() = 0;
    virtual ~ShoppingListView();
protected:
    ShoppingListController& controller;
};
