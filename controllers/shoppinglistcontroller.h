#pragma once
#include"services/shoppinglistservice.h"
#include"views/shoppinglistview.h"
#include<vector>
#include<string>

class ShoppingListController
{
public:
    ShoppingListController();
    void show();
    void refresh();
    void add(const std::string& item);
    void save(std::vector<std::string> list);
    void handleReturnClicked();
    void cancelClicked();
    void enableEditing();
    void disableEditing();
private:
    // TODO Actual class for view model
    std::vector<std::string> toViewModel(std::vector<std::string>& ingredients);
    std::vector<std::string> toModel(std::vector<std::string>& viewModel);
    std::shared_ptr<ShoppingList> currentState;
    std::shared_ptr<ShoppingListView> shoppingListView;
    ShoppingListService service;
};
