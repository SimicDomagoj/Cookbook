#pragma once

#include"services/service.h"
#include"models/category.h"
#include"filters/categoryfilter.h"

class CategoryService : public Service<Category>
{
public:
    CategoryService();
    Category get(uint32_t id) const override;
    std::vector<Category> get(const Filter<Category>& filter = CategoryFilter()) const override;
    Category getRandom(const Filter<Category>& filter = CategoryFilter()) const override;
};
