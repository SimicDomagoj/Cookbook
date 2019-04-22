#pragma once

#include"recipefilter.h"
#include<QObject>
#include<QString>
#include<QVector>

class QmlRecipeFilter : public QObject, public RecipeFilter
{
Q_OBJECT
Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
Q_PROPERTY(int minServings READ getMinServings WRITE setMinServings NOTIFY minServingsChanged)
Q_PROPERTY(int maxServings READ getMaxServings WRITE setMaxServings NOTIFY maxServingsChanged)
Q_PROPERTY(QVector<int> difficulties READ getDifficulties WRITE setDifficulties NOTIFY difficultiesChanged)
Q_PROPERTY(int minTime READ getMinTime WRITE setMinTime NOTIFY minTimeChanged)
Q_PROPERTY(int maxTime READ getMaxTime WRITE setMaxTime NOTIFY maxTimeChanged)
Q_PROPERTY(QString category READ getCategory WRITE setCategory NOTIFY categoryChanged)
Q_PROPERTY(QString ingredient READ getIngredient WRITE setIngredient NOTIFY ingredientChanged)
Q_PROPERTY(bool starred READ isStarred WRITE setStarred NOTIFY starredChanged)
signals:
    void nameChanged();
    void minServingsChanged();
    void maxServingsChanged();
    void difficultiesChanged();
    void minTimeChanged();
    void maxTimeChanged();
    void categoryChanged();
    void ingredientChanged();
    void starredChanged();
public:
    QmlRecipeFilter();
    QString getName() const;
    void setName(const QString &value);
    uint32_t getMinServings() const;
    void setMinServings(const uint32_t &value);
    uint32_t getMaxServings() const;
    void setMaxServings(const uint32_t &value);
    QVector<int32_t> getDifficulties() const;
    void setDifficulties(const QVector<int32_t> &value);
    uint32_t getMinTime() const;
    void setMinTime(const uint32_t &value);
    uint32_t getMaxTime() const;
    void setMaxTime(const uint32_t &value);
    QString getCategory() const;
    void setCategory(const QString &value);
    QString getIngredient() const;
    void setIngredient(const QString &value);
    bool isStarred() const;
    void setStarred(const bool &value);
};
