#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <stdio.h>
#include <QDebug>         //***Qt上调试显示需要用专门的QDebug进行调试才能显示出来***
#include <QDesktopWidget> //用于窗口居于屏幕中央显示
#include <QMessageBox>
#include <QWidget>
#include <QFile>
#include <QTextCodec>
#include <QStringList>
#include <QTextStream>

struct UsrInfo // 用户名的账户和密码信息
{
    char UsrName[20];
    char Psword[20];
};

// 创建主窗口指针
MainWindow *MD;

Login::Login(QWidget *parent) : QWidget(parent),
                                ui(new Ui::Login)
{
    ui->setupUi(this);

    logined = 0;

    // 密码框显示圆点符号
    ui->text_password->setEchoMode(QLineEdit::Password); //***用lineEdit可以自动实现输入文本显示圆点符号，可用于隐藏输入密码的功能***

    // 设置窗口的背景图
    QPixmap pixmap("./1.jpeg");
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))); // 图片可自适应窗口大小
    this->setPalette(palette);

    // 设置窗口固定大小
    this->setFixedSize(this->size());
    // 使窗口居于屏幕中央显示
    QDesktopWidget *desktop = QApplication::desktop();
    this->move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);

    // 连接信号与槽函数（***如果按照如on_pb_login_clicked这样的官方槽函数定义格式时，则不需要再次connect，否则点击按钮时会连续调用两次槽函数***）
    //    connect(ui->pb_login,SIGNAL(clicked()),this,SLOT(on_pb_login_clicked()));  //按下Login键
    //    connect(ui->pb_quit,SIGNAL(clicked()),this,SLOT(on_pb_quit_clicked()));    //按下Quit键
}

Login::~Login()
{
    delete ui;
}

// 按下Login键
void Login::on_pb_login_clicked()
{
    if (logined == 0)
    {
        QString username = ui->text_username->text();
        QByteArray username1 = username.toLatin1(); // QString先转成QByteArray
        char *username2 = username1.data();

        QString password = ui->text_password->text();
        QByteArray password1 = password.toLatin1(); // QString先转成QByteArray
        char *password2 = password1.data();

        QString strAll;
        QStringList strList;       // 创建字符串列表
        QFile file("UsrInfo.txt"); // 文件路径
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            // 把文件所有信息读出来
            QTextCodec *codec = QTextCodec::codecForName("utf8"); // 支持读取中文
            QTextStream stream(&file);
            stream.setCodec(codec); // 输出流的设置
            strAll = stream.readAll();
            //            qDebug()<< strAll;
        }
        file.close();
        strList = strAll.split("\n"); // 换行符来分割.txt文本
        //        qDebug()<< strList;

        int flag = 0;
        //         qDebug()<< strList.size();
        for (int i = 0; i < strList.size(); i++)
        {
            if (i % 3 == 0) // 奇数行为用户名
            {
                if (strcmp(username2, strList.at(i).toStdString().c_str()) == 0 && strcmp(password2, strList.at(i + 1).toStdString().c_str()) == 0) // 验证用户名
                {
                    logined = 1;
                    MD = new MainWindow();
                    MD->show();
                    this->close();
                    flag = 1;
                }
            }
        }
        if (flag == 0)
        {
            QMessageBox mesg;
            mesg.warning(this, "登录失败", "用户名、密码错误!");
        }

        //        if(username == "123" && password == "456"){
        //            logined = 1;
        //            MD = new MainWindow();
        //            MD->show();
        //            this->close();
        //        }
        //        else{       //若输入错误则弹框报错
        //            QMessageBox mesg;
        //            mesg.warning(this,"登录失败","用户名、密码错误!");
        //        }
    }
}

// 按下Register键
void Login::on_pb_register_clicked()
{
    QString username = ui->text_username->text();
    QByteArray username1 = username.toLatin1(); // QString先转成QByteArray
    char *username2 = username1.data();
    QString password = ui->text_password->text();

    QString strAll;
    QStringList strList;       // 创建字符串列表
    QFile file("UsrInfo.txt"); // 文件路径
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // 把文件所有信息读出来
        QTextCodec *codec = QTextCodec::codecForName("utf8"); // 支持读取中文
        QTextStream stream(&file);
        stream.setCodec(codec); // 输出流的设置
        strAll = stream.readAll();
    }
    file.close();
    strList = strAll.split("\n"); // 换行符来分割.txt文本
    //    qDebug()<< strList;

    int flag = 0;
    //     qDebug()<< strList.size();
    for (int i = 0; i < strList.size(); i++)
    {
        if (i % 3 == 0) // 奇数行为用户名
        {

            if (strcmp(username2, strList.at(i).toStdString().c_str()) == 0) // 验证用户名
            {

                usname = "";
                ui->text_username->setText(usname);
                psword = "";
                text_password_content = ""; // 清空字符串
                ui->text_password->setText(text_password_content);
                QMessageBox mesg;
                mesg.warning(this, "注册失败", "用户名已被注册，请重新选择用户名");
                flag = 1;
                break;
            }
        }
    }
    if (flag == 0)
    {
        strList.append(username);
        strList.append(password);
        //        return 1;//注册成功
        QFile p("UsrInfo.txt");
        if (p.open(QFile::WriteOnly | QIODevice::Text))
        {
            QTextStream s(&p);
            for (QString line : strList)
            {
                s << line << "\n";
            }
        }

        usname = "";
        ui->text_username->setText(usname);
        psword = "";
        text_password_content = ""; // 清空字符串
        ui->text_password->setText(text_password_content);
        QMessageBox mesg;
        mesg.warning(this, "注册成功", "注册成功，可进行登录");
    }
}

// 按下Quit键
void Login::on_pb_quit_clicked()
{
    QApplication *app;
    app->exit(0);
}
