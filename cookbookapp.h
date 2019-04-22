#pragma once
#include<QQmlApplicationEngine>
#include<QString>
#include<QQmlContext>
#include<QVariant>

class CookbookApp : public QObject
{
Q_OBJECT
public:
    static CookbookApp& getInstance();
    static QObject* getQmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);
    void init();
    void pushView(QString viewName);
    void popView();
    void registerObject(QString name, QObject* object);
    ~CookbookApp();
signals:
    void viewPushed(QString viewName);
    void viewPopped();
private:
    CookbookApp(){}
    static CookbookApp* instance;
    QQmlApplicationEngine engine{};
};
