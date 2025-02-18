#include "communication.h"

//全局变量
//主线程对象句柄
int cfd;                            //TCP连接对象句柄
//子线程对象句柄
int cfd_sub;                            //TCP连接对象句柄


int TCPconnect(int argc,char** argv){             //**建立TCP连接的全套过程函数
	struct sockaddr_in s_add, c_add;
	unsigned short portnum = 2333;     //端口号为2333
//	printf("Hello,welcome to client!\r\n");

	if(argc != 2)
	{
			printf("TCPconnect: echo ip\n");//**在开发板上执行程序时需要用“./test3_2_c 192.168.1.110”**
			return -1;
	}

	//创建socket网络套接字cfp
    cfd = socket(AF_INET, SOCK_STREAM, 0);   //***1表示非阻塞，0表示阻塞
	if(-1 == cfd)
	{
			printf("TCPconnect: socket fail ! \r\n");
			return -1;
	}
	printf("TCPconnect: socket ok !\r\n");

	//配置IP和端口
	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	s_add.sin_addr.s_addr= inet_addr(argv[1]);
	s_add.sin_port=htons(portnum);
//	printf("s_addr = %#x ,port : %#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);

	//向服务器发送连接请求
	if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
	{
			printf("TCPconnect: connect fail !\r\n");
			return -1;
	}
	printf("TCPconnect: connect ok !\r\n");

    return 0;
}


int TCPlogin(char* username,char* password){         //**客户端登录的函数
    char buffer[1024] = {0};            //接收缓存
    memset(buffer, 0, sizeof(buffer));           //清空接收缓存
    int recbyte;                        //当前read接收的字节数

    //1 向上位机发送登录请求
    printf("TCPlogin: Asking for permission of login.\r\n");
    if(-1 == (send(cfd, "Asking for permission of login.\r\n", strlen("Asking for permission of login.\r\n"), 0)))
    {
        printf("TCPlogin: send data fail !\r\n");
        return -1;
    }
    if(-1 == (recbyte = read(cfd, buffer, sizeof(buffer))))  //接收服务器反馈
    {
        printf("TCPlogin: read data fail !\r\n");
        return -1;
    }
//    printf("read ok\r\nREC:\r\n");
    buffer[recbyte]='\0';   //接收的最后一位加上\0变为字符串
    printf("TCPlogin: %s\r\n",buffer);
    sleep(1);

    //2 若上位机发送0(表示请求失败)则退出，否则继续正常执行登录
    if(strcmp(buffer,"0\r\n") == 0){
        memset(buffer, 0, sizeof(buffer));              //清空接收缓存
        printf("TCPlogin: Login failure.\r\n");
        return -1;                           //登录成功返回0
    }

    //3 客户端登录
    printf("TCPlogin: Begin to login.\r\n");

    //发送用户名
    printf("TCPlogin: Sending username...\r\n");
    if(-1 == (send(cfd, username, strlen(username), 0)))
    {
        printf("TCPlogin: send data fail !\r\n");
        return -1;
    }
    //接收服务器反馈
    if(-1 == (recbyte = read(cfd, buffer, sizeof(buffer))))  
    {
        printf("TCPlogin: read data fail !\r\n");
        return -1;
    }
    buffer[recbyte]='\0';   //接收的最后一位加上\0变为字符串
    sleep(1);
    if(strcmp(buffer,"1\r\n") == 0){
        memset(buffer, 0, sizeof(buffer));             //清空接收缓存
        printf("TCPlogin: Send username successfully!\r\n");
    }
    else{
        memset(buffer, 0, sizeof(buffer));             //清空接收缓存
        printf("TCPlogin: Send username failure.\r\n");
        return -1;                          //发送失败返回-1
    }

    //发送密码
    printf("TCPlogin: Sending password...\r\n");
    if(-1 == (send(cfd, password, strlen(password), 0)))
    {
        printf("TCPlogin: send data fail !\r\n");
        return -1;
    }
     //接收服务器反馈
    if(-1 == (recbyte = read(cfd, buffer, sizeof(buffer))))  
    {
        printf("TCPlogin: read data fail !\r\n");
        return -1;
    }
    buffer[recbyte]='\0';   //接收的最后一位加上\0变为字符串
    sleep(1);
    if(strcmp(buffer,"1\r\n") == 0){
        memset(buffer, 0, sizeof(buffer));             //清空接收缓存
        printf("TCPlogin: Send password successfully!\r\n");
    }
    else{
        memset(buffer, 0, sizeof(buffer));             //清空接收缓存
        printf("TCPlogin: Send password failure.\r\n");
        return -1;                          //发送失败返回-1
    }


    //4 登录成功后，向上位机发送登录成功的信息
    if(-1 == (recbyte = read(cfd, buffer, sizeof(buffer))))  
    {
        printf("TCPlogin: read data fail !\r\n");
        return -1;
    }
    buffer[recbyte]='\0';   //接收的最后一位加上\0变为字符串
    printf("TCPlogin: %s\r\n",buffer);
    sleep(1);
    if(strcmp(buffer,"1\r\n") == 0){
        memset(buffer, 0, sizeof(buffer));             //清空接收缓存
        printf("TCPlogin: Login successfully!\r\n");
        return 0;                           //登录成功返回0
    }
    else{
        memset(buffer, 0, sizeof(buffer));             //清空接收缓存
        printf("TCPlogin: Login failure.\r\n");
        return -1;                          //登录失败返回-1
    }
}

