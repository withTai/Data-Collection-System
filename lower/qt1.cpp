#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <QPainter>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QLineEdit>
#include <QTimer>
#include <pthread.h>
#include <QProcess>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include <fstream>
#include <QDateTime>
#include <QApplication>
#include <QLabel>
#include <QImage>
#include <QVector>
#include <cstdlib>
#include <QFile>
#include "qt1.h"
#include "dlinklist.c"
#include "yuv2rgb.h" //引入图像从YUV转换为RGB格式的函数
#include "camera.h"  //引入摄像头相关函数
#include <QTextCodec>
#include <QStringList>
#include <QTextStream>
extern "C"
{                          // 表示用C语言编译（当C与C++混合编译时使用）
#include "communication.h" //**引入TCP通信连接相关函数
}

// 用于本地图片查询时的页数判断
static int i = 0;

// 该数组用于记录历史电阻数据（最多50个）
QVector<double> rvalues;
int n = 0; // 记录实际采集到的历史数据个数（最多50）

// 在main函数获得的IP参数（用于TCP连接）
extern int mainArgc;
extern char **mainArgv;

// 声明全局变量，方便引用存储路径
QString filepath = "";
QString std_path = ""; // 对照图片存储路径
int FLAG = 1;          // 是否更新对照图片存储路径

// 用于子线程循环读取上位机的查询指令后，标志当前是否进入于Rwarning、R、图片的发送模式
int RwarningStarted = 0;
int RStarted = 0;
int PhotoStarted = 0;
int Dataindex = 1;

// DLIST* Qt1:: p=NULL;
DLIST *p;
DLIST *q;
DLIST head;
void insert_dlinklist(DLIST *d, char *s);
QImage convertToGrayscale(const QImage &image);
QImage resizeImage(const QImage &image, const QSize &newSize);

Qt1::Qt1(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    isCapOpen = false; // 表示当前是否打开了摄像头
    isToSave = false;  // 表示当前是否要存储
    m_image = NULL;
    opened = 0;
    started = 0;
    historyOpened = 0;
    delayTime = 1; // 数据采集周期默认为1s

    QString strAll;
    QStringList strList;        // 创建字符串列表
    QFile file("datatime.txt"); // 文件路径
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
    Dataindex = strList.at(0).toDouble();
    ; // 数据采集周期默认为1s
    qDebug() << "read_filedata:" << Dataindex;

    // 相关初始化函数
    InitBox();
    init_dlinklist(&head);

    // 将各个按键控件均禁用
    pb_prev->setDisabled(true);
    pb_next->setDisabled(true);
    pb_del->setDisabled(true);

    // 配置并创建摄像头对像
    width = 640; // 摄像头采集的图像大小，与开发板显示大小无关
    height = 480;
    myCamera = new Camera("/dev/video0", width, height, 0); // 调用Camera.cpp中的内容
    // 图片缓存数组
    frameBufRGB = new unsigned char[width * height * 3]; // 图像像素点个数乘每个像素点用的字节表示个数（注意YUV格式每个像素点用2个字节表示，RGB用3个字节表示）
    frameBufYUV = new unsigned char[width * height * 2];

    // 设置全屏
    this->setWindowFlags(Qt::Window);
    this->showFullScreen();

    // 信号与槽连接
    connect(pb_prev, SIGNAL(clicked()), this, SLOT(fun_prev()));                 // 按下Prev键
    connect(pb_next, SIGNAL(clicked()), this, SLOT(fun_pic()));                  // 按下Next键
    connect(pb_del, SIGNAL(clicked()), this, SLOT(fun_delete()));                // 按下Delete键
    connect(pb_open, SIGNAL(clicked()), this, SLOT(fun_open()));                 // 按下Open键（打开静态存储的图片）
    connect(&t1, SIGNAL(timeout()), this, SLOT(fun_time()));                     // 定时器1（用于每1s重新读取并显示当前时间）（此处使用t1额外进行摄像头图像刷新，实现视频画面）
    connect(&t2, SIGNAL(timeout()), this, SLOT(data_collection()));              // 定时器2（用于循环数据采集）
    connect(&t3, SIGNAL(timeout()), this, SLOT(fun_heartbeat()));                // 定时器3（用于通讯心跳包检测）
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(SetValue())); // 下拉菜单选择（用于延时拍摄时间选择）
    connect(pb_start, SIGNAL(clicked()), this, SLOT(fun_start()));               // 按下Start键：用于开始数据采集
    connect(pb_history, SIGNAL(clicked()), this, SLOT(fun_show_history()));      // 按下OpenHis键（用于查看历史数据曲线）
}

