#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
//文件操作函数头文件
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>




int TCPconnect();
int subTCPread();
int ask_R();
int ask_Rwn();
int ask_jpg();
void writetxt_Rwn(char*, char*);
void receive_photo();

#endif
