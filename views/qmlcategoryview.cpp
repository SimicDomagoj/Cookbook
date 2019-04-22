#include "qmlcategoryview.h"
#include"controllers/categorycontroller.h"
#include"cookbookapp.h"

QmlCategoryView::QmlCategoryView(CategoryController& controller) : CategoryView{controller} { }

void QmlCategoryView::show()
{
    CookbookApp::getInstance().registerObject("CategoryView", this);
    CookbookApp::getInstance().pushView("qrc:/views/categoryView.qml");
}

void QmlCategoryView::setCategories(const std::vector<CategoryViewModel>& categories)
{
    categoriesSet(toQmlModel(categories));
}

void QmlCategoryView::showMessage(const std::string &message)
{
    emit messageSet(QString::fromStdString(message));
}

void QmlCategoryView::handleClickedButton(QmlRecipeFilter* filter)
{
    controller.showRecepies(*filter);
}

void QmlCategoryView::handleRandomClicked(QmlRecipeFilter* filter)
{
    controller.handleRandomClicked(*filter);
}

void QmlCategoryView::handleShoppingListClicked()
{
    controller.handleShoppingListClicked();
}

void QmlCategoryView::activating()
{
    controller.refresh();
}

QVariantList QmlCategoryView::toQmlModel(const std::vector<CategoryViewModel>& categories)
{
    QVariantList qmlCategories{};
    for(const CategoryViewModel& category: categories){
        QmlCategoryViewModel* qmlModel = new QmlCategoryViewModel();
        qmlModel->name = category.name;
        qmlModel->imagePath = category.imagePath;
        QQmlEngine::setObjectOwnership(qmlModel, QQmlEngine::JavaScriptOwnership);
        qmlCategories.append(QVariant::fromValue(qmlModel));
    }
    return qmlCategories;
}
