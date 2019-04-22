#pragma once

#include"controllers/recipecontroller.h"
#include"views/listview.h"
#include"services/recipeservice.h"
#include"filters/recipefilter.h"
#include<memory>

class RecipeListController
{
public:
    RecipeListController();
    void show(RecipeFilter filter = RecipeFilter());
    void addRecipe();
    void deleteRecipe(uint32_t id);
    void handleStarredToggle(uint32_t id);
    void doReturn();
    void showRecipe(uint32_t recipeId);
    void refresh();
private:
    std::vector<ListInputViewModel> toViewModel(std::vector<Recipe> recipes);
    std::shared_ptr<ListView> listView;
    RecipeService service;
    RecipeController recipeController;
    RecipeFilter currentFilter;
};
