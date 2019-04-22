#pragma once

#include"repositories/categoryrepository.h"
#include"models/category.h"
#include"filters/categoryfilter.h"
#include<boost/filesystem.hpp>

class CategoryDiskRepository : public CategoryRepository
{
public:
    CategoryDiskRepository();
    virtual Category get(const uint32_t id) const override;
    virtual std::vector<Category> get(const Filter<Category>& filter = CategoryFilter()) const override;
    virtual Category getRandom(const Filter<Category>& filter = CategoryFilter()) const override;
    virtual void insert(Category& recipe) override;
    virtual void update(Category& recipe) override;
    virtual void remove(uint32_t id) override;
    virtual void remove(Category& recipe)override;
private:
    uint32_t getNextId();
    void filterCategories(std::vector<Category>& recipes, const Filter<Category>& filter) const;

    uint32_t lastId;
    const boost::filesystem::path dataFile;
};
