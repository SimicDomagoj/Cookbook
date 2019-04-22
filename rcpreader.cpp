#include"rcpreader.h"
#include"exceptions/invalidformatexception.h"

RcpReader::RcpReader() { }

Recipe RcpReader::decode(const boost::filesystem::path& file) const
{
    recipe = Recipe{};
    std::string line;
    boost::filesystem::ifstream iStream{file};
    while(std::getline(iStream, line))
    {
        if(line == "[id]") { decodeId(iStream); }
        else if(line == "[starred]") { decodeStarred(iStream); }
        else if(line == "[name]") { decodeName(iStream); }
        else if(line == "[category]") { decodeCategory(iStream); }
        else if(line == "[description]") { decodeDescription(iStream); }
        else if(line == "[servings]") { decodeServings(iStream); }
        else if(line == "[difficulty]") { decodeDifficulty(iStream); }
        else if(line == "[time]") { decodeTime(iStream); }
        else if(line == "[image]") { decodeImage(iStream); }
        else if(line == "[ingredients]") { decodeIngredients(iStream); }
        else if(line == "[steps]") { decodeSteps(iStream); }
        else{ throw InvalidFormatException(""); }
        verifyEndOfBlock(iStream);
    }
    return recipe;
}

void RcpReader::decodeId(boost::filesystem::ifstream &iStream) const
{
    std::string line;
    std::getline(iStream, line);
    try {
        recipe.id = std::stoul(line);
    }
    catch (std::invalid_argument) {
        throw InvalidFormatException("Couldn't convert Id to integer");
    }
}

void RcpReader::verifyEndOfBlock(boost::filesystem::ifstream &iStream) const
{
    std::string line;
    std::getline(iStream, line);
    if (line != "") {
        throw InvalidFormatException("Expected empty line after end of block");
    }
}

void RcpReader::decodeStarred(boost::filesystem::ifstream&) const
{
    recipe.starred = true;
}

void RcpReader::decodeName(boost::filesystem::ifstream &iStream) const
{
    std::getline(iStream, recipe.name);
}

void RcpReader::decodeCategory(boost::filesystem::ifstream &iStream) const
{    
    std::string line;
    while (std::getline(iStream, line) && line != "[category]")
    {
        if (line == "") {
            throw InvalidFormatException("Found empty line instead of the category");
        }
        recipe.categories.push_back(line);
    }
}

void RcpReader::decodeDescription(boost::filesystem::ifstream &iStream) const
{
    std::getline(iStream, recipe.description);
}

void RcpReader::decodeServings(boost::filesystem::ifstream &iStream) const
{
    std::string line;
    std::getline(iStream, line);
    try {
        recipe.servings = std::stoul(line);
    }
    catch (std::invalid_argument) {
        throw InvalidFormatException("Couldn't convert servings to integer");
    }
}

void RcpReader::decodeDifficulty(boost::filesystem::ifstream &iStream) const
{
    std::string line;
    std::getline(iStream, line);
    try {
        recipe.difficulty = std::stoul(line);
    }
    catch (std::invalid_argument) {
        throw InvalidFormatException("Couldn't convert difficulty to integer");
    }
}

void RcpReader::decodeTime(boost::filesystem::ifstream &iStream) const
{
    std::string line;
    std::getline(iStream, line);
    try {
        recipe.time = std::stoul(line);
    }
    catch (std::invalid_argument) {
        throw InvalidFormatException("Couldn't convert time to integer");
    }
}

void RcpReader::decodeImage(boost::filesystem::ifstream &iStream) const
{
    std::getline(iStream, recipe.imagePath);
}

void RcpReader::decodeIngredients(boost::filesystem::ifstream &iStream) const
{
    std::string line;
    while (std::getline(iStream, line) && line != "[ingredients]")
    {
        if (line == "") {
            throw InvalidFormatException("Found empty line instead of the ingredient");
        }
        recipe.ingredients.push_back(line);
    }
}

void RcpReader::decodeSteps(boost::filesystem::ifstream &iStream) const
{
    std::string line;
    while (std::getline(iStream, line) && line != "[steps]")
    {
        if (line == "") {
            throw InvalidFormatException("Found empty line instead of the step");
        }
        recipe.steps.push_back(line);
    }
}

void RcpReader::encode(const boost::filesystem::path& file, const Recipe& recipe) const
{   //TODO divide in functions?
    boost::filesystem::ofstream oStream{file};
    oStream << "[id]" << std::endl << recipe.id << std::endl << std::endl;
    if(recipe.starred)
    {
        oStream << "[starred]" << std::endl << std::endl;
    }
    oStream << "[name]" << std::endl << recipe.name << std::endl << std::endl;
    oStream << "[description]" << std::endl << recipe.description << std::endl << std::endl;
    oStream << "[servings]" << std::endl << recipe.servings << std::endl << std::endl;
    oStream << "[difficulty]" << std::endl << recipe.difficulty << std::endl << std::endl;
    oStream << "[time]" << std::endl << recipe.time << std::endl << std::endl;
    oStream << "[image]" << std::endl << recipe.imagePath << std::endl << std::endl;
    if(recipe.categories.size() > 0)
    {
        oStream << "[category]" << std::endl;
        for(const std::string& category: recipe.categories)
        {
            oStream << category << std::endl;
        }
        oStream << "[category]" << std::endl << std::endl;
    }
    if(recipe.ingredients.size() > 0)
    {
        oStream << "[ingredients]" << std::endl;
        for(const std::string& ingredient: recipe.ingredients)
        {
            oStream << ingredient << std::endl;
        }
        oStream << "[ingredients]" << std::endl << std::endl;
    }
    if(recipe.steps.size() > 0)
    {
        oStream << "[steps]" << std::endl;
        for(const std::string& step: recipe.steps)
        {
            oStream << step << std::endl;
        }
        oStream << "[steps]" << std::endl << std::endl;
    }
}
