#include"controllers/categorycontroller.h"
#include"controllers/recipecontroller.h"
#include"models/category.h"
#include"factories/viewfactory.h"
#include"exceptions/nodatafoundexception.h"

CategoryController::CategoryController() : service{}, listController{}, shoppingListController{}, recipeController{}
{
    categoryView = ViewFactory().getCategoryView(*this);
}

void CategoryController::show()
{
    categoryView->show();
}

void CategoryController::refresh()
{
    std::vector<Category> categories = service.get();
    std::vector<CategoryViewModel> viewCategories = toViewModel(categories);
    categoryView->setCategories(viewCategories);
}

void CategoryController::showRecepies(RecipeFilter& filter)
{
    listController.show(filter);
}

void CategoryController::handleRandomClicked(const RecipeFilter &filter)
{
    try
    {
        Recipe recipe = recipeService.getRandom(filter);
        recipeController.show(recipe.id);
    }
    catch (NoDataFoundException&)
    {
        categoryView->showMessage("No recipes found for the given filter!");
    }
}

void CategoryController::handleShoppingListClicked()
{
    shoppingListController.show();
}

std::vector<CategoryViewModel> CategoryController::toViewModel(std::vector<Category> categories) const
{
    std::vector<CategoryViewModel> viewCategories{};
    for(const Category& category: categories){
        CategoryViewModel viewModel;
        viewModel.name = category.name;
        viewModel.imagePath = category.imagePath;
        viewCategories.push_back(viewModel);
    }
    return viewCategories;
}

