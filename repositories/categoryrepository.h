#pragma once

#include"repositories/repository.h"
#include"models/category.h"

class CategoryRepository : public Repository<Category>
{
public:
    CategoryRepository();
};
