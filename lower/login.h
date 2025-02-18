#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    int c,c_sub;
    int logined;
    int mode;        //表示当前选择输入的文本框（0表示Username，1表示Password）
    QString username,password;       //用于存储当前输入的Username和Password内容
    QString text_password_content;   //用于在Password文本框显示*符号
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pb_login_clicked();
    void on_pb_quit_clicked();
    // void on_pb_a_clicked();
    // void on_pb_b_clicked();
    // void on_pb_c_clicked();
    void on_pb_1_clicked();
    void on_pb_2_clicked();
    void on_pb_3_clicked();
    void on_pb_0_clicked();
    void on_pb_4_clicked();
    void on_pb_5_clicked();
    void on_pb_6_clicked();
    void on_pb_7_clicked();
    void on_pb_8_clicked();
    void on_pb_9_clicked();
    void on_pb_clear_clicked();
    void on_pb_input_clicked();

private:
    Ui::Login *ui;

};

#endif // LOGIN_H
