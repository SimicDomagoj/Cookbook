#include"factories/repositoryfactory.h"
#include"repositories/recipediskrepository.h"
#include"repositories/categorydiskrepository.h"
#include"repositories/shoppinglistdiskrepository.h"

RepositoryFactory::RepositoryFactory() { }

template <>
std::shared_ptr<Repository<ShoppingList>> RepositoryFactory::getRepository<ShoppingList>() const
{
    return std::make_shared<ShoppingListDiskRepository>(ShoppingListDiskRepository());
}

template <>
std::shared_ptr<Repository<Category>> RepositoryFactory::getRepository<Category>() const
{
    return std::make_shared<CategoryDiskRepository>(CategoryDiskRepository{});
}

template <>
std::shared_ptr<Repository<Recipe>> RepositoryFactory::getRepository<Recipe>() const
{
    return std::make_shared<RecipeDiskRepository>(RecipeDiskRepository{});
}
