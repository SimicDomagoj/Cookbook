#include "qmllistview.h"
#include"controllers/recipelistcontroller.h"
#include"models/qmllistmodel.h"
#include"cookbookapp.h"
#include<QQmlEngine>

QmlListView::QmlListView(RecipeListController& controller) : ListView{controller} { }

void QmlListView::show()
{
    CookbookApp::getInstance().registerObject("CppListView", this);
    CookbookApp::getInstance().pushView("qrc:/views/listView.qml");
}

void QmlListView::setList(std::vector<ListInputViewModel> list)
{
    emit listSet(toQmlViewModel(list));
}

void QmlListView::close()
{
    CookbookApp::getInstance().popView();
}

void QmlListView::handleClickedElement(int id)
{
    controller.showRecipe(static_cast<uint32_t>(id));
}

void QmlListView::newButtonClicked()
{
    controller.addRecipe();
}

void QmlListView::deleteButtonClicked(int id)
{
    controller.deleteRecipe(static_cast<uint32_t>(id));
}

void QmlListView::returnButtonClicked()
{
    controller.doReturn();
}

void QmlListView::activating()
{
    controller.refresh();
}

void QmlListView::handleStarredToggle(int id)
{
    controller.handleStarredToggle(static_cast<uint32_t>(id));
}

QVariantList QmlListView::toQmlViewModel(std::vector<ListInputViewModel> list)
{
    QVariantList qmlListModel{};
    for(ListInputViewModel& item: list)
    {
        QmlListModel* viewModel = new QmlListModel(item.id,
                                                   QString::fromStdString(item.name),
                                                   QString::fromStdString(item.imagePath),
                                                   item.starred);
        QQmlEngine::setObjectOwnership(viewModel, QQmlEngine::JavaScriptOwnership);
        qmlListModel.append(QVariant::fromValue(viewModel));
    }
    return qmlListModel;
}
