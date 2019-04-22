#pragma once

template <typename T>
class Filter
{
public:
    Filter();
    virtual ~Filter();
    virtual bool filter(const T& object) const = 0;
};

template <typename T>
Filter<T>::Filter() { }

template <typename T>
Filter<T>::~Filter() { }
