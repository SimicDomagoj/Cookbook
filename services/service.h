#pragma once

#include"factories/repositoryfactory.h"

template <typename T>
class Service
{
public:
    Service();
    virtual ~Service();
    virtual T get(const uint32_t id) const;
    virtual std::vector<T> get(const Filter<T>& filter = Filter<T>()) const;
    virtual T getRandom(const Filter<T>& filter = Filter<T>()) const;
    virtual void insert(T& object);
    virtual void update(T& object);
    virtual void remove(uint32_t id);
    virtual void remove(T& object);
protected:
    virtual void verify(const T&) const;

    std::shared_ptr<Repository<T>> repository;
};

template <typename T>
Service<T>::Service()
{
    repository = RepositoryFactory().getRepository<T>();
}

template <typename T>
Service<T>::~Service() { }

template <typename T>
T Service<T>::get(const uint32_t id) const
{
    return repository->get(id);
}

template <typename T>
std::vector<T> Service<T>::get(const Filter<T>& filter) const
{
    return repository->get(filter);
}

template <typename T>
T Service<T>::getRandom(const Filter<T>& filter) const
{
    return repository->getRandom(filter);
}

template <typename T>
void Service<T>::insert(T& object)
{
    verify(object);
    repository->insert(object);
}

template <typename T>
void Service<T>::update(T& object)
{
    verify(object);
    repository->update(object);
}

template <typename T>
void Service<T>::remove(uint32_t id)
{
    repository->remove(id);
}

template <typename T>
void Service<T>::remove(T& object)
{
    repository->remove(object);
}

template <typename T>
void Service<T>::verify(const T&) const {}
