#ifndef QT1_H
#define QT1_H

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QProcess>
#include <QTimer>
#include <QImage>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include "camera.h"
#include "ui_qt1.h"
//#include "dlinklist.h"
#include "mythread.h"

class Qt1: public QDialog,public Ui_Qt1
{
	Q_OBJECT
public:
        QTimer t3;          //通讯心跳包定时(设为public变量便于login类中调用)
        MyThread thread1;   //创建子线程（用于持续读取上位机的查询指令，设为public变量便于login类中调用）
	Qt1(QWidget *parent = 0);
	~Qt1();
	void strip(char *s);
        int judge(char *s);
        void showCapPhoto();
        void paintEvent(QPaintEvent *){       //必须要重写该paintEvent才能实现绘制历史曲线
        // QPainter painter(this);
        // painter.drawImage(0,0,history_image);

    }
    //	void insert_dlinklist(DLIST *d,char *s);

signals:
//	mysig();
	
public slots:
        void fun_time();
        void fun_pic();
        void display_pic();
        void fun_prev();
        void fun_delete();
        void fun_open();
        void fun_cap_open();    //按下Open Cam键槽函数
        void fun_take_photo();  //按下Save键槽函数  
        void fun_refresh_pic();
        void fun_start();       //按下Start键槽函数
        void data_collection(); //数据采集函数
        void SetValue();        //下拉菜单选择槽函数
        void fun_heartbeat();   //网络通讯心跳包槽函数
        void fun_show_history();//绘制历史数据曲线的函数
        void fun_resistance();  //获取阻值
	
private:
        QTimer t1;	    //用于摄像头图像显示定时
        QTimer t2;      //用于数据采集定时
        int fd_adc, ans;
       // int adcValue;   //当前采集到的ADC电阻值
        int len;
        bool isCapOpen;
        Camera* myCamera;
        int width;
        int height;
        double delayTime;   //数据采集周期
        int opened;         //表示是否打开了本地图片
        int started;        //表示是否打开了数据采集
        int historyOpened;  //表示当前是否打开了历史数据曲线
        QImage* m_image;
        //QImage history_image;  //画历史曲线图像的画布
        char Resistance[512], buffer[512];
        unsigned char *frameBufRGB;
        unsigned char *frameBufYUV;
        bool isToSave;
        void fun_clean_pixmap();
        void InitBox();
        int recog(QString, QString);    //动态图像识别
        int detectDynamicChange(QString, QString, int);
};


#endif 
