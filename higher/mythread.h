#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>


class MyThread : public QThread
{
    Q_OBJECT

public:
    char* receivedString;
    MyThread();
    void run();   	//子线程处理函数（和主线程不在同一个线程）

signals:
    void ReceivedR(QString);
    void ReceivedRwarning(QString);
    void ReceivedPhoto();
};

#endif
