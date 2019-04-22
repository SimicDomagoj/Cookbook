#include"qmlrecipeviewmodel.h"

QmlRecipeViewModel::QmlRecipeViewModel() {}

QmlRecipeViewModel::QmlRecipeViewModel(uint32_t id) : QObject {}, RecipeViewModel{id} { }

uint32_t QmlRecipeViewModel::getId(){
    return id;
}

QString QmlRecipeViewModel::getName() const {
    return QString::fromStdString(name);
}

void QmlRecipeViewModel::setName(const QString &value){
    if(name != value.toStdString()){
        name = value.toStdString();
        emit nameChanged();
    }
}

QString QmlRecipeViewModel::getDescription() const {
    return QString::fromStdString(description);
}

void QmlRecipeViewModel::setDescription(const QString &value){
    if(description != value.toStdString()){
        description = value.toStdString();
        emit descriptionChanged();
    }
}

uint32_t QmlRecipeViewModel::getServings() const
{
    return servings;
}

void QmlRecipeViewModel::setServings(const uint32_t &value)
{
    if(servings != value){
        servings = value;
        emit servingsChanged();
    }
}

uint32_t QmlRecipeViewModel::getDifficulty() const
{
    return difficulty;
}

void QmlRecipeViewModel::setDifficulty(const uint32_t &value)
{
    if(difficulty != value){
        difficulty = value;
        emit difficultyChanged();
    }
}

uint32_t QmlRecipeViewModel::getTime() const
{
    return time;
}

void QmlRecipeViewModel::setTime(const uint32_t &value)
{
    if(time != value){
        time = value;
        emit timeChanged();
    }
}


QString QmlRecipeViewModel::getImagePath() const {
    return QString::fromStdString(imagePath);
}

void QmlRecipeViewModel::setImagePath(const QString &value){
    if(imagePath != value.toStdString()){
        imagePath = value.toStdString();
        emit imagePathChanged();
    }
}

QVector<QString> QmlRecipeViewModel::getCategories() const {
    int categoriesSize = static_cast<int>(categories.size());
    QVector<QString> qmlCategories{ categoriesSize };
    for (unsigned int i = 0; i < categories.size(); ++i) {
        qmlCategories[i] = QString::fromStdString(categories[i]);
    }
    return qmlCategories;
}

void QmlRecipeViewModel::setCategories(const QVector<QString> &value){
    categories.resize(value.size());
    for (int i = 0; i < value.size(); ++i) {
        categories[i] = value[i].toStdString();
    }
    emit categoriesChanged();
}

QVector<QString> QmlRecipeViewModel::getIngredients() const
{
    int ingredientsSize = static_cast<int>(ingredients.size());
    QVector<QString> qmlIngredients{ ingredientsSize };
    for (unsigned int i = 0; i < ingredients.size(); ++i) {
        qmlIngredients[i] = QString::fromStdString(ingredients[i]);
    }
    return qmlIngredients;
}
void QmlRecipeViewModel::setIngredients(const QVector<QString> &value)
{
    ingredients.resize(value.size());
    for (int i = 0; i < value.size(); ++i) {
        ingredients[i] = value[i].toStdString();
    }
    emit ingredientsChanged();
}

QVector<QString> QmlRecipeViewModel::getSteps() const
{
    int stepsSize = static_cast<int>(steps.size());
    QVector<QString> qmlSteps{ stepsSize };
    for (unsigned int i = 0; i < steps.size(); ++i) {
        qmlSteps[i] = QString::fromStdString(steps[i]);
    }
    return qmlSteps;
}
void QmlRecipeViewModel::setSteps(const QVector<QString> &value)
{
    steps.resize(value.size());
    for (int i = 0; i < value.size(); ++i) {
        steps[i] = value[i].toStdString();
    }
    emit stepsChanged();
}

bool QmlRecipeViewModel::isStarred() const {
    return starred;
}

void QmlRecipeViewModel::setStarred(const bool &value){
    if(starred != value){
        starred = value;
        emit starredChanged();
    }
}
