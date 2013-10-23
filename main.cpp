#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget* w = Widget::Instance();
    w->show();
    
    return a.exec();
}
