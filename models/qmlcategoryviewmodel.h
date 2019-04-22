#pragma once
#include"categoryviewmodel.h"
#include<QObject>
#include<QString>

class QmlCategoryViewModel : public QObject, public CategoryViewModel
{
Q_OBJECT
Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
Q_PROPERTY(QString imagePath READ getImagePath WRITE setImagePath NOTIFY imagePathChanged)
signals:
    void nameChanged();
    void imagePathChanged();
public:
    QmlCategoryViewModel();
    QString getName() const;
    void setName(const QString &value);
    QString getImagePath() const;
    void setImagePath(const QString &value);
};
