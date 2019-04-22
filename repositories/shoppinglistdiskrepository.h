#pragma once
#include"repositories/shoppinglistrepository.h"
#include"filters/shoppinglistfilter.h"
#include<boost/filesystem.hpp>

class ShoppingListDiskRepository : public ShoppingListRepository
{
public:
    ShoppingListDiskRepository();
    virtual ShoppingList get(const uint32_t id) const override;
    virtual std::vector<ShoppingList> get(const Filter<ShoppingList>& filter = ShoppingListFilter()) const override;
    virtual ShoppingList getRandom(const Filter<ShoppingList>& filter = ShoppingListFilter()) const override;
    virtual void insert(ShoppingList& recipe) override;
    virtual void update(ShoppingList& recipe) override;
    virtual void remove(uint32_t id) override;
    virtual void remove(ShoppingList& recipe)override;
private:
    uint32_t getNextId();
    void applyFilter(std::vector<ShoppingList>& recipes, const Filter<ShoppingList>& filter) const;
    std::string getFileName(const boost::filesystem::directory_entry& file) const;
    uint32_t getIdFromFile(const boost::filesystem::directory_entry& file) const;
    boost::filesystem::directory_entry getFileFromId(const uint32_t id) const;
    bool startsWith(const std::string& s, const std::string& w) const;
    std::string constructFileName(const ShoppingList& recipe) const;

    uint32_t lastId;
    const boost::filesystem::path dataPath;
};
