#include"cookbookapp.h"
#include"models/qmllistmodel.h"
#include"models/qmlrecipeviewmodel.h"
#include"filters/qmlrecipefilter.h"
#include"models/qmlcategoryviewmodel.h"

CookbookApp* CookbookApp::instance = nullptr;

CookbookApp& CookbookApp::getInstance()
{
    if(instance == nullptr){
        instance = new CookbookApp();
    }
    return *instance;
}

void qmlRegisterSingleton()
{
    qmlRegisterSingletonType<CookbookApp>("CookbookApp", 1, 0, "CookbookApp", &CookbookApp::getQmlInstance);
}

void CookbookApp::init()
{
    qmlRegisterSingleton();
    qmlRegisterType<QmlListModel>("CustomComponents", 1, 0, "QmlListModel");
    qmlRegisterType<QmlRecipeViewModel>("CustomComponents", 1, 0, "QmlRecipeViewModel");
    qmlRegisterType<QmlRecipeFilter>("CustomComponents", 1, 0, "QmlRecipeFilter");
    qmlRegisterType<QmlCategoryViewModel>("CustomComponents", 1, 0, "QmlCategoryViewModel");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
}

void CookbookApp::pushView(QString viewName)
{
    emit viewPushed(viewName);
}

void CookbookApp::popView()
{
    emit viewPopped();
}

void CookbookApp::registerObject(QString name, QObject* object)
{
    engine.rootContext()->setContextProperty(name, QVariant::fromValue(object));
}

QObject* CookbookApp::getQmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine)
    return &(getInstance());
}

CookbookApp::~CookbookApp()
{
    delete instance;
}
