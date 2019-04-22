#include"controllers/recipelistcontroller.h"
#include"factories/viewfactory.h"

RecipeListController::RecipeListController()
    : service{}, recipeController{}
{
    listView = ViewFactory().getListView(*this);
}

void RecipeListController::show(RecipeFilter filter)
{
    currentFilter = filter;
    listView->show();
    refresh();
}

void RecipeListController::addRecipe()
{
    recipeController.addRecipe();
}

void RecipeListController::deleteRecipe(uint32_t id)
{
    service.remove(id);
    refresh();
}

void RecipeListController::handleStarredToggle(uint32_t id)
{
    Recipe recipe = service.get(id);
    recipe.starred = !recipe.starred;
    service.update(recipe);
    refresh();
}

void RecipeListController::doReturn()
{
    listView->close();
}

void RecipeListController::refresh()
{
    std::vector<Recipe> recipes = service.get(currentFilter);
    std::vector<ListInputViewModel> viewModel = toViewModel(recipes);
    listView->setList(viewModel);
}

void RecipeListController::showRecipe(uint32_t recipeId)
{
    recipeController.show(recipeId);
}

std::vector<ListInputViewModel> RecipeListController::toViewModel(std::vector<Recipe> recipes)
{
    std::vector<ListInputViewModel> viewModelList{};
    for(Recipe& recipe: recipes)
    {
        ListInputViewModel viewModel{recipe.id,
                                     recipe.name,
                                     recipe.imagePath,
                                     recipe.starred};
        viewModelList.push_back(viewModel);
    }
    return viewModelList;
}
