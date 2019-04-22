#pragma once

#include"controllers/recipelistcontroller.h"
#include"controllers/shoppinglistcontroller.h"
#include"controllers/recipecontroller.h"
#include"views/categoryview.h"
#include"services/categoryservice.h"
#include"services/recipeservice.h"
#include"models/categoryviewmodel.h"

class CategoryController
{
public:
    CategoryController();
    void show();
    void refresh();
    void showRecepies(RecipeFilter& filter);
    void handleRandomClicked(const RecipeFilter& filter);
    void handleShoppingListClicked();
private:
    std::vector<CategoryViewModel> toViewModel(std::vector<Category> categories) const;
    std::shared_ptr<CategoryView> categoryView;
    CategoryService service;
    RecipeService recipeService;
    RecipeListController listController;
    ShoppingListController shoppingListController;
    RecipeController recipeController;
};
