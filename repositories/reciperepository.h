#pragma once

#include"repositories/repository.h"
#include"models/recipe.h"

class RecipeRepository : public Repository<Recipe>
{
public:
    RecipeRepository();
};
