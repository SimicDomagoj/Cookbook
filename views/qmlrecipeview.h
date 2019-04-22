#pragma once

#include"./views/recipeview.h"
#include"models/qmlrecipeviewmodel.h"
#include<QObject>
#include<QVariant>

class QmlRecipeView : public QObject, public RecipeView
{
Q_OBJECT
signals:
    void recipeSet(QVariant recipe);
    void errorMessageSet(QString message) const;
    void editingEnabled();
    void editingDisabled();
public:
    QmlRecipeView(RecipeController& controller);
    virtual void show() override;
    virtual void setRecipe(RecipeViewModel& recipe) override;
    virtual void close() override;
    virtual void enableEditing() override;
    virtual void disableEditing() override;
    void showErrorMessage(const std::string& message) const override;
protected slots:
    Q_INVOKABLE void saveButtonClicked(QmlRecipeViewModel* recipe);
    Q_INVOKABLE void editButtonClicked();
    Q_INVOKABLE void cancelButtonClicked();
    Q_INVOKABLE void returnButtonClicked();
    Q_INVOKABLE void deleteButtonClicked(QmlRecipeViewModel* recipe);
    Q_INVOKABLE void addToShoppingList(QString item);
    Q_INVOKABLE void activating();
private:
    QVariant toQmlViewModel(RecipeViewModel& viewModel);
};
