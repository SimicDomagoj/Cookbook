#include"qmlrecipefilter.h"

QmlRecipeFilter::QmlRecipeFilter() {}

QString QmlRecipeFilter::getName() const
{
    return QString::fromStdString(name);
}

void QmlRecipeFilter::setName(const QString &value)
{
    name = value.toStdString();
    emit nameChanged();
}

uint32_t QmlRecipeFilter::getMinServings() const
{
    return minServings;
}

void QmlRecipeFilter::setMinServings(const uint32_t &value)
{
    minServings = value;
    emit minServingsChanged();
}

uint32_t QmlRecipeFilter::getMaxServings() const
{
    return maxServings;
}

void QmlRecipeFilter::setMaxServings(const uint32_t &value)
{
    maxServings = value;
    emit maxServingsChanged();
}

QVector<int32_t> QmlRecipeFilter::getDifficulties() const
{
    QVector<int32_t> qmlDifficulties{};
    for(uint32_t difficulty: difficulties){
        qmlDifficulties.push_back(static_cast<int32_t>(difficulty));
    }
    return qmlDifficulties;
}

void QmlRecipeFilter::setDifficulties(const QVector<int32_t>& value)
{
    difficulties.clear();
    for(int32_t difficulty: value){
        difficulties.push_back(static_cast<uint32_t>(difficulty));
    }
    emit difficultiesChanged();
}

uint32_t QmlRecipeFilter::getMinTime() const
{
    return minTime;
}

void QmlRecipeFilter::setMinTime(const uint32_t &value)
{
    minTime = value;
    emit minTimeChanged();
}

uint32_t QmlRecipeFilter::getMaxTime() const
{
    return maxTime;
}

void QmlRecipeFilter::setMaxTime(const uint32_t &value)
{
    maxTime = value;
    emit maxTimeChanged();
}

QString QmlRecipeFilter::getCategory() const
{
    return QString::fromStdString(category);
}

void QmlRecipeFilter::setCategory(const QString &value)
{
    category = value.toStdString();
    emit categoryChanged();
}

QString QmlRecipeFilter::getIngredient() const
{
    return QString::fromStdString(ingredient);
}

void QmlRecipeFilter::setIngredient(const QString &value)
{
    ingredient = value.toStdString();
    emit ingredientChanged();
}

bool QmlRecipeFilter::isStarred() const
{
    return starred;
}

void QmlRecipeFilter::setStarred(const bool &value)
{
    starred = value;
    emit starredChanged();
}
