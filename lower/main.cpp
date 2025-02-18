#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include "qt1.h"
#include "ui_qt1.h"
#include "login.h"
#include "ui_login.h"

int mainArgc;
char** mainArgv;


int main(int argc, char** argv)
{
	mainArgc = argc;           //获得网路IP连接号
	mainArgv = argv;

    QApplication app(argc, argv);

    //创建并显示登陆界面
    Login LG;
    LG.show();

//    //也可用以下指针的方式创建窗口对象
//    Login* LG = new Login();
//    LG->show();

	return app.exec();
}
