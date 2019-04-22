#pragma once

#include"views/shoppinglistview.h"
#include<QObject>
#include<QVector>
#include<QString>

class QmlShoppingListView : public QObject, public ShoppingListView
{
Q_OBJECT
signals:
    void listSet(QVector<QString> list);
    void editingEnabled();
    void editingDisabled();
public:
    QmlShoppingListView(ShoppingListController& controller);
    void show();
    void setList(std::vector<std::string>& list);
    void close();
    void enableEditing();
    void disableEditing();
protected slots:
    Q_INVOKABLE void handleRetrunClicked();
    Q_INVOKABLE void saveButtonClicked(QVector<QString> list);
    Q_INVOKABLE void editButtonClicked();
    Q_INVOKABLE void cancelButtonClicked();
    Q_INVOKABLE void activating();
private:
    QVector<QString> toQmlViewModel(const std::vector<std::string>& list);
    std::vector<std::string> toViewModel(const QVector<QString>& list);
};
