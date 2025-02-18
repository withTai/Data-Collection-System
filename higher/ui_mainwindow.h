/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pb_R;
    QPushButton *pb_Rwarning;
    QPushButton *pb_photo;
    QLabel *lb_pic;
    QTextBrowser *text_R;
    QTextBrowser *text_Rwarning;
    QPushButton *pb_connect;
    QPushButton *pb_open;
    QPushButton *pb_prev;
    QPushButton *pb_next;
    QPushButton *pb_delete;
    QLabel *lb_localoperations;
    QLabel *lb_1;
    QPushButton *pb_quit;
    QLabel *lb_collectoperations;
    QLabel *lb_2;
    QComboBox *comboBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1165, 730);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pb_R = new QPushButton(centralwidget);
        pb_R->setObjectName(QString::fromUtf8("pb_R"));
        pb_R->setGeometry(QRect(690, 200, 141, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu Condensed"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        pb_R->setFont(font);
        pb_Rwarning = new QPushButton(centralwidget);
        pb_Rwarning->setObjectName(QString::fromUtf8("pb_Rwarning"));
        pb_Rwarning->setGeometry(QRect(910, 200, 141, 31));
        pb_Rwarning->setFont(font);
        pb_photo = new QPushButton(centralwidget);
        pb_photo->setObjectName(QString::fromUtf8("pb_photo"));
        pb_photo->setGeometry(QRect(800, 260, 141, 31));
        pb_photo->setFont(font);
        lb_pic = new QLabel(centralwidget);
        lb_pic->setObjectName(QString::fromUtf8("lb_pic"));
        lb_pic->setGeometry(QRect(10, 380, 501, 291));
        text_R = new QTextBrowser(centralwidget);
        text_R->setObjectName(QString::fromUtf8("text_R"));
        text_R->setGeometry(QRect(690, 150, 141, 31));
        text_Rwarning = new QTextBrowser(centralwidget);
        text_Rwarning->setObjectName(QString::fromUtf8("text_Rwarning"));
        text_Rwarning->setGeometry(QRect(910, 150, 141, 31));
        pb_connect = new QPushButton(centralwidget);
        pb_connect->setObjectName(QString::fromUtf8("pb_connect"));
        pb_connect->setGeometry(QRect(710, 640, 141, 31));
        pb_connect->setFont(font);
        pb_open = new QPushButton(centralwidget);
        pb_open->setObjectName(QString::fromUtf8("pb_open"));
        pb_open->setGeometry(QRect(880, 510, 141, 31));
        pb_open->setFont(font);
        pb_prev = new QPushButton(centralwidget);
        pb_prev->setObjectName(QString::fromUtf8("pb_prev"));
        pb_prev->setGeometry(QRect(720, 460, 141, 31));
        pb_prev->setFont(font);
        pb_next = new QPushButton(centralwidget);
        pb_next->setObjectName(QString::fromUtf8("pb_next"));
        pb_next->setGeometry(QRect(880, 460, 141, 31));
        pb_next->setFont(font);
        pb_delete = new QPushButton(centralwidget);
        pb_delete->setObjectName(QString::fromUtf8("pb_delete"));
        pb_delete->setGeometry(QRect(720, 510, 141, 31));
        pb_delete->setFont(font);
        lb_localoperations = new QLabel(centralwidget);
        lb_localoperations->setObjectName(QString::fromUtf8("lb_localoperations"));
        lb_localoperations->setGeometry(QRect(820, 350, 311, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Ubuntu Condensed"));
        font1.setPointSize(17);
        font1.setBold(true);
        font1.setWeight(75);
        lb_localoperations->setFont(font1);
        lb_1 = new QLabel(centralwidget);
        lb_1->setObjectName(QString::fromUtf8("lb_1"));
        lb_1->setGeometry(QRect(620, 330, 501, 251));
        pb_quit = new QPushButton(centralwidget);
        pb_quit->setObjectName(QString::fromUtf8("pb_quit"));
        pb_quit->setGeometry(QRect(910, 640, 141, 31));
        pb_quit->setFont(font);
        lb_collectoperations = new QLabel(centralwidget);
        lb_collectoperations->setObjectName(QString::fromUtf8("lb_collectoperations"));
        lb_collectoperations->setGeometry(QRect(820, 80, 351, 41));
        lb_collectoperations->setFont(font1);
        lb_2 = new QLabel(centralwidget);
        lb_2->setObjectName(QString::fromUtf8("lb_2"));
        lb_2->setGeometry(QRect(620, 60, 501, 261));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(720, 410, 301, 21));
        MainWindow->setCentralWidget(centralwidget);
        lb_2->raise();
        lb_1->raise();
        pb_R->raise();
        pb_Rwarning->raise();
        pb_photo->raise();
        lb_pic->raise();
        text_R->raise();
        text_Rwarning->raise();
        pb_connect->raise();
        pb_open->raise();
        pb_prev->raise();
        pb_next->raise();
        pb_delete->raise();
        lb_localoperations->raise();
        pb_quit->raise();
        lb_collectoperations->raise();
        comboBox->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1165, 28));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pb_R->setText(QApplication::translate("MainWindow", "Collect R", nullptr));
        pb_Rwarning->setText(QApplication::translate("MainWindow", "Collect Rwarning", nullptr));
        pb_photo->setText(QApplication::translate("MainWindow", "Collect Photo", nullptr));
        lb_pic->setText(QString());
        pb_connect->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        pb_open->setText(QApplication::translate("MainWindow", "Open", nullptr));
        pb_prev->setText(QApplication::translate("MainWindow", "Prev", nullptr));
        pb_next->setText(QApplication::translate("MainWindow", "Next", nullptr));
        pb_delete->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        lb_localoperations->setText(QApplication::translate("MainWindow", "Local Photos", nullptr));
        lb_1->setText(QString());
        pb_quit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        lb_collectoperations->setText(QApplication::translate("MainWindow", "Collect Data", nullptr));
        lb_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
