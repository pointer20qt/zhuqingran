#include "widget.h"
#include <QApplication>
#include"login.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login l;
    l.setWindowTitle("登录界面");
    l.show();
    return a.exec();
}
