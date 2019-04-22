#include"repositories/reciperepository.h"
#include"filters/recipefilter.h"
#include"rcpreader.h"
#include<boost/filesystem.hpp>

class RecipeDiskRepository : public RecipeRepository
{
public:
    RecipeDiskRepository();
    virtual Recipe get(const uint32_t id) const override;
    virtual std::vector<Recipe> get(const Filter<Recipe>& filter = RecipeFilter()) const override;
    virtual Recipe getRandom(const Filter<Recipe>& filter = RecipeFilter()) const override;
    virtual void insert(Recipe& recipe) override;
    virtual void update(Recipe& recipe) override;
    virtual void remove(uint32_t id) override;
    virtual void remove(Recipe& recipe)override;
private:
    uint32_t getNextId();
    void applyFilter(std::vector<Recipe>& recipes, const Filter<Recipe>& filter) const;
    std::string getFileName(const boost::filesystem::directory_entry& file) const;
    uint32_t getIdFromFile(const boost::filesystem::directory_entry& file) const;
    boost::filesystem::directory_entry getFileFromId(const uint32_t id) const;
    bool startsWith(const std::string& s, const std::string& w) const;
    std::string constructFileName(const Recipe& recipe) const;

    uint32_t lastId;
    boost::filesystem::path dataPath;
    RcpReader rcpReader;
};
