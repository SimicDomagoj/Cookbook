#include "qmllistmodel.h"

QmlListModel::QmlListModel() : QObject{} {}

QmlListModel::QmlListModel(uint32_t id, QString name, QString imgPath, bool starred)
{
    this->id = id;
    setName(name);
    setImagePath(imgPath);
    setStarred(starred);
}

uint32_t QmlListModel::getId(){
    return id;
}
QString QmlListModel::getName() const {
    return QString::fromStdString(name);
}
void QmlListModel::setName(const QString &value){
    name = value.toStdString();
    emit nameChanged();
}
QString QmlListModel::getImagePath() const {
    return QString::fromStdString(imagePath);
}
void QmlListModel::setImagePath(const QString &value){
    imagePath = value.toStdString();
    emit imagePathChanged();
}
bool QmlListModel::isStarred() const {
    return starred;
}
void QmlListModel::setStarred(const bool &value){
    starred = value;
    emit starredChanged();
}
