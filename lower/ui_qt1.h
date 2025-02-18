/********************************************************************************
** Form generated from reading UI file 'qt1.ui'
**
** Created: Thu Apr 18 00:01:18 2024
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT1_H
#define UI_QT1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qt1
{
public:
    QLabel *lb_time;
    QLabel *lb_pic;
    QLabel *label_camera;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_prev;
    QPushButton *pb_next;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_history;
    QPushButton *pb_del;
    QPushButton *pb_open;
    QPushButton *pb_start;
    QComboBox *comboBox;
    QLabel *lb_num;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *rb_resistance;
    QRadioButton *rb_image;
    QLabel *lb_R;

    void setupUi(QDialog *Qt1)
    {
        if (Qt1->objectName().isEmpty())
            Qt1->setObjectName(QString::fromUtf8("Qt1"));
        Qt1->resize(480, 272);
        lb_time = new QLabel(Qt1);
        lb_time->setObjectName(QString::fromUtf8("lb_time"));
        lb_time->setGeometry(QRect(10, 240, 171, 20));
        lb_pic = new QLabel(Qt1);
        lb_pic->setObjectName(QString::fromUtf8("lb_pic"));
        lb_pic->setGeometry(QRect(10, 10, 271, 201));
        label_camera = new QLabel(Qt1);
        label_camera->setObjectName(QString::fromUtf8("label_camera"));
        label_camera->setGeometry(QRect(290, 10, 171, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_camera->setFont(font);
        layoutWidget = new QWidget(Qt1);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(290, 190, 181, 36));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pb_prev = new QPushButton(layoutWidget);
        pb_prev->setObjectName(QString::fromUtf8("pb_prev"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Ubuntu Condensed"));
        font1.setBold(true);
        font1.setWeight(75);
        pb_prev->setFont(font1);

        horizontalLayout->addWidget(pb_prev);

        pb_next = new QPushButton(layoutWidget);
        pb_next->setObjectName(QString::fromUtf8("pb_next"));
        pb_next->setFont(font1);

        horizontalLayout->addWidget(pb_next);

        layoutWidget1 = new QWidget(Qt1);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(190, 230, 281, 36));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pb_history = new QPushButton(layoutWidget1);
        pb_history->setObjectName(QString::fromUtf8("pb_history"));
        pb_history->setFont(font1);

        horizontalLayout_2->addWidget(pb_history);

        pb_del = new QPushButton(layoutWidget1);
        pb_del->setObjectName(QString::fromUtf8("pb_del"));
        pb_del->setFont(font1);

        horizontalLayout_2->addWidget(pb_del);

        pb_open = new QPushButton(layoutWidget1);
        pb_open->setObjectName(QString::fromUtf8("pb_open"));
        pb_open->setFont(font1);

        horizontalLayout_2->addWidget(pb_open);

        pb_start = new QPushButton(Qt1);
        pb_start->setObjectName(QString::fromUtf8("pb_start"));
        pb_start->setGeometry(QRect(290, 50, 181, 31));
        pb_start->setFont(font1);
        comboBox = new QComboBox(Qt1);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(290, 110, 61, 21));
        comboBox->setFont(font1);
        lb_num = new QLabel(Qt1);
        lb_num->setObjectName(QString::fromUtf8("lb_num"));
        lb_num->setGeometry(QRect(10, 220, 51, 21));
        layoutWidget_3 = new QWidget(Qt1);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(360, 90, 116, 55));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        rb_resistance = new QRadioButton(layoutWidget_3);
        rb_resistance->setObjectName(QString::fromUtf8("rb_resistance"));

        verticalLayout_3->addWidget(rb_resistance);

        rb_image = new QRadioButton(layoutWidget_3);
        rb_image->setObjectName(QString::fromUtf8("rb_image"));

        verticalLayout_3->addWidget(rb_image);

        lb_R = new QLabel(Qt1);
        lb_R->setObjectName(QString::fromUtf8("lb_R"));
        lb_R->setGeometry(QRect(290, 160, 181, 20));

        retranslateUi(Qt1);

        QMetaObject::connectSlotsByName(Qt1);
    } // setupUi

    void retranslateUi(QDialog *Qt1)
    {
        Qt1->setWindowTitle(QApplication::translate("Qt1", "Dialog", 0, QApplication::UnicodeUTF8));
        lb_time->setText(QString());
        lb_pic->setText(QString());
        label_camera->setText(QApplication::translate("Qt1", "Data Collection", 0, QApplication::UnicodeUTF8));
        pb_prev->setText(QApplication::translate("Qt1", "Prev", 0, QApplication::UnicodeUTF8));
        pb_next->setText(QApplication::translate("Qt1", "Next", 0, QApplication::UnicodeUTF8));
        pb_history->setText(QApplication::translate("Qt1", "OpenHis", 0, QApplication::UnicodeUTF8));
        pb_del->setText(QApplication::translate("Qt1", "Delete", 0, QApplication::UnicodeUTF8));
        pb_open->setText(QApplication::translate("Qt1", "Open", 0, QApplication::UnicodeUTF8));
        pb_start->setText(QApplication::translate("Qt1", "Start", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Qt1", "1s", 0, QApplication::UnicodeUTF8)
        );
        lb_num->setText(QString());
        rb_resistance->setText(QApplication::translate("Qt1", "RISTANCE", 0, QApplication::UnicodeUTF8));
        rb_image->setText(QApplication::translate("Qt1", "IMAGE", 0, QApplication::UnicodeUTF8));
        lb_R->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Qt1: public Ui_Qt1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT1_H
