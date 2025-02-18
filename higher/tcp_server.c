#include "tcp_server.h"


#define MAX_SIZE 1024

//接收的数据缓存
char R[10];      //阻值信息
char Rwn[10];    //报警信息
char local_file[128];

//主线程变量
int sfp, nfp;

//子线程变量
int sfp_sub, nfp_sub;




int TCPconnect()//连接函数（同时建立主线程和子线程两个端口连接）
{
    //1 主线程TCP建立
    socklen_t sin_size;
    struct sockaddr_in s_add,c_add;
    unsigned short portnum=2333;  //端口号2333
    char buffer[100] = {0};
    memset(buffer, 0, sizeof(buffer));   //清空接收缓存
    int recbyte;
	//创建socket网络套接字sfp
	sfp = socket(AF_INET, SOCK_STREAM, 0);   
	if(-1 == sfp)
	{
            printf("TCPconnect: socket fail ! \r\n");
			return -1;
	}
    printf("TCPconnect: socket ok !\r\n");


	//配置IP和端口
	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	s_add.sin_addr.s_addr=htonl(INADDR_ANY);
	s_add.sin_port=htons(portnum);

	//套接字与IP、端口绑定
	if(-1 == bind(sfp,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))   
	{
            printf("TCPconnect: bind fail !\r\n");
			return -1;
	}
    printf("TCPconnect: bind ok !\r\n");

	//侦听客户端的连接请求
	if(-1 == listen(sfp,5))    
	{
            printf("TCPconnect: listen fail !\r\n");
			return -1;
	}
	printf("listen ok\r\n");

	//接收客户端的socket连接请求并建立连接nfp
	sin_size = sizeof(struct sockaddr_in);
	nfp = accept(sfp, (struct sockaddr *)(&c_add), &sin_size);
	if(-1 == nfp)
	{
            printf("TCPconnect: accept fail !\r\n");
			return -1;
	}
//	printf("accept ok!\r\nServer start get connect from %#x : %#x\r\n", ntohl(c_add.sin_addr.s_addr), ntohs(c_add.sin_port));

	//2 子线程TCP建立
    socklen_t sin_size_sub;
    struct sockaddr_in s_add_sub,c_add_sub;
    unsigned short portnum_sub=4666;  //端口号4666
    char buffer_sub[100] = {0};
    memset(buffer_sub, 0, sizeof(buffer_sub));   //清空接收缓存
    int recbyte_sub;
	//创建socket网络套接字sfp
	sfp_sub = socket(AF_INET, SOCK_STREAM, 0);   
	if(-1 == sfp_sub)
	{
            printf("subTCPconnect: socket fail ! \r\n");
			return -1;
	}
    printf("subTCPconnect: socket ok !\r\n");


	//配置IP和端口
	bzero(&s_add_sub,sizeof(struct sockaddr_in));
	s_add_sub.sin_family=AF_INET;
	s_add_sub.sin_addr.s_addr=htonl(INADDR_ANY);
	s_add_sub.sin_port=htons(portnum_sub);

	//套接字与IP、端口绑定
	if(-1 == bind(sfp_sub,(struct sockaddr *)(&s_add_sub), sizeof(struct sockaddr)))   
	{
            printf("subTCPconnect: bind fail !\r\n");
			return -1;
	}
    printf("subTCPconnect: bind ok !\r\n");

	//侦听客户端的连接请求
	if(-1 == listen(sfp_sub,5))    
	{
            printf("subTCPconnect: listen fail !\r\n");
			return -1;
	}
    printf("subTCPconnect: listen ok\r\n");

	//接收客户端的socket连接请求并建立连接nfp
	sin_size_sub = sizeof(struct sockaddr_in);
	nfp_sub = accept(sfp_sub, (struct sockaddr *)(&c_add_sub), &sin_size_sub);
	if(-1 == nfp_sub)
	{
            printf("subTCPconnect: accept fail !\r\n");
			return -1;
	}
//	printf("accept ok!\r\nServer start get connect from %#x : %#x\r\n", ntohl(c_add_sub.sin_addr.s_addr), ntohs(c_add_sub.sin_port));

    //主线程验证客户端请求登录的信号
    printf("TCPlogin: Waiting the client to begin to login.\r\n");
    while(1)
    {
        if(-1 == (recbyte = read(nfp, buffer, sizeof(buffer))))
        {
            printf("TCPlogin: read data fail !\r\n");
            return -1;
        }
        buffer[recbyte]='\0';   //接收的最后一位加上\0变为字符串
        printf("TCPlogin: %s\r\n",buffer);
        sleep(1);

        // 上位机发送1(表示请求登录)
        if(strcmp(buffer,"Asking for permission of login.\r\n") == 0){
            memset(buffer, 0, sizeof(buffer));   //清空接收缓存
            send(nfp, "1\r\n", strlen("1\r\n"), 0);
            sleep(1);
            break;
        }
        // 上位机发送0(表示请求失败)
        else{
            memset(buffer, 0, sizeof(buffer));   //清空接收缓存
            send(nfp, "0\r\n", strlen("0\r\n"), 0);
            sleep(1);
        }
    }

    //主线程验证客户端登录
    //定义字符串类型的接受客户端的用户名和密码
    char* username[20] = {0};
    char* password[20] = {0};

    printf("TCPlogin: Waiting the client to input username and password.\r\n");
    while(1)
    {
        //接收客户端的用户名
        if(-1 == (recbyte = read(nfp, buffer, sizeof(buffer))))
        {
            printf("TCPlogin: read data fail !\r\n");
            return -1;
        }
        buffer[recbyte]='\n';   //接收的最后一位加上\0变为字符串
        buffer[recbyte+1]='\0';
        //将收到的用户名存入username
        strcpy(username,buffer);
        memset(buffer, 0, sizeof(buffer));   //清空接收缓存
        printf("TCPlogin:username received: %s\r\n",username);
        sleep(1);
        send(nfp, "1\r\n", strlen("1\r\n"), 0);
        sleep(1);

        //接收客户端的密码
        if(-1 == (recbyte = read(nfp, buffer, sizeof(buffer))))
        {
            printf("TCPlogin: read data fail !\r\n");
            return -1;
        }
        buffer[recbyte]='\n';   //接收的最后一位加上\0变为字符串
        buffer[recbyte+1]='\0';
        //将收到的用户名存入password
        strcpy(password,buffer);
        memset(buffer, 0, sizeof(buffer));   //清空接收缓存
        printf("TCPlogin:password received: %s\r\n",password);
        sleep(1);
        send(nfp, "1\r\n", strlen("1\r\n"), 0);
        sleep(1);

        //定义用户管理txt文件路径
        char userfile[100] = "UsrInfo.txt";
        //创建字符串列表
        char* strList[100][100] = {0};

        //打开用户管理txt文件
        FILE *fp;
        fp = fopen(userfile,"r");
        if(fp == NULL){
            printf("TCPlogin: open file fail !\r\n");
            return -1;
        }
        printf("TCPlogin: open file ok !\r\n");

        //读取用户管理txt文件
        int i = 0;
        while(!feof(fp)){
            fgets(strList[i],100,fp);
            i++;
        }
        // 打印username及其长度
//        printf("username:%s length:%d",username,strlen(username));
//        printf("password:%s length:%d",password,strlen(password));
        //  打印strList 及其每行的长度
//        int k = 0;
//        for(k = 0;k < i;k++){
//            printf("strList[%d]:%s length:%d",k,strList[k],strlen(strList[k]));
//        }
        fclose(fp);
        printf("TCPlogin: read file ok !\r\n");

        //验证用户名和密码
        int j = 0;
        int flag = 0;
        for(j = 0;j < i;j=j+3){
//            printf("%s",strList[j]);
            if(strcmp(username,strList[j]) == 0){
//                printf("进入循环：%s",strList[j]);
                if(strcmp(password,strList[j+1]) == 0){      
                    flag = 1;
                    break;
                }
            }
        }
        if(flag == 1){
            printf("TCPlogin: login success !\r\n");
            send(nfp, "1\r\n", strlen("1\r\n"), 0);
            sleep(1);
            break;
        }
        else{
            printf("TCPlogin: login fail !\r\n");
            send(nfp, "0\r\n", strlen("0\r\n"), 0);
            sleep(1);
        }
    
        //通过查询userfile路径下的test.txt文件，验证用户名和密码，该txt文件奇数行为用户名，偶数行为密码
        // if(file.open(QIODevice::ReadOnly | QIODevice::Text))    //以只读方式打开文件
        // {
        //     QTextStream in(&file);  //创建文本流
        //     while(!in.atEnd())  //判断是否到文件末尾
        //     {
        //         QString line = in.readLine();  //读取一行
        //         strList.append(line);   //将读取的一行添加到字符串列表中
        //     }
        //     file.close();   //关闭文件
        // }
        // qDebug()<< strList;

        // if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        // {
        //     //把文件所有信息读出来
        //     QTextCodec *codec = QTextCodec::codecForName("utf8");    //支持读取中文
        //     QTextStream stream(&file);
        //     stream.setCodec(codec);     //输出流的设置
        //     strAll = stream.readAll();
        //     qDebug()<< strAll;
        // }
        // file.close();
        // strList = strAll.split("\n");       //换行符来分割.txt文本
        // qDebug()<< strList;

        // 利用字符串列表验证用户名和密码
        // for(int i=0;i<strList.size();i++)
        // {
        //     if(i%3 == 0)    //奇数行为用户名
        //     {
        //         if(strcmp(username,strList.at(i).toStdString().c_str()) == 0)   //验证用户名
        //         {
        //             if(strcmp(password,strList.at(i+1).toStdString().c_str()) == 0)   //验证密码
        //             {
        //                 memset(buffer, 0, sizeof(buffer));   //清空接收缓存
        //                 send(nfp, "1\r\n", strlen("1\r\n"), 0);
        //                 sleep(1);
        //                 //密码验证成功，跳出循环
        //                 break;
        //             }
        //             else
        //             {
        //                 memset(buffer, 0, sizeof(buffer));   //清空接收缓存
        //                 send(nfp, "0\r\n", strlen("0\r\n"), 0);
        //                 sleep(1);
        //                 break;
        //             }
        //         }
        //     }
        // }

    }

    return 0;
}


