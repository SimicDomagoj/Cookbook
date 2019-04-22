#include"recipefilter.h"
#include<algorithm>

RecipeFilter::RecipeFilter() {}

bool RecipeFilter::filter(const Recipe &object) const
{
    if(object.name.find(name) == std::string::npos)
    {
        return false;
    }
    if(category != "" && std::find_if(object.categories.begin(), object.categories.end(), [&] (const std::string& s) { return s.find(category) != std::string::npos; }) == object.categories.end())
    {
        return false;
    }
    if(object.time < minTime || object.time > maxTime)
    {
        return false;
    }
    if(object.servings < minServings || object.servings > maxServings)
    {
        return false;
    }
    if(difficulties.size() != 0 && std::find(difficulties.begin(), difficulties.end(), object.difficulty) != difficulties.end())
    {
        return false;
    }
    if(ingredient != "" && std::find_if(object.ingredients.begin(), object.ingredients.end(), [&] (const std::string& s) { return s.find(ingredient) != std::string::npos; }) == object.ingredients.end())
    {
        return false;
    }
    if(starred && !object.starred)
    {
        return false;
    }
    return true;
}

std::string RecipeFilter::getName() const
{
    return name;
}

void RecipeFilter::setName(const std::string &value)
{
    name = value;
}

uint32_t RecipeFilter::getMinServings() const
{
    return minServings;
}

void RecipeFilter::setMinServings(const uint32_t &value)
{
    minServings = value;
}

uint32_t RecipeFilter::getMaxServings() const
{
    return maxServings;
}

void RecipeFilter::setMaxServings(const uint32_t &value)
{
    maxServings = value;
}

std::vector<uint32_t> RecipeFilter::getDifficulties() const
{
    return difficulties;
}

void RecipeFilter::setDifficulties(const std::vector<uint32_t>& value)
{
    difficulties = value;
}

uint32_t RecipeFilter::getMinTime() const
{
    return minTime;
}

void RecipeFilter::setMinTime(const uint32_t &value)
{
    minTime = value;
}

uint32_t RecipeFilter::getMaxTime() const
{
    return maxTime;
}

void RecipeFilter::setMaxTime(const uint32_t &value)
{
    maxTime = value;
}

std::string RecipeFilter::getCategory() const
{
    return category;
}

void RecipeFilter::setCategory(const std::string &value)
{
    category = value;
}

std::string RecipeFilter::getIngredient() const
{
    return ingredient;
}

void RecipeFilter::setIngredient(const std::string &value)
{
    ingredient = value;
}

bool RecipeFilter::isStarred() const
{
    return starred;
}

void RecipeFilter::setStarred(const bool &value)
{
    starred = value;
}
