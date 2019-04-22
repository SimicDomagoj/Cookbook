#include "qmlshoppinglistview.h"
#include"controllers/shoppinglistcontroller.h"
#include"cookbookapp.h"

QmlShoppingListView::QmlShoppingListView(ShoppingListController& controller) : ShoppingListView{controller}{}

void QmlShoppingListView::show()
{
    CookbookApp::getInstance().registerObject("ShoppingListView", this);
    CookbookApp::getInstance().pushView("qrc:/views/shoppingListView.qml");
}

void QmlShoppingListView::setList(std::vector<std::string>& list)
{
    emit listSet(toQmlViewModel(list));
}

void QmlShoppingListView::close()
{
    CookbookApp::getInstance().popView();
}

void QmlShoppingListView::enableEditing()
{
    emit editingEnabled();
}

void QmlShoppingListView::disableEditing()
{
    emit editingDisabled();
}

void QmlShoppingListView::handleRetrunClicked()
{
    controller.handleReturnClicked();
}

void QmlShoppingListView::saveButtonClicked(QVector<QString> list)
{
    controller.save(toViewModel(list));
}

void QmlShoppingListView::editButtonClicked()
{
    controller.enableEditing();
}

void QmlShoppingListView::cancelButtonClicked()
{
    controller.cancelClicked();
}

void QmlShoppingListView::activating()
{
    controller.refresh();
}

QVector<QString> QmlShoppingListView::toQmlViewModel(const std::vector<std::string> &list)
{
    QVector<QString> qmlViewModel;
    for (const std::string& item: list){
        qmlViewModel.push_back(QString::fromStdString(item));
    }
    return qmlViewModel;
}

std::vector<std::string> QmlShoppingListView::toViewModel(const QVector<QString> &list)
{
    std::vector<std::string> viewModel;
    for (const QString& item: list){
        viewModel.push_back(item.toStdString());
    }
    return viewModel;
}
