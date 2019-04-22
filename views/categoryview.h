#pragma once

#include"filters/qmlrecipefilter.h"
#include"models/qmlcategoryviewmodel.h"
#include<vector>

class CategoryController;

class CategoryView
{
public:
    CategoryView(CategoryController& controller);
    virtual void show() = 0;
    virtual void setCategories(const std::vector<CategoryViewModel>& categories) = 0;
    virtual void showMessage(const std::string& message) = 0;
    virtual ~CategoryView();
protected:
    CategoryController& controller;
};
