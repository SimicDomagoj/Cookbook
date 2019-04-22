#pragma once

#include"./filters/filter.h"
#include"models/recipe.h"
#include<string>
#include<vector>

class RecipeFilter : public Filter<Recipe>
{
public:
    RecipeFilter();
    bool filter(const Recipe& object) const override;
    std::string getName() const;
    void setName(const std::string &value);
    uint32_t getMinServings() const;
    void setMinServings(const uint32_t &value);
    uint32_t getMaxServings() const;
    void setMaxServings(const uint32_t &value);
    std::vector<uint32_t> getDifficulties() const;
    void setDifficulties(const std::vector<uint32_t> &value);
    uint32_t getMinTime() const;
    void setMinTime(const uint32_t &value);
    uint32_t getMaxTime() const;
    void setMaxTime(const uint32_t &value);
    std::string getCategory() const;
    void setCategory(const std::string &value);
    std::string getIngredient() const;
    void setIngredient(const std::string &value);
    bool isStarred() const;
    void setStarred(const bool &value);

protected:
    std::string name{ "" };
    uint32_t minServings{ 0 };
    uint32_t maxServings{ 999 };
    std::vector<uint32_t> difficulties{ };
    uint32_t minTime{ 0 };
    uint32_t maxTime{ 999 };
    std::string category{ "" };
    std::string ingredient{ "" };
    bool starred{ false };
};
