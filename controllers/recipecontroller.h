#pragma once

#include"shoppinglistcontroller.h"
#include"views/recipeview.h"
#include"services/recipeservice.h"
#include<memory>

class RecipeListController;

class RecipeController
{
public:
    RecipeController();
    void show(uint32_t recipeId);
    void save(RecipeViewModel& viewModel);
    void remove(RecipeViewModel& viewModel);
    void cancelClicked();
    void enableEditing();
    void disableEditing();
    void addRecipe();
    void doReturn();
    void refresh();
    void addToShoppingList(const std::string& item);
private:
    RecipeViewModel toViewModel(Recipe& recipe);
    Recipe toModel(RecipeViewModel& viewModel);

    std::shared_ptr<Recipe> currentState;
    std::shared_ptr<RecipeView> recipeView;
    RecipeService service;
    ShoppingListController shoppingListController;
};
