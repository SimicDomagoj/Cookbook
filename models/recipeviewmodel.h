#pragma once

#include<string>
#include<vector>

class RecipeViewModel
{
public:
    RecipeViewModel();
    RecipeViewModel(uint32_t id);

    uint32_t id;
    std::string name;
    std::string description;
    uint32_t servings;
    uint32_t difficulty;
    uint32_t time;
    std::string imagePath;
    std::vector<std::string> categories;
    std::vector<std::string> ingredients;
    std::vector<std::string> steps;
    bool starred;
};