// 下拉组合菜单初始化设置
void Qt1::InitBox()
{
    comboBox->clear();
    QStringList strList;
    strList << "1s"
            << "0.1s"
            << "0.5s"
            << "3s"
            << "5s";
    comboBox->addItems(strList);
    comboBox->setCurrentIndex(Dataindex);

    QString text = comboBox->currentText();
    QByteArray text1 = text.toLatin1(); // QString先转成QByteArray
    char *text2 = text1.data();
    delayTime = atof(text2);
}

// 下拉菜单选择槽函数:用于设置数据采集频率
void Qt1::SetValue()
{
    if (comboBox->currentText() == "0.1s")
    {
        delayTime = 0.1;
        Dataindex = 1;
    }
    else if (comboBox->currentText() == "0.5s")
    {
        delayTime = 0.5;
        Dataindex = 2;
    }
    else if (comboBox->currentText() == "1s")
    {
        delayTime = 1;
        Dataindex = 0;
    }
    else if (comboBox->currentText() == "3s")
    {
        delayTime = 3;
        Dataindex = 3;
    }
    else
    {
        delayTime = 5;
        Dataindex = 4;
    }
}

// Start按键槽函数，开始或停止数据采集
void Qt1::fun_start()
{
    if (started == 0)
    { // 若当前未打开数据采集
        started = 1;
        pb_start->setText(QApplication::translate("Qt1", "Stop", 0, QApplication::UnicodeUTF8)); // 将Start按键更换显示为Stop
        fun_cap_open();                                                                          // 打开摄像头
        t2.start(delayTime * 1000);                                                              // 开始采集
    }
    else
    { // 若当前已经打开了数据采集
        started = 0;
        pb_start->setText(QApplication::translate("Qt1", "Start", 0, QApplication::UnicodeUTF8)); // 将Stop按键更换显示为Start
        fun_cap_open();                                                                           // 关闭摄像头
        t2.stop();                                                                                // 停止采集
    }
}
// 电阻值采集、报警函数
void Qt1::fun_resistance()
{
    char *adc = "/dev/adc";
    if ((fd_adc = ::open(adc, O_RDWR | O_NOCTTY | O_NDELAY)) < 0)
    {
        printf("open ADC error\n");
        return;
    }
    memset(buffer, 0, sizeof(buffer));
    int len = read(fd_adc, buffer, 10);
    if (len == 0)
    {
        printf("ADC read error\n");
        return;
    }
    ans = atoi(buffer);
    ans = ans * 10000 / 4095;
    // 记录阻值50个
    rvalues.append(ans);
    // timestamps.append(QDateTime::currentDateTime().toTime_t());
    while (rvalues.size() > 50)
    {
        rvalues.remove(0);
        // timestamps.remove(0);
    }
    // 显示阻值
    sprintf(Resistance, "Resistance: %d Ohm", ans);
    lb_R->setText(Resistance);
    // 异常报警
    if (ans > 9000 || ans < 1000)
    {
        rb_resistance->setChecked(true);
        rb_resistance->setStyleSheet("QRadioButton:checked { color: red; }");
    }
    else
    {
        rb_resistance->setChecked(true);
        rb_resistance->setStyleSheet("QRadioButton:checked { color: green; }");
    }
}
// 数据循环采集函数
void Qt1::data_collection()
{
    if (started == 1) // 当按下Start开始采集数据时，进入循环采集数据
    {
        //  采集、显示图片
        fun_take_photo();                           // 保存图片
        char *iophoto = filepath.toLatin1().data(); // 将QString Unicode编码转为字符
        char IOphoto[128] = "/mnt/usb/Test/lower/";
        strcat(IOphoto, iophoto);

        // 采集、显示、记录ADC阻值
        fun_resistance();

        // 向上位机发送数据
        // 判断当前是否需要向上位机发送R，需要则发送
        if (RStarted == 1)
        {
            sendR(ans);
        }
        // 判断当前是否需要向上位机发送Rwarning，需要则发送
        if (RwarningStarted == 1)
        {
            sendRwarning(ans);
        }

        if (FLAG == 0 && PhotoStarted == 1)
        {
            rb_image->setChecked(true);
            rb_image->setStyleSheet("QRadioButton:checked { color: green; }");
        }
        else if (FLAG == 1 && PhotoStarted == 1) // 判断是否更新对照照片
        {
            rb_image->setChecked(true);
            rb_image->setStyleSheet("QRadioButton:checked { color: red; }");

            std_path = filepath;
            FLAG = 0;
        }
        else
        {
            rb_image->setChecked(false);
        }

        //  监测
        int i;
        if ((i = detectDynamicChange(std_path, filepath, 4)) && PhotoStarted == 1)
        {
            FLAG = 1;
            sendPhoto(IOphoto); // 发送异常照片
        }

        // 只要没有点Stop键，则持续循环读取数据
        t2.start(delayTime * 1000); // 课设对延迟拍照没有要求，用其参数来定义发送周期(后边可修改)
    }
    else
    { // 若此时是停止采集状态，则不再循环
        t2.stop();
    }
}

