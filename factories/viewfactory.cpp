#include"factories/viewfactory.h"
#include"views/qmlcategoryview.h"
#include"views/qmllistview.h"
#include"views/qmlrecipeview.h"
#include"views/qmlshoppinglistview.h"

ViewFactory::ViewFactory(){}

ViewFactory::~ViewFactory(){}

std::shared_ptr<CategoryView> ViewFactory::getCategoryView(CategoryController& controller) const
{
    return std::make_shared<QmlCategoryView>(controller);
}

std::shared_ptr<ListView> ViewFactory::getListView(RecipeListController& controller) const
{
    return std::make_shared<QmlListView>(controller);
}

std::shared_ptr<RecipeView> ViewFactory::getRecipeView(RecipeController& controller) const
{
    return std::make_shared<QmlRecipeView>(controller);
}

std::shared_ptr<ShoppingListView> ViewFactory::getShoppingListView(ShoppingListController& controller) const
{
    return std::make_shared<QmlShoppingListView>(controller);
}
