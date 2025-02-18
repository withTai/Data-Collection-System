/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created: Thu Apr 18 00:01:04 2024
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_login;
    QPushButton *pb_quit;
    QTextBrowser *text_username;
    QTextBrowser *text_password;
    QLabel *label_username;
    QLabel *label_password;
    QLabel *label_title;
    QPushButton *pb_7;
    QPushButton *pb_8;
    QPushButton *pb_9;
    QPushButton *pb_1;
    QPushButton *pb_2;
    QPushButton *pb_3;
    QPushButton *pb_input;
    QPushButton *pb_clear;
    QPushButton *pb_0;
    QPushButton *pb_5;
    QPushButton *pb_4;
    QPushButton *pb_6;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(480, 272);
        horizontalLayoutWidget = new QWidget(Login);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(120, 190, 201, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pb_login = new QPushButton(horizontalLayoutWidget);
        pb_login->setObjectName(QString::fromUtf8("pb_login"));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        pb_login->setFont(font);

        horizontalLayout->addWidget(pb_login);

        pb_quit = new QPushButton(horizontalLayoutWidget);
        pb_quit->setObjectName(QString::fromUtf8("pb_quit"));
        pb_quit->setFont(font);

        horizontalLayout->addWidget(pb_quit);

        text_username = new QTextBrowser(Login);
        text_username->setObjectName(QString::fromUtf8("text_username"));
        text_username->setGeometry(QRect(120, 80, 201, 31));
        text_password = new QTextBrowser(Login);
        text_password->setObjectName(QString::fromUtf8("text_password"));
        text_password->setGeometry(QRect(120, 140, 201, 31));
        label_username = new QLabel(Login);
        label_username->setObjectName(QString::fromUtf8("label_username"));
        label_username->setGeometry(QRect(30, 80, 81, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setWeight(50);
        label_username->setFont(font1);
        label_password = new QLabel(Login);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        label_password->setGeometry(QRect(30, 140, 81, 31));
        label_password->setFont(font1);
        label_title = new QLabel(Login);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setGeometry(QRect(100, 10, 291, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Consolas"));
        font2.setPointSize(17);
        font2.setBold(true);
        font2.setWeight(75);
        label_title->setFont(font2);
        pb_7 = new QPushButton(Login);
        pb_7->setObjectName(QString::fromUtf8("pb_7"));
        pb_7->setGeometry(QRect(350, 110, 21, 21));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Ubuntu Condensed"));
        font3.setBold(true);
        font3.setWeight(75);
        pb_7->setFont(font3);
        pb_8 = new QPushButton(Login);
        pb_8->setObjectName(QString::fromUtf8("pb_8"));
        pb_8->setGeometry(QRect(380, 110, 21, 21));
        pb_8->setFont(font3);
        pb_9 = new QPushButton(Login);
        pb_9->setObjectName(QString::fromUtf8("pb_9"));
        pb_9->setGeometry(QRect(410, 110, 21, 21));
        pb_9->setFont(font3);
        pb_1 = new QPushButton(Login);
        pb_1->setObjectName(QString::fromUtf8("pb_1"));
        pb_1->setGeometry(QRect(350, 170, 21, 21));
        pb_1->setFont(font3);
        pb_2 = new QPushButton(Login);
        pb_2->setObjectName(QString::fromUtf8("pb_2"));
        pb_2->setGeometry(QRect(380, 170, 21, 21));
        pb_2->setFont(font3);
        pb_3 = new QPushButton(Login);
        pb_3->setObjectName(QString::fromUtf8("pb_3"));
        pb_3->setGeometry(QRect(410, 170, 21, 21));
        pb_3->setFont(font3);
        pb_input = new QPushButton(Login);
        pb_input->setObjectName(QString::fromUtf8("pb_input"));
        pb_input->setGeometry(QRect(350, 80, 81, 21));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Consolas"));
        font4.setPointSize(9);
        font4.setBold(true);
        font4.setWeight(75);
        pb_input->setFont(font4);
        pb_clear = new QPushButton(Login);
        pb_clear->setObjectName(QString::fromUtf8("pb_clear"));
        pb_clear->setGeometry(QRect(380, 200, 51, 21));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Consolas"));
        font5.setPointSize(10);
        font5.setBold(true);
        font5.setWeight(75);
        pb_clear->setFont(font5);
        pb_0 = new QPushButton(Login);
        pb_0->setObjectName(QString::fromUtf8("pb_0"));
        pb_0->setGeometry(QRect(350, 200, 21, 21));
        pb_0->setFont(font3);
        pb_5 = new QPushButton(Login);
        pb_5->setObjectName(QString::fromUtf8("pb_5"));
        pb_5->setGeometry(QRect(380, 140, 21, 21));
        pb_5->setFont(font3);
        pb_4 = new QPushButton(Login);
        pb_4->setObjectName(QString::fromUtf8("pb_4"));
        pb_4->setGeometry(QRect(350, 140, 21, 21));
        pb_4->setFont(font3);
        pb_6 = new QPushButton(Login);
        pb_6->setObjectName(QString::fromUtf8("pb_6"));
        pb_6->setGeometry(QRect(410, 140, 21, 21));
        pb_6->setFont(font3);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Form", 0, QApplication::UnicodeUTF8));
        pb_login->setText(QApplication::translate("Login", "Login", 0, QApplication::UnicodeUTF8));
        pb_quit->setText(QApplication::translate("Login", "Quit", 0, QApplication::UnicodeUTF8));
        text_username->setHtml(QApplication::translate("Login", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Ubuntu'; font-size:11pt;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        text_password->setHtml(QApplication::translate("Login", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Ubuntu'; font-size:11pt;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_username->setText(QApplication::translate("Login", "Username:", 0, QApplication::UnicodeUTF8));
        label_password->setText(QApplication::translate("Login", "Password:", 0, QApplication::UnicodeUTF8));
        label_title->setText(QApplication::translate("Login", "Data Collection System", 0, QApplication::UnicodeUTF8));
        pb_7->setText(QApplication::translate("Login", "7", 0, QApplication::UnicodeUTF8));
        pb_8->setText(QApplication::translate("Login", "8", 0, QApplication::UnicodeUTF8));
        pb_9->setText(QApplication::translate("Login", "9", 0, QApplication::UnicodeUTF8));
        pb_1->setText(QApplication::translate("Login", "1", 0, QApplication::UnicodeUTF8));
        pb_2->setText(QApplication::translate("Login", "2", 0, QApplication::UnicodeUTF8));
        pb_3->setText(QApplication::translate("Login", "3", 0, QApplication::UnicodeUTF8));
        pb_input->setText(QApplication::translate("Login", "Username", 0, QApplication::UnicodeUTF8));
        pb_clear->setText(QApplication::translate("Login", "Clear", 0, QApplication::UnicodeUTF8));
        pb_0->setText(QApplication::translate("Login", "0", 0, QApplication::UnicodeUTF8));
        pb_5->setText(QApplication::translate("Login", "5", 0, QApplication::UnicodeUTF8));
        pb_4->setText(QApplication::translate("Login", "4", 0, QApplication::UnicodeUTF8));
        pb_6->setText(QApplication::translate("Login", "6", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
