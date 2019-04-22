#include "qmlcategoryviewmodel.h"

QmlCategoryViewModel::QmlCategoryViewModel()
{

}

QString QmlCategoryViewModel::getName() const
{
    return QString::fromStdString(name);
}

void QmlCategoryViewModel::setName(const QString &value)
{
    name = value.toStdString();
    emit nameChanged();
}

QString QmlCategoryViewModel::getImagePath() const
{
    return QString::fromStdString(imagePath);
}

void QmlCategoryViewModel::setImagePath(const QString &value)
{
    imagePath = value.toStdString();
    emit imagePathChanged();
}