// 网络通讯心跳包槽函数（10s执行一次，若执行更频繁会导致程序卡顿）
void Qt1::fun_heartbeat()
{
    // 若检测到连接断开或错误则退出程序
    if (sendHeartbeat() != 0)
    {
        QApplication *app;
        app->exit(0);
    }

    // 持续检测通讯心跳
    t3.start(10000);
}

// 打开摄像头函数
void Qt1::fun_cap_open()
{
    if (isCapOpen == 0)
    {                               // 若当期摄像头没打开
        myCamera->OpenDevice();     // 打开摄像头
        isCapOpen = 1;              // 表示摄像头已打开
        pb_prev->setDisabled(true); // 摄像头打开时这些按键不能操作
        pb_next->setDisabled(true);
        pb_del->setDisabled(true);
        pb_open->setDisabled(true);
        pb_history->setDisabled(true);

        t1.start(50); // 开始刷新图像实现动态画面（**注意不能用->，只能用.，否则报错）
    }
    else
    {                            // 若当期摄像头已打开
        myCamera->CloseDevice(); // 关闭摄像头
        isCapOpen = 0;           // 表示摄像头已关闭
        if (opened == 1)
        {                                // 之前已经打开过本地图片后才能启用这些按键
            pb_prev->setDisabled(false); // 摄像头关闭时这些按键可以操作
            pb_next->setDisabled(false);
            pb_del->setDisabled(false);
        }
        pb_history->setDisabled(false);
        pb_open->setDisabled(false);

        t1.stop();
    }
    display_pic();
}
// 保存摄像头图像函数
void Qt1::fun_take_photo()
{
    QDateTime time = QDateTime::currentDateTime();
    QString datatime = time.toString("MM-dd-hh-mm-ss"); // 获取当前时间

    QString file_p;
    file_p += datatime; // 图片名称
    file_p += ".jpg";
    filepath = file_p;
    QByteArray a = file_p.toUtf8();
    m_image->save(file_p, "JPG", -1); // 保存图片
    i++;
}
// 显示图片函数（摄像头开启状态时使用）
void Qt1::showCapPhoto()
{
    if (m_image != NULL)
        delete m_image; // 清空图像缓存
    m_image = NULL;
    m_image = new QImage(frameBufRGB, width, height, QImage::Format_RGB888);
    lb_pic->setPixmap(QPixmap::fromImage(*m_image));
}
// 定时器1槽函数(每1s刷新一次):此处使用t1额外进行摄像头图像刷新，实现视频画面
void Qt1::fun_time()
{
    if (isCapOpen == 1)
    {                                                            // 只有在摄像头打开时才进行刷新
        fun_refresh_pic();                                       // 刷新当期图像
        QDateTime d = QDateTime::currentDateTime();              // 获取当期日期时间
        lb_time->setText(d.toString("yyyy-MM-dd-ddd hh:mm:ss")); // 在标签lb_time上显示时间

        t1.start(50); // 只要摄像头打开，则持续循环刷新实现动态画面
    }
    else
    {
        t1.stop();
    }
}
// 刷新当前显示图片的函数（摄像头开启状态时使用）
void Qt1::fun_refresh_pic()
{
    if (!myCamera->GetBuffer(frameBufYUV)) // 获取摄像头采集的图像
    {
        std::cout << "Get Camera Buf error!\n";
        return;
    }
    // TODO:process_image() function is now empty.
    myCamera->process_image(frameBufYUV, frameBufRGB); // 将采集到的YUV格式图像转为RGB格式（调用Camera.cpp中的函数）
    showCapPhoto();                                    // 将新采集的图片显示出来
}

