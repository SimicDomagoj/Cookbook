#pragma once

#include"filters/filter.h"
#include<vector>
#include<random>
#include<ctime>

template <typename T>
class Repository
{
public:
    Repository() : mtNumberGenerator{ static_cast<uint32_t>(time(nullptr)) } {}
    virtual std::vector<T> get(const Filter<T>& filter = Filter<T>()) const = 0;
    virtual T getRandom(const Filter<T>& filter = Filter<T>()) const = 0;
    virtual T get(uint32_t id) const = 0;
    virtual void insert(T& recipe) = 0;
    virtual void update(T& recipe) = 0;
    virtual void remove(T& recipe) = 0;
    virtual void remove(uint32_t id) = 0;
    virtual ~Repository(){}
protected:
    mutable std::mt19937 mtNumberGenerator;
};

