#include "qmlrecipeview.h"
#include"controllers/recipecontroller.h"
#include"cookbookapp.h"
#include<QVector>
#include<QString>

QmlRecipeView::QmlRecipeView(RecipeController& controller) : RecipeView {controller} { }

void QmlRecipeView::show()
{
    CookbookApp::getInstance().registerObject("RecipeView", this);
    CookbookApp::getInstance().pushView("qrc:/views/recipeView.qml");
}

void QmlRecipeView::setRecipe(RecipeViewModel& recipe)
{
    emit recipeSet(toQmlViewModel(recipe));
}

void QmlRecipeView::close()
{
    CookbookApp::getInstance().popView();
}

void QmlRecipeView::enableEditing()
{
    emit editingEnabled();
}

void QmlRecipeView::disableEditing()
{
    emit editingDisabled();
}

void QmlRecipeView::showErrorMessage(const std::string& message) const
{
    emit errorMessageSet(QString::fromStdString(message));
}

void QmlRecipeView::saveButtonClicked(QmlRecipeViewModel* recipe)
{
    controller.save(*recipe);
}

void QmlRecipeView::editButtonClicked()
{
    controller.enableEditing();
}

void QmlRecipeView::cancelButtonClicked()
{
    controller.cancelClicked();
}

void QmlRecipeView::returnButtonClicked()
{
    controller.doReturn();
}

void QmlRecipeView::deleteButtonClicked(QmlRecipeViewModel* recipe)
{
    controller.remove(*recipe);
}

void QmlRecipeView::addToShoppingList(QString item)
{
    controller.addToShoppingList(item.toStdString());
}

void QmlRecipeView::activating()
{
    controller.refresh();
}

QVariant QmlRecipeView::toQmlViewModel(RecipeViewModel& viewModel)
{
    QmlRecipeViewModel* qmlViewModel = new QmlRecipeViewModel(viewModel.id);
    qmlViewModel->setName(QString::fromStdString(viewModel.name));
    qmlViewModel->setDescription(QString::fromStdString(viewModel.description));
    qmlViewModel->setServings(viewModel.servings);
    qmlViewModel->setDifficulty(viewModel.difficulty);
    qmlViewModel->setTime(viewModel.time);
    qmlViewModel->setImagePath(QString::fromStdString(viewModel.imagePath));
    qmlViewModel->setStarred(viewModel.starred);
    QVector<QString> categoriesViewModel, stepsViewModel, ingredientsViewModel;
    for(std::string& category: viewModel.categories)
    {
        categoriesViewModel.append(QString::fromStdString(category));
    }
    for(std::string& step: viewModel.steps)
    {
        stepsViewModel.append(QString::fromStdString(step));
    }
    for(std::string& ingredient: viewModel.ingredients)
    {
        ingredientsViewModel.append(QString::fromStdString(ingredient));
    }
    qmlViewModel->setCategories(categoriesViewModel);
    qmlViewModel->setSteps(stepsViewModel);
    qmlViewModel->setIngredients(ingredientsViewModel);
    QQmlEngine::setObjectOwnership(qmlViewModel, QQmlEngine::JavaScriptOwnership);
    return QVariant::fromValue(qmlViewModel);
}