// 五、绘制历史曲线
void Qt1::fun_show_history()
{
    if (historyOpened == 0)
    {
        // 切换历史曲线显示模式
        historyOpened = 1;                                                                             // 表示当前已打开历史数据曲线
        pb_history->setText(QApplication::translate("Qt1", "CloseHis", 0, QApplication::UnicodeUTF8)); // 将OpenHis按键更换显示为CloseHis

        // 暂时隐藏图片label，占用该区域来画历史曲线，关闭相关按键功能
        pb_prev->setDisabled(true);
        pb_next->setDisabled(true);
        pb_del->setDisabled(true);
        pb_open->setDisabled(true);
        pb_start->setDisabled(true);

        // 创建QPainter
        QImage history(270, 200, QImage::Format_ARGB32);
        history.fill(Qt::gray);
        QPainter painter(&history);
        // painter.setRenderHint(QPainter::Antialiasing, true); // 设置反锯齿模式，好看一点

        //  绘制坐标轴
        QPen axispen(Qt::black, 2);
        painter.setPen(axispen);
        painter.drawLine(0, 200, 0, 0);
        painter.drawLine(0, 199, 270, 199);

        // 绘制刻度
        QPen tickpen(Qt::black, 1.8);
        painter.setPen(tickpen);
        painter.setFont(QFont("consolas", 10));
        const int xtick = 270 / 5;
        const int ytick = 200 / 5;
        for (int k = 0, l = 0; k < 50, l <= 270; k += 10, l += xtick)
        {
            painter.drawLine(l, 200, l, 195);
            painter.drawText(l - 7, 195, QString::number(k));
        }
        for (int k = 0, l = 1; k <= 10000, l <= 200; k += 2000, l += ytick)
        {
            painter.drawLine(0, l, 5, l);
            painter.drawText(0, l + 5, QString::number(10000 - k));
        }
        // 绘制点
        QPen pen(Qt::black, 1.5);
        painter.setPen(pen);
        QVector<QPointF> points;
        for (int k = 0; k < rvalues.size(); ++k)
        {
            double x = k * (270.0 / 27);
            double y = 200 - (rvalues[k] * 200 / 10000);
            points.append(QPointF(x, y));
        }
        // 每隔5个点标注一次数据
        for (int k = 0; k < points.size() - 1; ++k)
        {
            if (points.size() > 1)
            {
                painter.drawLine(points[k], points[k + 1]);
            }
            if (k % 5 == 0)
            {
                painter.save();
                painter.translate(points[k] + QPointF(5, -5));
                painter.rotate(70);
                QString valueText = QString::number(rvalues[k]);
                // painter.drawText(points[k] + QPointF(5, -5), valueText);
                painter.drawText(QPointF(0, 0), valueText);
                painter.restore();
            }

            lb_pic->setPixmap(QPixmap::fromImage(history));
            lb_pic->setScaledContents(1);
        }
    }
    else
    {
        // 退出历史曲线显示模式
        historyOpened = 0;                                                                            // 表示当前已关闭历史数据曲线
        pb_history->setText(QApplication::translate("Qt1", "OpenHis", 0, QApplication::UnicodeUTF8)); // 将CloseHis按键更换显示为OpenHis
        fun_clean_pixmap();

        // 图片label显示，相关按钮恢复功能
        if (opened == 1)
        { // 之前已经打开过本地图片后才能启用这些按键
            pb_prev->setDisabled(false);
            pb_next->setDisabled(false);
            pb_del->setDisabled(false);
        }
        pb_open->setDisabled(false);
        pb_start->setDisabled(false);
    }
}

