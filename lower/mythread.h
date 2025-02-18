#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QMutex>            //用于终止线程


class MyThread : public QThread
{
public:
    int receivedSignal;
    QMutex m_lock;
    MyThread();
    void run();   	//子线程处理函数（和主线程不在同一个线程）
};

#endif
