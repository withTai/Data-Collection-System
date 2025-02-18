#include "login.h"
#include "ui_login.h"
#include "qt1.h"
#include "ui_qt1.h"
extern "C"{                      //表示用C语言编译（当C与C++混合编译时使用）
    #include "communication.h"   //**引入TCP通信连接相关函数
}

//在main函数获得的IP参数（用于TCP连接）
extern int mainArgc;
extern char** mainArgv;

//创建主窗口指针
//***必须在全局域内创建该窗口对象，而不能直接在Login的槽函数中创建，否则槽函数结束后会立即将其自动析构***
//***同时在全局域创建时不能直接用Qt1 MD的方式完整创建一个窗口对象(否则报错Must construct a QApplication before a QPaintDevice)，而是只能在全局域内创建其指针Qt1* MD，之后再进行创建对象MD = new Qt1()***
Qt1* MD;

Login::Login(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    username = "";
    password = "";
    mode = 0; //初始默认是先选择输入Username文本框

    //创建主窗口对象，但先不显示
    MD = new Qt1();

    //建立TCP连接(主线程和子线程用不同端口号建立TCP两个连接，顺序不可更换)
    c = TCPconnect(mainArgc,mainArgv);
    c_sub = subTCPconnect(mainArgc,mainArgv);

    //表明当前客户端还没有登录
    logined = 0;

    //设置全屏
    this->setWindowFlags(Qt::Window);
    this->showFullScreen();

}



void Login::on_pb_login_clicked()  //按下Login键的槽函数：登录进入主界面
{
    if(c == 0 && c_sub == 0){          //若之前TCP连接成功则继续
        if(logined == 0){     //***若当前客户端已经登录了则不再重复登录，否则容易导致开发板判定为连续点击了多次登录，即开发板需要按键消抖操作，开发板按键会自动双击!!!!!!!***
            //QString转char*
            QByteArray username1 = username.toLatin1(); //QString先转成QByteArray
            QByteArray password1 = password.toLatin1();
            char* username2 = username1.data();         //QByteArray再转成char*
            char* password2 = password1.data();

            if(TCPlogin(username2,password2) == 0){  //只有登录成功后才会创建并显示主窗口(communication)
                logined = 1;      //表明当前客户端已经登录了
                MD->show();       //显示主窗口
                MD->t3.start(10000);  //登录成功且主窗口打开后便开始进行通讯心跳检测
                MD->thread1.start();  //登录成功且主窗口打开后便开始进行子线程持续读取上位机查询指令
                this->close();        //关闭登录界面（只是关闭显示，没有析构，也可用close）
            }
        }
    }
    else{          //若之前TCP连接失败则此处直接报错并退出程序
        printf("TCP connection failed!\r\n");
        QApplication* app;
        app->exit(0);
    }
}

void Login::on_pb_quit_clicked()   //按下QUit键的槽函数：退出程序
{
    QApplication* app;
    app->exit(0);
}

Login::~Login()
{
    delete ui;
}


void Login::on_pb_1_clicked()
{
        if(mode == 0){   //若当前是Username输入模式
            username = username + "1";
            ui->text_username->setText(username);
        }
        else{            //若当前是Password输入模式
            password = password + "1";

            //显示密码文本框*符号
            text_password_content = "";  //清空字符串
            int i;
            for(i = 0; i < password.length(); i++){   //Password中有多少字符就显示多少*符号
                text_password_content = text_password_content + "*";
            }
            ui->text_password->setText(text_password_content);
        }
}

void Login::on_pb_2_clicked()
{
        if(mode == 0){   //若当前是Username输入模式
            username = username + "2";
            ui->text_username->setText(username);
        }
        else{            //若当前是Password输入模式
            password = password + "2";

            //显示密码文本框*符号
            text_password_content = "";  //清空字符串
            int i;
            for(i = 0; i < password.length(); i++){   //Password中有多少字符就显示多少*符号
                text_password_content = text_password_content + "*";
            }
            ui->text_password->setText(text_password_content);
        }
}

void Login::on_pb_3_clicked()
{
        if(mode == 0){   //若当前是Username输入模式
            username = username + "3";
            ui->text_username->setText(username);
        }
        else{            //若当前是Password输入模式
            password = password + "3";

            //显示密码文本框*符号
            text_password_content = "";  //清空字符串
            int i;
            for(i = 0; i < password.length(); i++){   //Password中有多少字符就显示多少*符号
                text_password_content = text_password_content + "*";
            }
            ui->text_password->setText(text_password_content);
        }
}

