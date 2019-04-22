#include"repositories/recipediskrepository.h"
#include"exceptions/nodatafoundexception.h"

RecipeDiskRepository::RecipeDiskRepository() : lastId{ 0 }, dataPath{ "data/recipes/" }
{
    if(!boost::filesystem::exists(dataPath)){
        boost::filesystem::create_directories(dataPath);
    }
    for(boost::filesystem::directory_entry& file : boost::filesystem::directory_iterator( dataPath ))
    {
        uint32_t id = getIdFromFile(file);
        if(id > lastId)
        {
            lastId = id;
        }
    }
}

Recipe RecipeDiskRepository::get(uint32_t id) const
{
    boost::filesystem::directory_entry file = getFileFromId(id);
    return rcpReader.decode(file);
}

std::vector<Recipe> RecipeDiskRepository::get(const Filter<Recipe>& filter) const
{
    std::vector<Recipe> recipes;
    for(boost::filesystem::directory_entry& file : boost::filesystem::directory_iterator( dataPath ))
    {
        recipes.push_back(rcpReader.decode(file));
    }
    applyFilter(recipes, filter);
    return recipes;
}

Recipe RecipeDiskRepository::getRandom(const Filter<Recipe>& filter) const
{
    std::vector<Recipe> recipes = get(filter);
    if(recipes.size() > 0)
    {
        std::uniform_int_distribution<size_t> distribution(0, recipes.size() - 1);
        return recipes[distribution(mtNumberGenerator)];
    }
    else
    {
        throw NoDataFoundException("No data for the given filter found"); //TODO probably print filter as well
    }
}

void RecipeDiskRepository::insert(Recipe &recipe)
{
    recipe.id = getNextId();
    std::string filename = constructFileName(recipe);
    boost::filesystem::path recipePath{filename};
    rcpReader.encode(recipePath, recipe);
}

void RecipeDiskRepository::update(Recipe &recipe)
{
    boost::filesystem::path recipePath = getFileFromId(recipe.id); // TODO error handling
    boost::filesystem::remove(recipePath);
    rcpReader.encode(recipePath, recipe);
}

void RecipeDiskRepository::remove(uint32_t id)
{
    boost::filesystem::directory_entry file = getFileFromId(id);
    boost::filesystem::remove(file);
}

void RecipeDiskRepository::remove(Recipe& recipe)
{
    remove(recipe.id);
}

uint32_t RecipeDiskRepository::getNextId()
{
    return ++lastId;
}

void RecipeDiskRepository::applyFilter(std::vector<Recipe>& recipes, const Filter<Recipe>& filter) const
{
    std::vector<Recipe>::iterator first_removed = std::remove_if(recipes.begin(),
                                                                 recipes.end(),
                                                                 [&filter](Recipe& r){ return !filter.filter(r); });
    recipes.erase(first_removed, recipes.end());
}

std::string RecipeDiskRepository::getFileName(const boost::filesystem::directory_entry &file) const
{
    return file.path().filename().string();
}

uint32_t RecipeDiskRepository::getIdFromFile(const boost::filesystem::directory_entry& file) const
{
    std::string filename = getFileName(file);
    std::size_t underscoreIndex = filename.find_first_of('_');
    std::string id = filename.substr(0, underscoreIndex);
    return static_cast<uint32_t>(std::stoi(id));
}

boost::filesystem::directory_entry RecipeDiskRepository::getFileFromId(const uint32_t id) const
{
    for(boost::filesystem::directory_entry& file : boost::filesystem::directory_iterator( dataPath ))
    {
        std::string filename = getFileName(file);
        if(startsWith(filename, std::to_string(id) + "_"))
        {
            return file;
        }
    }
    // TODO exception if not there
}

bool RecipeDiskRepository::startsWith(const std::string& s, const std::string& w) const
{
    return s.find(w) == 0;
}

std::string RecipeDiskRepository::constructFileName(const Recipe& recipe) const
{
    return dataPath.string() + std::to_string(recipe.id) + "_" + recipe.name + ".rcp";
}
