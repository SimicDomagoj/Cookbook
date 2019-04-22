#pragma once

#include"models/recipeviewmodel.h"

class RecipeController;

class RecipeView
{
public:
    RecipeView(RecipeController& controller);
    virtual void show() = 0;
    virtual void setRecipe(RecipeViewModel& recipe) = 0;
    virtual void close() = 0;
    virtual void enableEditing() = 0;
    virtual void disableEditing() = 0;
    virtual void showErrorMessage(const std::string& message) const = 0;
    virtual ~RecipeView();
protected:
    RecipeController& controller;
};
