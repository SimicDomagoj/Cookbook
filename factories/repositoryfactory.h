#pragma once

#include"repositories/repository.h"
#include<memory>

class RepositoryFactory
{
public:
    RepositoryFactory();
    template <typename T>
    std::shared_ptr<Repository<T>> getRepository() const;
};

