#include<QGuiApplication>
#include"controllers/categorycontroller.h"
#include"cookbookapp.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    CookbookApp::getInstance().init();
    CategoryController controller{};
    controller.show();
    return a.exec();
}
