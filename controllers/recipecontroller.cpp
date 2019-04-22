#include"controllers/recipecontroller.h"
#include"factories/viewfactory.h"
#include"exceptions/serviceexception.h"
#include"models/qmlrecipeviewmodel.h"
#include"cookbookapp.h"

RecipeController::RecipeController() : service{}
{
    recipeView = ViewFactory().getRecipeView(*this);
    shoppingListController = ShoppingListController();
    currentState = nullptr;
}

void RecipeController::show(uint32_t recipeId)
{
    currentState = std::make_shared<Recipe>();
    currentState->id = recipeId;
    recipeView->show();
}

void RecipeController::refresh()
{
    if(currentState != nullptr)
    {
        currentState = std::make_shared<Recipe>(service.get(currentState->id));
    }
    else
    {
        currentState = std::make_shared<Recipe>();
    }
    RecipeViewModel viewModel = toViewModel(*currentState);
    recipeView->setRecipe(viewModel);
}

void RecipeController::save(RecipeViewModel& viewModel)
{
    Recipe recipe = toModel(viewModel);
    try {
        if(recipe.id == 0)
        {
            service.insert(recipe);
            currentState = std::make_shared<Recipe>(recipe); // TODO if Recipe becomes a pointer, this shouldn't be neccessary
            disableEditing();
            refresh(); // TODO refresh logic can be improved on qml side
        }
        else
        {
            service.update(recipe);
            disableEditing();
        }
    }
    catch (const ServiceException& e)
    {
        recipeView->showErrorMessage(e.what());
    }
}

void RecipeController::remove(RecipeViewModel& viewModel)
{
    Recipe recipe = toModel(viewModel);
    service.remove(recipe);
    doReturn();
}

void RecipeController::enableEditing()
{
    recipeView->enableEditing();
}

void RecipeController::disableEditing()
{
    recipeView->disableEditing();
}

void RecipeController::cancelClicked()
{
    if(currentState == nullptr || currentState->id == 0)
    {
        doReturn();
    }
    else
    {
        recipeView->disableEditing();
        RecipeViewModel viewModel = toViewModel(*currentState);
        recipeView->setRecipe(viewModel);
    }
}

void RecipeController::addRecipe()
{
    currentState = nullptr;
    recipeView->show();
    Recipe recipe{};
    RecipeViewModel viewModel = toViewModel(recipe);
    recipeView->setRecipe(viewModel);
    enableEditing();
}

void RecipeController::doReturn()
{
    recipeView->close();
}

void RecipeController::addToShoppingList(const std::string &item)
{
    shoppingListController.add(item);
}

RecipeViewModel RecipeController::toViewModel(Recipe& recipe)
{
    RecipeViewModel viewModel{recipe.id};
    viewModel.name = recipe.name;
    viewModel.description = recipe.description;
    viewModel.servings = recipe.servings;
    viewModel.difficulty = recipe.difficulty;
    viewModel.time = recipe.time;
    viewModel.imagePath = recipe.imagePath;
    viewModel.starred = recipe.starred;
    viewModel.categories = recipe.categories;
    viewModel.steps = recipe.steps;
    viewModel.ingredients = recipe.ingredients;
    return viewModel;
}

Recipe RecipeController::toModel(RecipeViewModel& viewModel)
{
    Recipe model{};
    model.id = viewModel.id;
    model.name = viewModel.name;
    model.description = viewModel.description;
    model.servings = viewModel.servings;
    model.difficulty = viewModel.difficulty;
    model.time = viewModel.time;
    model.imagePath = viewModel.imagePath;
    model.starred = viewModel.starred;
    model.categories = viewModel.categories;
    model.steps = viewModel.steps;
    model.ingredients = viewModel.ingredients;
    return model;
}
