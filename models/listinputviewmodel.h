#pragma once

#include<string>

class ListInputViewModel
{
public:
    ListInputViewModel(){}
    ListInputViewModel(uint32_t id, std::string name, std::string imgPath, bool starred) :
        id{id}, name{name}, imagePath{imgPath}, starred{starred}{}

    uint32_t id;
    std::string name;
    std::string imagePath;
    bool starred;
};