int subTCPread(){//接收信息函数
    char buffer[1024] = {0};
    memset(buffer, 0, sizeof(buffer));   //清空接收缓存(***buffer分配多少空间，memset清空时就需要清空多少空间，一一对应***)
    int recbyte = 0;

    //接收来自下位机的信息
    if(-1==(recbyte=read(nfp,buffer,sizeof(buffer))))
    {
        memset(buffer, 0, sizeof(buffer));   //清空接收缓存
        printf("subTCPread: read data failed!\r\n");
        if(-1 == send(nfp, "0\r\n", strlen("0\r\n"), 0))
        {
              printf("subTCPread: send data failed!\r\n");
              return -1;
        }
        return -1;
    }
    buffer[recbyte]='\0';   //接收的最后一位加上\0变为字符串
    printf("%s\r\n",buffer);
  
    

    char buf[5];
    strncpy(buf,buffer,2);
    
      if(strcmp(buf,"3n") == 0)
    {
        //打印提示信息
        printf("subTCPread: The data is image!\r\n");
    }

    // strcmp函数的返回值为0时，表示两个字符串相等，返回值为1时，表示两个字符串不相等

    //1 判断是否为心跳包
    if(strcmp(buffer,"1\r\n") == 0)
    {
            memset(buffer, 0, sizeof(buffer));   //清空接收缓存
            send(nfp, "1\r\n", strlen("1\r\n"), 0);        //回应心跳包
            return 1; //返回1
    }
    //2 判断前两位是否为"03"和"04"，是则为阻值信息
    else if(strcmp(buf,"03") == 0 || strcmp(buf,"04") == 0){
            printf("The data is R!\n");
            if(-1==send(nfp, "1\r\n", strlen("1\r\n"), 0)){//向下位机传达收到信号1\r\n
                printf("subTCPread:send data failed!\r\n");
                memset(buffer, 0, sizeof(buffer));   //清空接收缓存
                return -1;
            }

            memset(R, 0, sizeof(R));   //清空R阻值缓存
            strcpy(R,buffer+2); //得到阻值信息
            memset(buffer, 0, sizeof(buffer));   //清空接收缓存
            return 2;//返回2
    }
    //3 判断前两位是否为"12"，是则为报警信息
     else if(strcmp(buf,"12") == 0){
             printf("The data is Rwn!\n");
             if(-1==send(nfp, "1\r\n", strlen("1\r\n"), 0)){//向下位机传达收到信号1\r\n
                     printf("subTCPread: send data failed!\r\n");
                     memset(buffer, 0, sizeof(buffer));   //清空接收缓存
                     return -1;
             }
             memset(Rwn,0,10);  //清空报警信号缓存
             strcpy(Rwn,buffer+2);  //得到报警信号
             memset(buffer, 0, sizeof(buffer));   //清空接收缓存
             return 3;//返回3
    }
    //4 判断接收是否为3n，是则为图片信息
    else if(strcmp(buf,"3n") == 0){
            printf("The data is jpg!\n");
            if(-1==send(nfp, "1\r\n", strlen("1\r\n"), 0)){//向下位机传达收到信号1\r\n
                    printf("subTCPread: send data failed!\r\n");
                    memset(buffer, 0, sizeof(buffer));   //清空接收缓存
                    return -1;
            }
            receive_photo();
            return 4;//返回4
    }
    //5 都不是则是其他信息
    else return 0;//什么都不是返回0
}


