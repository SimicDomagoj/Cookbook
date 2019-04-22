#pragma once
#include"models/recipe.h"
#include<boost/filesystem.hpp>
#include<boost/filesystem/fstream.hpp>

class RcpReader
{
public:
    RcpReader();
    Recipe decode(const boost::filesystem::path& file) const;
    void encode(const boost::filesystem::path& file, const Recipe& recipe) const;

private:
    void verifyEndOfBlock(boost::filesystem::ifstream& iStream) const;
    void decodeId(boost::filesystem::ifstream& iStream) const;
    void decodeStarred(boost::filesystem::ifstream& iStream) const;
    void decodeName(boost::filesystem::ifstream& iStream) const;
    void decodeCategory(boost::filesystem::ifstream& iStream) const;
    void decodeDescription(boost::filesystem::ifstream& iStream) const;
    void decodeServings(boost::filesystem::ifstream& iStream) const;
    void decodeDifficulty(boost::filesystem::ifstream& iStream) const;
    void decodeTime(boost::filesystem::ifstream& iStream) const;
    void decodeImage(boost::filesystem::ifstream& iStream) const;
    void decodeIngredients(boost::filesystem::ifstream& iStream) const;
    void decodeSteps(boost::filesystem::ifstream& iStream) const;
    mutable Recipe recipe;
};