void Login::on_pb_4_clicked()
{
        if(mode == 0){   //若当前是Username输入模式
            username = username + "4";
            ui->text_username->setText(username);
        }
        else{            //若当前是Password输入模式
            password = password + "4";

            //显示密码文本框*符号
            text_password_content = "";  //清空字符串
            int i;
            for(i = 0; i < password.length(); i++){   //Password中有多少字符就显示多少*符号
                text_password_content = text_password_content + "*";
            }
            ui->text_password->setText(text_password_content);
        }
}

void Login::on_pb_5_clicked()
{
        if(mode == 0){   //若当前是Username输入模式
            username = username + "5";
            ui->text_username->setText(username);
        }
        else{            //若当前是Password输入模式
            password = password + "5";

            //显示密码文本框*符号
            text_password_content = "";  //清空字符串
            int i;
            for(i = 0; i < password.length(); i++){   //Password中有多少字符就显示多少*符号
                text_password_content = text_password_content + "*";
            }
            ui->text_password->setText(text_password_content);
        }
}

void Login::on_pb_6_clicked()
{
        if(mode == 0){   //若当前是Username输入模式
            username = username + "6";
            ui->text_username->setText(username);
        }
        else{            //若当前是Password输入模式
            password = password + "6";

            //显示密码文本框*符号
            text_password_content = "";  //清空字符串
            int i;
            for(i = 0; i < password.length(); i++){   //Password中有多少字符就显示多少*符号
                text_password_content = text_password_content + "*";
            }
            ui->text_password->setText(text_password_content);
        }
}

void Login::on_pb_7_clicked()
{
        if(mode == 0){   //若当前是Username输入模式
            username = username + "7";
            ui->text_username->setText(username);
        }
        else{            //若当前是Password输入模式
            password = password + "7";

            //显示密码文本框*符号
            text_password_content = "";  //清空字符串
            int i;
            for(i = 0; i < password.length(); i++){   //Password中有多少字符就显示多少*符号
                text_password_content = text_password_content + "*";
            }
            ui->text_password->setText(text_password_content);
        }
}

void Login::on_pb_8_clicked()
{
        if(mode == 0){   //若当前是Username输入模式
            username = username + "8";
            ui->text_username->setText(username);
        }
        else{            //若当前是Password输入模式
            password = password + "8";

            //显示密码文本框*符号
            text_password_content = "";  //清空字符串
            int i;
            for(i = 0; i < password.length(); i++){   //Password中有多少字符就显示多少*符号
                text_password_content = text_password_content + "*";
            }
            ui->text_password->setText(text_password_content);
        }
}

void Login::on_pb_9_clicked()
{
        if(mode == 0){   //若当前是Username输入模式
            username = username + "9";
            ui->text_username->setText(username);
        }
        else{            //若当前是Password输入模式
            password = password + "9";

            //显示密码文本框*符号
            text_password_content = "";  //清空字符串
            int i;
            for(i = 0; i < password.length(); i++){   //Password中有多少字符就显示多少*符号
                text_password_content = text_password_content + "*";
            }
            ui->text_password->setText(text_password_content);
        }
}

void Login::on_pb_0_clicked()
{
        if(mode == 0){   //若当前是Username输入模式
            username = username + "0";
            ui->text_username->setText(username);
        }
        else{            //若当前是Password输入模式
            password = password + "0";

            //显示密码文本框*符号
            text_password_content = "";  //清空字符串
            int i;
            for(i = 0; i < password.length(); i++){   //Password中有多少字符就显示多少*符号
                text_password_content = text_password_content + "*";
            }
            ui->text_password->setText(text_password_content);
        }
}

void Login::on_pb_clear_clicked()
{
        if(mode == 0){   //若当前是Username输入模式
            username = "";
            ui->text_username->setText(username);
        }
        else{            //若当前是Password输入模式
            password = "";

            //显示密码文本框*符号
            text_password_content = "";  //清空字符串
            ui->text_password->setText(text_password_content);
        }
}

void Login::on_pb_input_clicked()
{
        if(mode == 0){   //若当前是Username输入模式
            mode = 1;
            ui->pb_input->setText(QApplication::translate("Qt1", "Password", 0, QApplication::UnicodeUTF8));  //将Username按键更换显示为Password
        }
        else{            //若当前是Password输入模式
            mode = 0;
            ui->pb_input->setText(QApplication::translate("Qt1", "Username", 0, QApplication::UnicodeUTF8));  //将Password按键更换显示为Username
        }
}

