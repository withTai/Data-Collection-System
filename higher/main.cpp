#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // 创建了QApplication对象a
    QApplication a(argc, argv);
    // 创建了Login对象LG
    Login LG;
    
    LG.show();

    return a.exec();
}