int sendR(int R){        //**发送当前采集的ADC阻值（参数R表示当前采集的ADC阻值）
    char buffer[1024] = {0};            //接收缓存
    memset(buffer, 0, sizeof(buffer));           //清空接收缓存
    int recbyte;                        //当前read接收的字节数

    //1 设置发送帧格式
    char pin1[10];  //存放电阻阻值信息(第1个字节表示数据类型为阻值信息，第2个字节表示数据长度为1,第3个字节为所传阻值数据，第4、5个字节为CRC校验码)
    memset(pin1, 0, 10);
    if(R < 1000){
        sprintf(pin1,"03%d",R);
    }
    else{
        sprintf(pin1,"04%d",R);
    }
	
    int i;
	for(i = 0; i < 3; i++){    //同一数据最多只发送3次，否则视为网络连接有问题
		//3 向上位机发送ADC阻值
		if(-1 == (send(cfd, pin1, strlen(pin1), 0)))    
		{
			printf("R: send data fail !\r\n");
			return -1;
		}
        printf("R: send %s \r\n",pin1);
		sleep(1);

		//4 接收上位机回复（反映上位机是否接收成功）
        if(-1 == (recbyte = read(cfd, buffer, sizeof(buffer))))  //接收服务器反馈
		{
			printf("R: read data fail !\r\n");
			return -1;
		}
//		printf("read ok\r\nREC:\r\n");
		buffer[recbyte]='\0';   //接收的最后一位加上\0变为字符串
		printf("R: %s\r\n",buffer);
		sleep(1);

		//5 通过上位机回复决定是否重传
		if(strcmp(buffer,"1\r\n") == 0){      //若上位机接收成功，则跳出循环
            memset(buffer, 0, sizeof(buffer));           //清空接收缓存
			break;                            //跳出循环
		} 
		else{                                 //若上位机接收失败，则继续循环，重传
			printf("R: Send data failed！ Retransmit!\r\n");
            memset(buffer, 0, sizeof(buffer));           //清空接收缓存
		}
	}
	
	//6 若发送了3次均失败，则判断网络连接有问题
	if(i == 3) {
        printf("R: Send data 3 times failed! Examinate the connection!\r\n");  
        return -1;
    }
    else{
        return 0;
    }
}


