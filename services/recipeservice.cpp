#include"services/recipeservice.h"
#include"exceptions/serviceexception.h"

RecipeService::RecipeService() { }

Recipe RecipeService::get(uint32_t id) const
{
    return Service<Recipe>::get(id);
}

std::vector<Recipe> RecipeService::get(const Filter<Recipe>& filter) const
{
    return Service<Recipe>::get(filter);
}

Recipe RecipeService::getRandom(const Filter<Recipe>& filter) const
{
    return Service<Recipe>::getRandom(filter);
}

void RecipeService::verify(const Recipe &recipe) const
{
    for (const std::string& ingredient: recipe.ingredients) {
        if(ingredient == "")
        {
            throw ServiceException("Ingredient cannot be empty");
        }
    }
    for (const std::string& step: recipe.steps) {
        if(step == "")
        {
            throw ServiceException("Step cannot be empty");
        }
    }
}
