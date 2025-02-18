#include "mythread.h"
#include "mainwindow.h"
#include <stdio.h>
#include <QDebug>
extern "C"{                  //表示用C语言编译（当C与C++混合编译时使用）
    #include "tcp_server.h"
}

extern char R[10];      //阻值信息
extern char Rwn[10];    //报警信息



MyThread::MyThread()
{

}


void MyThread::run() {   //子线程运行的内容
    while(1) {                              //子线程一直持续准备接收
        qDebug() << "Thread: reading...\r\n";
        int ReceivedSignal = subTCPread();

        qDebug() << "ReceivedSignal: " << ReceivedSignal << "\r\n";
        if(ReceivedSignal == 2){        //若下位机发送的是阻值数据
            QString RString = QString(QLatin1String(R));
            emit ReceivedR(RString);
        }
        else if(ReceivedSignal == 3){   //若下位机发送的是警报数据
            QString RwnString = QString(QLatin1String(Rwn));
            emit ReceivedRwarning(RwnString);
        }
        else if(ReceivedSignal == 4){   //若下位机发送的是图像数据
            emit ReceivedPhoto();
        }
    }
};