int sendRwarning(int R){      //**发送阻值上下限报警
    char buffer[1024] = {0};            //接收缓存
    memset(buffer, 0, sizeof(buffer));           //清空接收缓存
    int recbyte;                        //当前read接收的字节数

    //1 设置发送帧格式
    char pin2[10];  //存放报警信息(第1个字节表示数据类型为报警信息，第2个字节表示数据长度为2,第3、4个字节为所传报警信息，第5、6个字节为CRC校验码)
    memset(pin2, 0, 10);
	if(R > 9000){        //高限报警
        sprintf(pin2,"12HI");
	}
	else if(R < 1000){   //低限报警
        sprintf(pin2,"12LO");
	}
    else{
        sprintf(pin2,"12OK");
    }

	int i;
	for(i = 0; i < 3; i++){    //同一数据最多只发送3次，否则视为网络连接有问题
		//3 向上位机发送阻值报警信号
		if(-1 == (send(cfd, pin2, strlen(pin2), 0)))  
		{
			printf("Rwarning: send data fail !\r\n");
			return -1;
		}
        printf("Rwarning: send %s \r\n",pin2);
		sleep(1);

		//4 接收上位机回复（反映上位机是否接收成功）
        if(-1 == (recbyte = read(cfd, buffer, sizeof(buffer))))  //接收服务器反馈
		{
			printf("Rwarning: read data fail !\r\n");
			return -1;
		}
		buffer[recbyte]='\0';   //接收的最后一位加上\0变为字符串
		printf("Rwarning: %s\r\n",buffer);
		sleep(1);

		//5 通过上位机回复决定是否重传
		if(strcmp(buffer,"1\r\n") == 0){      //若上位机接收成功，则跳出循环
            memset(buffer, 0, sizeof(buffer));           //清空接收缓存
			break;                            //跳出循环
		} 
		else{                                 //若上位机接收失败，则继续循环，重传
			printf("Rwarning: Send data failed！ Retransmit!\r\n");
            memset(buffer, 0, sizeof(buffer));           //清空接收缓存
		}
	}
	
	//6 若发送了3次均失败，则判断网络连接有问题
	if(i == 3) {
        printf("Rwarning: Send data 3 times failed! Examinate the connection!\r\n");  
        return -1;
    }
    else{
        return 0;
    }
}


int sendPhoto(char *IOphoto){               //**发送图片
    char file_info[2048] = {0};//文件信息
    char file_name[128] = {0}; //文件名
    char *p; 				   //"/"+文件名
    char buf[1024] = {0};
    strcpy(file_name,(p = strrchr(IOphoto,'/')) ? p+1 : IOphoto);	//获取文件名
    int recbyte;                        //当前read接收的字节数
    char buffer[1024] = {0};            //接收缓存
    memset(buffer, 0, sizeof (buffer));           //清空接收缓存

    //打开文件
    int fd_p = open(IOphoto, O_RDWR);
    if (fd_p == -1)
    {
        printf("open [%s]  failed!\n", IOphoto);
        return -1;
    }

    //计算文件大小
    int file_len = lseek(fd_p, 0, SEEK_END);	//lseek(fd_p, 0, SEEK_END)作用:光标移到文件尾，返回字节数
    lseek(fd_p, 0, SEEK_SET);	    	     //文件光标偏移回文件开始位置
    sprintf(file_info, "%d", file_len);		//将文件大小存放到file_info
    strcpy(file_info + 16, file_name);   	//将文件名存放到file_info,

    //发送图片类型码
    printf("sendPhoto: sending photo flag...\r\n");
    char temp[10];
    memset(temp, 0, 10);
    sprintf(temp,"3n");
    write(cfd, temp, strlen(temp));     //发送图片类型码
    if(-1 == (recbyte = read(cfd, buffer, sizeof(buffer))))  //接收服务器反馈
    {
        printf("sendPhoto: read data failed !\r\n");
    }
    buffer[recbyte]='\0';   //接收的最后一位加上\0变为字符串
    printf("sendPhoto: %s\r\n",buffer);
    if(strcmp(buffer,"1\r\n") != 0){  //若收到的不是1,则发生失败
        printf("sendPhoto: send data failed !\r\n");
    }
    memset(buffer, 0, sizeof(buffer));     //清空接收缓存

    //发送图片大小和名字
    printf("sendPhoto: sending photo length and name...\r\n");
    write(cfd, file_info, 144);		    //将需要上传的文件名告诉对方 144 = 16 + 128,前16位是文件大小，后128位是文件名称，方便信息接受解析
    if(-1 == (recbyte = read(cfd, buffer, sizeof(buffer))))  //接收服务器反馈
    {
        printf("sendPhoto: read data failed !\r\n");
    }
    buffer[recbyte]='\0';   //接收的最后一位加上\0变为字符串
    printf("sendPhoto: %s\r\n",buffer);
    if(strcmp(buffer,"1\r\n") != 0){  //若收到的不是1,则发生失败
        printf("sendPhoto: send data failed !\r\n");
    }
    memset(buffer, 0, sizeof(buffer));     //清空接收缓存

    //发送图片
    int send_len = 0;//记录发送了多少字节
    while (1)
    {
        bzero(buf, sizeof(buf));				//buf缓存清零
        recbyte = read(fd_p, buf, sizeof(buf));	//读取数据
        if (recbyte <= 0)
        {
            break;
        }
        write(cfd, buf, recbyte);		//发送数据
        send_len += recbyte;            //统计发送了多少字节
    }

    //发送图片发送完毕结束信号
    sleep(1);                           //防止上位机还没接收完之前的图片内容
    printf("sendPhoto: send file:%s succeed!!!!\n", file_name);
    send(cfd, "finshed!\r\n", strlen("finshed!\r\n"), 0);  //向上位机发finished!表示图片已经发送完

    //接收上位机最后的响应
    if(-1 == (recbyte = read(cfd, buffer, sizeof (buffer))))  //接收服务器反馈
    {
        printf("sendPhoto: read data fail !\r\n");
        return -1;
    }
    buffer[recbyte]='\0';   //接收的最后一位加上\0变为字符串
    printf("sendPhoto: %s\r\n",buffer);
//    sleep(1);

    if(strcmp(buffer,"1\r\n") == 0){      //若上位机接收成功，则跳出循环
        memset(buffer, 0, sizeof (buffer));           //清空接收缓存
        close(fd_p);
        return 0;                            //跳出循环
    }
    else{                                 //若上位机接收失败，则继续循环，重传
        printf("sendPhoto: Send data failed！ Retransmit!\r\n");
        memset(buffer, 0, sizeof (buffer));           //清空接收缓存
        close(fd_p);
        return -1;
    }
}


