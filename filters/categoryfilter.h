#pragma once

#include"filters/filter.h"
#include"models/category.h"
#include<string>

class CategoryFilter : public Filter<Category>
{
public:
    CategoryFilter();
    bool filter(const Category& object) const override;
    uint32_t getId() const;
    void setId(const uint32_t value);
    std::string getName() const;
    void setName(const std::string &value);
protected:
    uint32_t id{ 0 };
    std::string name{ "" };
};
