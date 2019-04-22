#pragma once

#include<vector>
#include<string>

class ShoppingList
{
public:
    ShoppingList();
    uint32_t getId() const;
    void setId(const uint32_t value);
    std::string getName() const;
    void setName(const std::string& value);
    std::vector<std::string> getItems() const;
    void setItems(const std::vector<std::string>& value);
protected:
    uint32_t id{ 0 };
    std::string name{ "" };
    std::vector<std::string> items{ };
};
