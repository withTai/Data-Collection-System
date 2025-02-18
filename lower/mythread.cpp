#include "mythread.h"
#include "qt1.h"
extern "C"{                  //表示用C语言编译（当C与C++混合编译时使用）
    #include "communication.h"   //**引入TCP通信连接相关函数
}


//用于子线程循环读取上位机的查询指令后，标志当前是否进入于Rwarning、R、图片的发送模式
extern int RwarningStarted;    //**注意在extern外部变量时不可再次赋值，否则报错multiple definition
extern int RStarted;
extern int PhotoStarted;


MyThread::MyThread()
{

}


void MyThread::run() {   //子线程运行的内容
    while(1) {                              //子线程一直持续准备接收上位机指令
//        fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL, 0) | O_NONBLOCK);

        printf("Thread: reading...\r\n");
        receivedSignal = subTCPread();         //读取上位机指令(若没有发送，则子线程会一直阻塞在此处)

        if(receivedSignal == 1){       //上位机查询R
            if(RStarted == 0){              //若当前未进入RStarted发送状态，则进入发送状态
                RStarted = 1;
            }
            else{                           //若当前已进入RStarted发送状态，则退出发送状态
                RStarted = 0;
            }
        }
        else if(receivedSignal == 2){  //上位机查询Rwarning
            if(RwarningStarted == 0){       //若当前未进入Rwarning发送状态，则进入发送状态
                RwarningStarted = 1;
            }
            else{                           //若当前已进入Rwarning发送状态，则退出发送状态
                RwarningStarted = 0;
            }
        }
        else if(receivedSignal == 3){  //上位机查询图片
            if(PhotoStarted == 0){          //若当前未进入PhotoStarted发送状态，则进入发送状态
                PhotoStarted = 1;
            }
            else{                           //若当前已进入PhotoStarted发送状态，则退出发送状态
                PhotoStarted = 0;
            }
        }
    }
};
