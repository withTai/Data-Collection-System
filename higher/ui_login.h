/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QPushButton *pb_login;
    QPushButton *pb_quit;
    QLabel *lb_username;
    QLabel *lb_password;
    QLabel *lb_tittle;
    QLineEdit *text_password;
    QLineEdit *text_username;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QPushButton *pb_register;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(411, 332);
        pb_login = new QPushButton(Login);
        pb_login->setObjectName(QStringLiteral("pb_login"));
        pb_login->setGeometry(QRect(150, 250, 81, 31));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu Condensed"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        pb_login->setFont(font);
        pb_quit = new QPushButton(Login);
        pb_quit->setObjectName(QStringLiteral("pb_quit"));
        pb_quit->setGeometry(QRect(250, 250, 81, 31));
        pb_quit->setFont(font);
        lb_username = new QLabel(Login);
        lb_username->setObjectName(QStringLiteral("lb_username"));
        lb_username->setGeometry(QRect(50, 120, 81, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu Condensed"));
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        lb_username->setFont(font1);
        lb_password = new QLabel(Login);
        lb_password->setObjectName(QStringLiteral("lb_password"));
        lb_password->setGeometry(QRect(50, 180, 81, 31));
        lb_password->setFont(font1);
        lb_tittle = new QLabel(Login);
        lb_tittle->setObjectName(QStringLiteral("lb_tittle"));
        lb_tittle->setGeometry(QRect(100, 40, 221, 31));
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu Condensed"));
        font2.setPointSize(18);
        font2.setBold(true);
        font2.setWeight(75);
        lb_tittle->setFont(font2);
        text_password = new QLineEdit(Login);
        text_password->setObjectName(QStringLiteral("text_password"));
        text_password->setGeometry(QRect(130, 180, 201, 31));
        text_username = new QLineEdit(Login);
        text_username->setObjectName(QStringLiteral("text_username"));
        text_username->setGeometry(QRect(130, 120, 201, 31));
        line = new QFrame(Login);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(20, 300, 371, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(Login);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(10, 20, 20, 291));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(Login);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(380, 20, 20, 291));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(Login);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(20, 10, 371, 21));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        pb_register = new QPushButton(Login);
        pb_register->setObjectName(QStringLiteral("pb_register"));
        pb_register->setGeometry(QRect(50, 250, 81, 31));
        pb_register->setFont(font);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Form", Q_NULLPTR));
        pb_login->setText(QApplication::translate("Login", "Login", Q_NULLPTR));
        pb_quit->setText(QApplication::translate("Login", "Quit", Q_NULLPTR));
        lb_username->setText(QApplication::translate("Login", "Username", Q_NULLPTR));
        lb_password->setText(QApplication::translate("Login", "Password", Q_NULLPTR));
        lb_tittle->setText(QApplication::translate("Login", "Data Acquisition System", Q_NULLPTR));
        pb_register->setText(QApplication::translate("Login", "Register", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