// 按下Next键槽函数
void Qt1::fun_pic()
{
    if (isCapOpen == 0)
    {        // 只有摄像头关闭时才能切换图片
        i++; // 切换到下一张图片
        if (i == (len + 1))
            i = 1; // 若已经是最后一张，则循环到第一张

        p = p->next;
        display_pic(); // 刷新显示图片
    }
}
// 按下Prev键槽函数
void Qt1::fun_prev()
{
    if (isCapOpen == 0)
    {        // 只有摄像头关闭时才能切换图片
        i--; // 切换到上一张图片
        if (i == 0)
            i = len; // 若已经是第一张，则循环到最后一张

        p = p->prev;
        display_pic(); // 刷新显示图片
    }
}
// 显示图片（摄像头关闭状态时使用，可显示静态存储的照片）
void Qt1::display_pic()
{
    QString buf(p->path);
    QPixmap p(buf);
    lb_pic->setPixmap(p);
    lb_pic->setScaledContents(1);
    lb_num->setText(QString::number(i));
}
// 按下Delete键槽函数
void Qt1::fun_delete()
{
    int ret;
    ret = QMessageBox::warning(this, tr("m_image browser"),
                               tr("Are you sure to delete it?"),
                               QMessageBox::Yes | QMessageBox::No,
                               QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        remove(p->path);
        DLIST *r = (&head)->next;
        int n = 1;
        while (r != p)
        {
            n++;
            r = r->next;
        }
        p = p->next;
        del_dlinklist(&head, n);
        if (i == len)
            i--;
        len = legnth_dlinklist(&head);
        display_pic();
    }
}
// 按下Open键槽函数（打开静态存储的图片）
void Qt1::fun_open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/mnt/usb/Test/lower", tr("Images (*.png *.xpm *.jpg)")); // lujing
    printf("open folder!\n");
    if (fileName != NULL)
    {
        init_dlinklist(&head);
        char *str;
        char filename[100] = {0};
        DIR *dp;
        struct dirent *dirp;

        int m = strlen(fileName.toAscii().data());
        str = (char *)malloc(m);
        strcpy(str, fileName.toAscii().data());
        strcpy(filename, str);

        QString buf(fileName.toAscii().data());
        QPixmap first(buf);
        lb_pic->setPixmap(first);
        lb_pic->setScaledContents(1);

        strip(filename);
        dp = opendir(filename);
        while (dirp = readdir(dp))
        {
            if (judge(dirp->d_name) == 1)
            {
                strcat(filename, "/");
                strcat(filename, dirp->d_name);
                printf("%s\n", filename);
                insert_dlinklist(&head, filename);
                filename[strlen(filename) - strlen(dirp->d_name) - 1] = '\0';
            }
        }
        q->next = (&head)->next;
        (&head)->next->prev = q;

        len = legnth_dlinklist(&head);
        int pos = 1;
        DLIST *r = (&head)->next;
        while (strcmp(r->path, str) != 0)
        {
            r = r->next;
            pos++;
        }
        p = r;
        i = pos;
        lb_num->setText(QString::number(i));

        pb_prev->setDisabled(false);
        pb_next->setDisabled(false);
        pb_del->setDisabled(false);

        opened = 1; // 表示已经打开了本地图片
    }

}

