#pragma once

#include"views/categoryview.h"
#include<QObject>
#include<QString>

class QmlCategoryView :  public QObject, public CategoryView
{
Q_OBJECT
signals:
    void categoriesSet(const QVariantList& categories);
    void messageSet(const QString& message);
public:
    QmlCategoryView(CategoryController& controller);
    void show() override;
    void setCategories(const std::vector<CategoryViewModel>& categories) override;
    void showMessage(const std::string& message) override;
protected slots:
    Q_INVOKABLE void handleClickedButton(QmlRecipeFilter* filter);
    Q_INVOKABLE void handleRandomClicked(QmlRecipeFilter* filter);
    Q_INVOKABLE void handleShoppingListClicked();
    Q_INVOKABLE void activating();
private:
    QVariantList toQmlModel(const std::vector<CategoryViewModel>& categories);
};
