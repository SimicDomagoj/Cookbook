#pragma once

#include<string>
#include<vector>

class Recipe
{
public:
    Recipe();
    uint32_t id{0};
    std::string name;
    std::string description;
    uint32_t servings{0};
    uint32_t difficulty{1}; // TODO consider string as well
    uint32_t time{0};
    std::string imagePath;
    std::vector<std::string> categories;
    std::vector<std::string> ingredients;
    std::vector<std::string> steps;
    bool starred{false};
};
