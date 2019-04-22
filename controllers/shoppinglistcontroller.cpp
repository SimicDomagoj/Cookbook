#include"controllers/shoppinglistcontroller.h"
#include"factories/viewfactory.h"

ShoppingListController::ShoppingListController()
{
    shoppingListView = ViewFactory().getShoppingListView(*this);
}

void ShoppingListController::show()
{
    shoppingListView->show();
}

void ShoppingListController::refresh()
{
    currentState = std::make_shared<ShoppingList>(service.get(1));
    std::vector<std::string> items = currentState->getItems();
    std::vector<std::string> ingredients = toViewModel(items);
    shoppingListView->setList(ingredients);
}

void ShoppingListController::add(const std::string &item)
{
    ShoppingList list = service.get(1);
    std::vector<std::string> items = list.getItems();
    items.push_back(item);
    list.setItems(items);
    service.update(list);
}

void ShoppingListController::save(std::vector<std::string> list)
{
    currentState->setItems(toModel(list));
    service.update(*currentState);
    disableEditing();
}

void ShoppingListController::enableEditing()
{
    shoppingListView->enableEditing();
}

void ShoppingListController::disableEditing()
{
    shoppingListView->disableEditing();
}

void ShoppingListController::cancelClicked()
{
    shoppingListView->disableEditing();
    std::vector<std::string> items = currentState->getItems();
    std::vector<std::string> ingredients = toViewModel(items);
    shoppingListView->setList(ingredients);
}

void ShoppingListController::handleReturnClicked()
{
    shoppingListView->close();
}

std::vector<std::string> ShoppingListController::toViewModel(std::vector<std::string>& ingredients)
{
    return ingredients;
}

std::vector<std::string> ShoppingListController::toModel(std::vector<std::string> &viewModel)
{
    return viewModel;
}