int sendHeartbeat(){      //**发送心跳包
    char buffer[1024] = {0};            //接收缓存
    memset(buffer, 0, sizeof (buffer));           //清空接收缓存
    int recbyte;                        //当前read接收的字节数

	int i;
	for(i = 0; i < 3; i++){    //同一数据最多只发送3次，否则视为网络连接有问题
		//1 发送心跳包
        if(-1 == (send(cfd, "1\r\n", strlen("1\r\n"), 0)))
		{
			printf("Hearbeat: send data fail !\r\n");
			return -1;
		}

		//2 接收上位机回复（反映上位机是否接收成功）
        if(-1 == (recbyte = read(cfd, buffer, sizeof (buffer))))  //接收服务器反馈
		{
			printf("Hearbeat: read data fail !\r\n");
			return -1;
		}
//		printf("read ok\r\nREC:\r\n");
		buffer[recbyte]='\0';   //接收的最后一位加上\0变为字符串
		printf("Hearbeat: %s\r\n",buffer);

		//3 通过上位机回复决定是否重传
		if(strcmp(buffer,"1\r\n") == 0){      //若上位机接收成功，则跳出循环
            memset(buffer, 0, sizeof (buffer));           //清空接收缓存
			break;                            //跳出循环
		} 
		else{                                 //若上位机接收失败，则继续循环，重传
			printf("Hearbeat: Send data failed！ Retransmit!\r\n");
            memset(buffer, 0, sizeof (buffer));           //清空接收缓存
		}
	}
	
	//4 若发送了3次均失败，则判断网络连接有问题
	if(i == 3) {
        printf("Hearbeat: Send data 3 times failed! Examinate the connection!\r\n");  
        return -1;
    }
    else{
        return 0;
    }
}


int subTCPconnect(int argc,char** argv){             //**子线程建立TCP连接的全套过程函数(与主线程使用不同端口)
    struct sockaddr_in s_add_sub, c_add_sub;
    unsigned short portnum_sub = 4666;     //端口号为4666
//	printf("Hello,welcome to client!\r\n");

    if(argc != 2)
    {
            printf("subTCPconnect: echo ip\n");//**在开发板上执行程序时需要用“./test3_2_c 192.168.1.110”**
            return -1;
    }

    //创建socket网络套接字cfp
    cfd_sub = socket(AF_INET, SOCK_STREAM, 0);   //***1表示非阻塞，0表示阻塞
    if(-1 == cfd_sub)
    {
            printf("subTCPconnect: socket fail ! \r\n");
            return -1;
    }
    printf("subTCPconnect: socket ok !\r\n");

    //配置IP和端口
    bzero(&s_add_sub,sizeof(struct sockaddr_in));
    s_add_sub.sin_family=AF_INET;
    s_add_sub.sin_addr.s_addr= inet_addr(argv[1]);
    s_add_sub.sin_port=htons(portnum_sub);
//	printf("s_addr = %#x ,port : %#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);

    //向服务器发送连接请求
    if(-1 == connect(cfd_sub,(struct sockaddr *)(&s_add_sub), sizeof(struct sockaddr)))
    {
            printf("subTCPconnect: connect fail !\r\n");
            return -1;
    }
    printf("subTCPconnect: connect ok !\r\n");

    return 0;
}