// 七、其他功能
void Qt1::strip(char *s)
{
    char *p = s;
    int n = 0;
    while (*p)
    {
        if (*p == '/')
        {
            n++;
        }
        p++;
    }
    if (n == 1)
    {
        s[1] = '\0';
    }
    else
    {
        p--;
        while (*p)
        {
            if (*p == '/')
            {
                *p = '\0';
                break;
            }
            p--;
        }
    }
}
int Qt1::judge(char *s)
{
    int i, len = strlen(s);
    char *p = s;
    if (len < 5)
    {
        return 0;
    }
    else
    {
        while (*p)
        {
            p++;
        }
        for (i = 0; i < 4; i++)
            p--;
        if ((strncmp(p, ".jpg", 4) == 0) || (strncmp(p, ".png", 4) == 0) || (strncmp(p, ".xpm", 4) == 0))
        {
            return 1;
        }
        else
            return 0;
    }
}
void insert_dlinklist(DLIST *d, char *s)
{
    DLIST *r = d;
    q = (DLIST *)malloc(sizeof(DLIST));
    memset(q, 0, sizeof(q));
    strcpy(q->path, s);

    if (r->next == NULL)
    {
        r->next = q;
        q->next = NULL;
    }
    else
    {
        while (r->next != NULL)
        {
            r = r->next;
        }
        r->next = q;
        q->prev = r;
        q->next = NULL;
    }
    printf("insert success\n");
}
Qt1::~Qt1()
{
    delete[] frameBufRGB;
    delete[] frameBufYUV;
    delete m_image;
}
void Qt1::fun_clean_pixmap()
{
    QPixmap p;
    lb_pic->setPixmap(p);
}

QImage convertToGrayscale(const QImage &image)
{
    QImage temp_img(image.size(), QImage::Format_ARGB32);
    for (int i = 0; i < image.width(); i++)
    {
        for (int j = 0; j < image.height(); j++)
        {
            QRgb color = image.pixel(i, j);
            int gray = qGray(color);
            temp_img.setPixel(i, j, qRgba(gray, gray, gray, qAlpha(color)));
        }
    }

    return temp_img;
}

QImage resizeImage(const QImage &image, const QSize &newSize)
{
    return image.scaled(newSize, Qt::KeepAspectRatio, Qt::FastTransformation);
}

int Qt1::detectDynamicChange(QString A, QString B, int stride)
{
    QImage std_image = QImage(A);
    QImage chk_image = QImage(B);
    if (std_image.size() != chk_image.size())
    {
        return 0;
    }

    QImage std_gray_image = convertToGrayscale(std_image);
    QImage chk_gray_image = convertToGrayscale(chk_image);

    int dynamicDetectionFlag = 0;
    int dynamicpoints = 0;

    for (int y = 0; y < std_gray_image.height(); y += stride)
    {
        for (int x = 0; x < std_gray_image.width(); x += stride)
        {
            int gray_std_value = qGray(std_gray_image.pixel(x, y));
            int gray_chk_value = qGray(chk_gray_image.pixel(x, y));
            int diff = std::abs(gray_std_value - gray_chk_value);

            if (diff > 30)
            {
                dynamicpoints = dynamicpoints + 1;
            }
            if (dynamicpoints > 2500)
            {
                dynamicDetectionFlag = 1;
                // 当检测到动态点超过2500个时，直接返回1，不再继续检测
                break;
            }
        }
        if (dynamicDetectionFlag == 1)
        {
            break;
        }
    }
    return dynamicDetectionFlag;
}

QVector<int> calculateHistogram(const QImage &image, int stride)
{
    QVector<int> histogram(256, 0);

    for (int y = 0; y < image.height(); y += stride)
    {
        for (int x = 0; x < image.width(); x += stride)
        {
            int gray_value = qGray(image.pixel(x, y));
            histogram[gray_value]++;
        }
    }

    return histogram;
}

double calculateHistogramIntersection(const QVector<int> &histogram1, const QVector<int> &histogram2)
{
    double intersection = 0;

    for (int i = 0; i < 256; ++i)
    {
        intersection += std::min(histogram1[i], histogram2[i]);
    }

    return intersection;
}

