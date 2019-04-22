#pragma once

#include"listinputviewmodel.h"
#include <QObject>
#include<QString>

class QmlListModel : public QObject, public ListInputViewModel
{
Q_OBJECT
Q_PROPERTY(int id READ getId)
Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
Q_PROPERTY(QString imagePath READ getImagePath WRITE setImagePath NOTIFY imagePathChanged)
Q_PROPERTY(bool starred READ isStarred WRITE setStarred NOTIFY starredChanged)
public:
    QmlListModel();
    QmlListModel(uint32_t id, QString name, QString imgPath, bool starred);
    uint32_t getId();
    QString getName() const;
    void setName(const QString &value);
    QString getImagePath() const;
    void setImagePath(const QString &value);
    bool isStarred() const;
    void setStarred(const bool &value);
signals:
    void nameChanged();
    void imagePathChanged();
    void starredChanged();
};
