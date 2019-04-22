#include"repositories/shoppinglistdiskrepository.h"
#include"exceptions/nodatafoundexception.h"

ShoppingListDiskRepository::ShoppingListDiskRepository() : lastId{ 0 }, dataPath{"data/shopping_lists"}
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

ShoppingList ShoppingListDiskRepository::get(uint32_t id) const
{
    ShoppingListFilter filter;
    filter.setId(id);
    std::vector<ShoppingList> lists = get(filter);
    // TODO if size != 1 throw exception
    return lists[0];
}

std::vector<ShoppingList> ShoppingListDiskRepository::get(const Filter<ShoppingList>& filter) const
{
    std::vector<ShoppingList> lists;
    for(boost::filesystem::directory_entry& file : boost::filesystem::directory_iterator( dataPath ))
    {
        ShoppingList list; // TODO separate class or atleast encode method
        std::string filename = getFileName(file);
        size_t delimiterIndex = filename.find_first_of('_');
        list.setId(std::stoul(filename.substr(0, delimiterIndex)));
        list.setName(filename.substr(delimiterIndex + 1, filename.size() - 1 - delimiterIndex));
        boost::filesystem::ifstream iStream{ file };
        std::string line;
        std::vector<std::string> items;
        while(std::getline(iStream, line))
        {
            items.push_back(line);
        }
        list.setItems(items);
        lists.push_back(list);
    }
    applyFilter(lists, filter);
    return lists;
}

ShoppingList ShoppingListDiskRepository::getRandom(const Filter<ShoppingList>& filter) const
{
    std::vector<ShoppingList> lists = get(filter);
    if(lists.size() > 0)
    {
        std::uniform_int_distribution<size_t> distribution(0, lists.size() - 1);
        return lists[distribution(mtNumberGenerator)];
    }
    else
    {
        throw NoDataFoundException("No data for the given filter found"); //TODO probably print filter as well
    }
}

void ShoppingListDiskRepository::insert(ShoppingList& list)
{    
    list.setId(getNextId());
    std::string filename = constructFileName(list);
    boost::filesystem::path listPath{ filename };
    boost::filesystem::ofstream oStream{ listPath };
    for(const std::string& item: list.getItems()){
        oStream << item << std::endl;
    }
}

void ShoppingListDiskRepository::update(ShoppingList& list)
{
    boost::filesystem::path listPath = getFileFromId(list.getId()); // TODO error handling
    boost::filesystem::ofstream oStream{ listPath };
    for(const std::string& item: list.getItems())
    {
        oStream << item << std::endl;
    }
}

void ShoppingListDiskRepository::remove(uint32_t id)
{
    boost::filesystem::directory_entry file = getFileFromId(id);
    boost::filesystem::remove(file);
}

void ShoppingListDiskRepository::remove(ShoppingList& list)
{
    remove(list.getId());
}

uint32_t ShoppingListDiskRepository::getNextId()
{
    return ++lastId;
}

void ShoppingListDiskRepository::applyFilter(std::vector<ShoppingList>& recipes, const Filter<ShoppingList>& filter) const
{
    std::vector<ShoppingList>::iterator first_removed = std::remove_if(recipes.begin(),
                                                                 recipes.end(),
                                                                 [&filter](ShoppingList& l){ return !filter.filter(l); });
    recipes.erase(first_removed, recipes.end());
}

std::string ShoppingListDiskRepository::getFileName(const boost::filesystem::directory_entry &file) const
{
    return file.path().filename().string();
}

uint32_t ShoppingListDiskRepository::getIdFromFile(const boost::filesystem::directory_entry& file) const
{
    std::string filename = getFileName(file);
    std::size_t underscoreIndex = filename.find_first_of('_');
    std::string id = filename.substr(0, underscoreIndex);
    return static_cast<uint32_t>(std::stoi(id));
}

boost::filesystem::directory_entry ShoppingListDiskRepository::getFileFromId(const uint32_t id) const
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

bool ShoppingListDiskRepository::startsWith(const std::string& s, const std::string& w) const
{
    return s.find(w) == 0;
}

std::string ShoppingListDiskRepository::constructFileName(const ShoppingList& list) const
{
    return dataPath.string() + std::to_string(list.getId()) + "_" + list.getName() + ".rcp";
}
