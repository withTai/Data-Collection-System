#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "mythread.h"
#include <QDir>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyThread thread1;
    int RReceiving;
    int RwarningReceiving;
    int photoReceiving;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *){       //必须要重写该paintEvent才能实现绘制历史曲线
            QPainter painter(this);
            painter.drawImage(10,10,history_image);  //此处可设置画布的位置
    }

private:
    Ui::MainWindow *ui;
    QImage history_image;  //画历史曲线图像的画布
    int historyOpened;     //表示当前是否打开了历史数据曲线
    int localOpened;       //表示是否打开了本地图片浏览
    QDir *directory;       //指向操作文件夹目录的对象
    QStringList files;     //存放当前文件夹下所有图片文件名的列表
    int picNum;           //记录当前显示的是第几个图片


public slots:
    void fun_history();     //绘制历史数据曲线的函数
    void fun_ReceivedR(QString);
    void fun_ReceivedRwarning(QString);
    void fun_displayPhoto();
    void fun_photo_choose(QString);

private slots:
    void on_pb_photo_clicked();
    void on_pb_R_clicked();
    void on_pb_Rwarning_clicked();
    void on_pb_connect_clicked();
    void on_pb_open_clicked();
    void on_pb_prev_clicked();
    void on_pb_next_clicked();
    void on_pb_delete_clicked();
    void on_pb_quit_clicked();
};


#endif // MAINWINDOW_H
