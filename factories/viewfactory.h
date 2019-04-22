#pragma once
#include<memory>

class CategoryView;
class CategoryController;
class ListView;
class RecipeListController;
class RecipeView;
class RecipeController;
class ShoppingListView;
class ShoppingListController;

class ViewFactory
{
public:
    ViewFactory();
    virtual ~ViewFactory();
    virtual std::shared_ptr<CategoryView> getCategoryView(CategoryController& controller) const;
    virtual std::shared_ptr<ListView> getListView(RecipeListController& controller) const;
    virtual std::shared_ptr<RecipeView> getRecipeView(RecipeController& controller) const;
    virtual std::shared_ptr<ShoppingListView> getShoppingListView(ShoppingListController& controller) const;
};