//索取信号发送
//1 发送索取‘阻值’信号
int ask_R(){
      send(nfp_sub, "0x00", strlen("0x00"), 0);//向下位机传达索取‘阻值’信号
      return 0;
}

//2 发送索取‘报警信息’信号
int ask_Rwn(){
      send(nfp_sub, "0x01", strlen("0x01"), 0);//向下位机传达索取‘报警信息’信号
      return 0;
}

//3 发送索取‘图片’信号
int ask_jpg()
{
      if (-1 == send(nfp_sub, "0x02", strlen("0x02"), 0))
      { // 向下位机传达索取‘图片’信号
            printf("ask_jpg: send data failed!\r\n");
            return -1;
      }
      return 0;
}

void writetxt_Rwn(char *path , char *buffer){//写入文件函数
    //(1)打开文件。
    printf("111111111111111111111111111111111111");
    int fd = 0;
    if ((fd = open(path, O_RDWR, 0777))<0)
            printf("open %s failed!\n", path);

    //(2)写入文件
    if (-1 == write(fd, buffer, strlen(buffer)))
            perror("write");

    //(3)关闭文件(保存文件)
            close(fd);
}


void receive_photo()
{
    int recbyte;
    char file_len[16] = {0};//文件长度
    char file_name[128] = {0};//文件名称
    char file[144];
    char buf[1024] = {0};//数据缓冲区
    //读取文件大小和文件名称
    read(nfp, file, sizeof(file));
    send(nfp, "1\r\n", strlen("1\r\n"), 0);   //向下位机传达收到信号1\r\n

    strncpy(file_len, file, sizeof(file_len));//取出文件大小
    strncpy(file_name, file+sizeof(file_len), sizeof(file_name));//取出文件名称

    //save photo for display
    strcpy(local_file,file_name);

    printf("ready receive!!!! file name:[%s] file size:[%s] \n",file_name, file_len);

    // sprintf(buf, "%s", file_name);

    //创建新文件
    int fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if(fd < 0){
        printf("open %s failed!\n",file_name);
    }
    int size = atoi(file_len);//文件大小
    int write_len = 0;//记录已写入的字节数

    //接收文件
    while(1)
    {
        bzero(buf, 1024);

        //接收文件数据
        recbyte = read(nfp, buf, sizeof(buf));

        if(strcmp(buf,"finshed!\r\n") == 0)      //判断图片是否发完
        {
            memset(buf, 0, sizeof(buf));   //清空接收缓存
            break;
        }
//        if( recbyte < 1024)
//        {
//            printf("\n [%s] receive file done!!!\n", file_name);
//            break;
//        }

        //将数据写入文件
        write(fd, buf, recbyte);
        write_len += recbyte;//记录写入的字节数
        //接收进度
        printf("receiving %.2f%% \n", (float)write_len/size * 100);
    }

    send(nfp, "1\r\n", strlen("1\r\n"), 0);   //向下位机传达收到信号1\r\n

    close(fd);
}
