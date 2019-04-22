#pragma once

#include"recipeviewmodel.h"
#include<QObject>
#include<QString>
#include<QVector>

class QmlRecipeViewModel : public QObject, public RecipeViewModel
{
Q_OBJECT
Q_PROPERTY(int id READ getId)
Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY descriptionChanged)
Q_PROPERTY(int servings READ getServings WRITE setServings NOTIFY servingsChanged)
Q_PROPERTY(int difficulty READ getDifficulty WRITE setDifficulty NOTIFY difficultyChanged)
Q_PROPERTY(int time READ getTime WRITE setTime NOTIFY timeChanged)
Q_PROPERTY(QString imagePath READ getImagePath WRITE setImagePath NOTIFY imagePathChanged)
Q_PROPERTY(QVector<QString> categories READ getCategories WRITE setCategories NOTIFY categoriesChanged)
Q_PROPERTY(QVector<QString> ingredients READ getIngredients WRITE setIngredients NOTIFY ingredientsChanged)
Q_PROPERTY(QVector<QString> steps READ getSteps WRITE setSteps NOTIFY stepsChanged)
Q_PROPERTY(bool starred READ isStarred WRITE setStarred NOTIFY starredChanged)
public:
    QmlRecipeViewModel();
    QmlRecipeViewModel(uint32_t id);
    uint32_t getId();
    QString getName() const;
    void setName(const QString &value);
    QString getDescription() const;
    void setDescription(const QString &value);
    uint32_t getServings() const;
    void setServings(const uint32_t &value);
    uint32_t getDifficulty() const;
    void setDifficulty(const uint32_t &value);
    uint32_t getTime() const;
    void setTime(const uint32_t &value);
    QString getImagePath() const;
    void setImagePath(const QString &value);
    QVector<QString> getCategories() const;
    void setCategories(const QVector<QString> &value);
    QVector<QString> getIngredients() const;
    void setIngredients(const QVector<QString> &value);
    QVector<QString> getSteps() const;
    void setSteps(const QVector<QString> &value);
    bool isStarred() const;
    void setStarred(const bool &value);
signals:
    void nameChanged();
    void descriptionChanged();
    void servingsChanged();
    void difficultyChanged();
    void timeChanged();
    void imagePathChanged();
    void categoriesChanged();
    void ingredientsChanged();
    void stepsChanged();
    void starredChanged();
};
