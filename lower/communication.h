#ifndef COMMUNICATION_H
#define COMMUNICATION_H

//标准输入输出函数头文件
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//字符串操作函数头文件
#include <string.h>
#include <unistd.h>
//文件操作函数头文件
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <math.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>   //用于捕捉ctl+c信号的头文件


int TCPconnect(int,char**);             //**建立TCP连接的全套过程函数(函数全部执行成功时返回0,否则返回-1)
int TCPlogin(char*,char*);              //**客户端登录的函数
int sendR(int);                         //**发送当前采集的ADC阻值
int sendRwarning(int);                  //**发送阻值上下限报警
int sendPhoto(char*);                   //**发送图片
int sendHeartbeat();                    //**发送心跳包
int subTCPconnect(int,char**);          //**子线程建立TCP连接的全套过程函数(与主线程使用不同端口)
int subTCPread();                       //**用于子线程读取上位机发送的指令内容
long long get_timestamp(void);          //获取时间戳函数
void get_format_time_string(char*);     //获取格式化时间
void InvertUint8(unsigned char*, unsigned char*);
void InvertUint16(unsigned short*, unsigned short*);
unsigned short CRC16_IBM(unsigned char*, unsigned int);   //CRC校验
int ASCIItoNum(char);                   //ASCII码值转其对应符号的十六进制数值
// static void my_handler(int);           //捕获ctl+c信号并代替其原本作用


#endif


