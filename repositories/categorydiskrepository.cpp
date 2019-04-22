#include"repositories/categorydiskrepository.h"
#include"exceptions/nodatafoundexception.h"
#include<boost/filesystem/fstream.hpp>

CategoryDiskRepository::CategoryDiskRepository() : lastId{ 0 }, dataFile{"data/categories.txt"}
{
    if(!boost::filesystem::exists(dataFile)){
        boost::filesystem::ofstream{dataFile};
    }
}
// TODO pass string from factory?

Category CategoryDiskRepository::get(uint32_t id) const
{
    CategoryFilter filter;
    filter.setId(id);
    std::vector<Category> categories = get(filter);
    // TODO if size != 1 throw exception
    return categories[0];
}

std::vector<Category> CategoryDiskRepository::get(const Filter<Category>& filter) const
{
    std::vector<Category> categories;
    boost::filesystem::ifstream iStream{ dataFile };
    std::string line;
    while(std::getline(iStream, line))
    {
        Category category;
        size_t delimiterIndex = line.find_first_of(':');
        category.id = std::stoul(line.substr(0, delimiterIndex));
        std::string categorySecondPart = line.substr(delimiterIndex + 1, line.size() - 1 - delimiterIndex);
        delimiterIndex = categorySecondPart.find_first_of(':');
        category.name = categorySecondPart.substr(0, delimiterIndex);
        category.imagePath = categorySecondPart.substr(delimiterIndex + 1, categorySecondPart.size() - 1 - delimiterIndex);
        categories.push_back(category);
    }
    filterCategories(categories, filter);
    return categories;
}

Category CategoryDiskRepository::getRandom(const Filter<Category>& filter) const
{
    std::vector<Category> categories = get(filter);
    if(categories.size() > 0)
    {
        std::uniform_int_distribution<size_t> distribution(0, categories.size() - 1);
        return categories[distribution(mtNumberGenerator)];
    }
    else
    {
        throw NoDataFoundException("No data for the given filter found"); //TODO probably print filter as well
    }
}

void CategoryDiskRepository::insert(Category& category)
{
    category.id = getNextId();
    boost::filesystem::ofstream oStream{dataFile, std::ios::out | std::ios::app}; // TODO probably separate function
    oStream << category.id << ":" << category.name << ":" << category.imagePath << std::endl;
}

void CategoryDiskRepository::update(Category &category)
{
    std::vector<Category> categories = get();
    boost::filesystem::ofstream oStream{ dataFile }; // TODO probably separate function
    for(const Category& c: categories)
    {
        if(category.id == c.id)
        {
            oStream << category.id << ":" << category.name << ":" << category.imagePath << std::endl;
        }
        else
        {
            oStream << c.id << ":" << c.name << ":" << c.imagePath << std::endl;
        }
    }
}

void CategoryDiskRepository::remove(uint32_t id)
{
    std::vector<Category> categories = get();
    boost::filesystem::ofstream oStream{dataFile}; // TODO probably separate function
    for(const Category& category: categories)
    {
        if(category.id != id)
        {
            oStream << category.id << ":" << category.name << ":" << category.imagePath << std::endl;
        }
    }
}

void CategoryDiskRepository::remove(Category& category)
{
    remove(category.id);
}

uint32_t CategoryDiskRepository::getNextId()
{
    return ++lastId;
}

void CategoryDiskRepository::filterCategories(std::vector<Category>& recipes, const Filter<Category>& filter) const
{
    std::vector<Category>::iterator first_removed = std::remove_if(recipes.begin(),
                                                                 recipes.end(),
                                                                 [&filter](Category& r){ return !filter.filter(r); });
    recipes.erase(first_removed, recipes.end());
}
