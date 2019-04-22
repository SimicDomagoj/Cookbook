#pragma once

#include"listview.h"
#include<QObject>
#include<QString>
#include<QVector>
#include<QVariant>

class QmlListView : public QObject, public ListView
{
Q_OBJECT
signals:
    void listSet(QVariantList list);
public:
    QmlListView(RecipeListController& controller);
    void show() override;
    void setList(std::vector<ListInputViewModel> list) override;
    void close() override;
protected slots:
    Q_INVOKABLE void handleClickedElement(int id);
    Q_INVOKABLE void newButtonClicked();
    Q_INVOKABLE void deleteButtonClicked(int id);
    Q_INVOKABLE void returnButtonClicked();
    Q_INVOKABLE void activating();
    Q_INVOKABLE void handleStarredToggle(int id);
private:
    QVariantList toQmlViewModel(std::vector<ListInputViewModel> recipes);
};
