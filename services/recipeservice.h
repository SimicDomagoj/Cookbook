#pragma once

#include"services/service.h"
#include"models/recipe.h"
#include"filters/recipefilter.h"

class RecipeService : public Service<Recipe>
{
public:
    RecipeService();
    Recipe get(uint32_t id) const override;
    std::vector<Recipe> get(const Filter<Recipe>& filter = RecipeFilter()) const override;
    Recipe getRandom(const Filter<Recipe>& filter = RecipeFilter()) const override;
protected:
    void verify(const Recipe& recipe) const override;
};
