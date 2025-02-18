#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    QString usname,psword;       //用于存储当前输入的Username和Password内容
    QString text_password_content;   //用于在Password文本框显示*符号
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pb_login_clicked();
    void on_pb_register_clicked();
    void on_pb_quit_clicked();

private:
    Ui::Login *ui;
    int logined;
};

#endif // LOGIN_H