int subTCPread(){        //**用于子线程读取上位机发送的指令内容(**char*相当于是C中的字符串String，而String是C++中面向对象的数组，但注意用该类型容易段出错)
    char buffer_sub[1024] = {0};            //接收缓存
    memset(buffer_sub, 0, sizeof(buffer_sub));
    int recbyte_sub;                        //当前read接收的字节数

    if(-1 == (recbyte_sub = read(cfd_sub, buffer_sub, sizeof(buffer_sub))))  //接收服务器反馈
    {
        printf("subTCPread: read data fail !\r\n");
    }
    buffer_sub[recbyte_sub]='\0';   //接收的最后一位加上\0变为字符串
    printf("subTCPread: %s\r\n",buffer_sub);
    sleep(1);

    if(strcmp(buffer_sub,"0x00") == 0){
        memset(buffer_sub, 0, sizeof(buffer_sub)); //清空接收缓存
        return 1;
    }
    else if(strcmp(buffer_sub,"0x01") == 0){
        memset(buffer_sub, 0, sizeof(buffer_sub)); //清空接收缓存
        return 2;
    }
    else if(strcmp(buffer_sub,"0x02") == 0){
        memset(buffer_sub, 0, sizeof(buffer_sub)); //清空接收缓存
        return 3;
    }
    else{
        memset(buffer_sub, 0, sizeof(buffer_sub)); //清空接收缓存
        return 0;
    }
}


long long get_timestamp(void)   //获取时间戳函数
{
    long long tmp;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    tmp = tv.tv_sec;
    tmp = tmp * 1000;
    tmp = tmp + (tv.tv_usec / 1000);
    return tmp;
}
void get_format_time_string(char *str_time) //获取格式化时间
{
	time_t now;
    struct tm *tm_now;
    char datetime[128];
    time(&now);
    tm_now = localtime(&now);
    strftime(datetime, 128, " %Y-%m-%d %H:%M:%S ", tm_now);
	strcpy(str_time, datetime);
}


void InvertUint8(unsigned char *DesBuf, unsigned char *SrcBuf)
{
    int i;
    unsigned char temp = 0;

    for(i = 0; i < 8; i++)
    {
        if(SrcBuf[0] & (1 << i))
        {
            temp |= 1<<(7-i);
        }
    }
    DesBuf[0] = temp;
}
void InvertUint16(unsigned short *DesBuf, unsigned short *SrcBuf)
{
    int i;
    unsigned short temp = 0;

    for(i = 0; i < 16; i++)
    {
        if(SrcBuf[0] & (1 << i))
        {
            temp |= 1<<(15 - i);
        }
    }
    DesBuf[0] = temp;
}
unsigned short CRC16_IBM(unsigned char *puchMsg, unsigned int usDataLen)  //CRC校验
{
    unsigned short wCRCin = 0x0000;
    unsigned short wCPoly = 0x8005;
    unsigned char wChar = 0;

    while (usDataLen--)
    {
        wChar = *(puchMsg++);
        InvertUint8(&wChar, &wChar);
        wCRCin ^= (wChar << 8);

		int i;
        for(i = 0; i < 8; i++)
        {
            if(wCRCin & 0x8000)
            {
                wCRCin = (wCRCin << 1) ^ wCPoly;
            }
            else
            {
                wCRCin = wCRCin << 1;
            }
        }
    }
    InvertUint16(&wCRCin,&wCRCin);
    return (wCRCin) ;
}


int ASCIItoNum(char a){               //ASCII码转int数字函数
	if(a >= '0' && a <= '9') return (a-'0');
	else return (a-'7');
}


// static void my_handler(int sig){  //捕获ctl+c的函数
// 	breakFlag = 1;
// }
