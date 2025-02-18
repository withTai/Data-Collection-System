#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <QDesktopWidget> //用于窗口居于屏幕中央显示
#include <QDir>           //用于打开本地图片
#include <QFileDialog>    //用于打开本地图片
extern "C"
{ // 表示用C语言编译（当C与C++混合编译时使用）
#include "tcp_server.h"
}

extern char local_file[128];

// 该数组用于记录历史电阻数据（最多50个）
int historyR[50];
int n = 0; // 记录实际采集到的历史数据个数（最多50）

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 表示当前是否正处于接收相关数据的状态
    RReceiving = 0;
    RwarningReceiving = 0;
    photoReceiving = 0;
    localOpened = 0;

    // 设置窗口的背景图
    QPixmap pixmap("./1.jpeg");
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))); // 图片可自适应窗口大小
    this->setPalette(palette);

    // 设置边框
    ui->lb_1->setStyleSheet("background:transparent;border:2px solid white;"); // 2px表示边框宽度
    ui->lb_2->setStyleSheet("background:transparent;border:2px solid white;");
    // ui->lb_3->setStyleSheet("background:transparent;border:2px solid white;");

    // 在TCP连接前不可进行上位机其他操作
    ui->pb_R->setDisabled(true);
    ui->pb_Rwarning->setDisabled(true);
    ui->pb_photo->setDisabled(true);
    ui->lb_pic->setStyleSheet("QLabel{background-color:rgb(255,255,255);}"); // 图像label背景色在没有显示图像时则为黑色

    // 在打开本地图片前不可操作以下按键
    ui->pb_prev->setDisabled(true);
    ui->pb_next->setDisabled(true);
    ui->pb_delete->setDisabled(true);

    // 历史曲线画布初始化
    history_image = QImage(501, 331, QImage::Format_RGB32); // 画布的初始化大小设为281*211，使用32位颜色
    fun_history();

    // 固定窗口大小
    this->setFixedSize(this->size());
    // 使窗口居于屏幕中央显示
    QDesktopWidget *desktop = QApplication::desktop();
    this->move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);

    //    connect(ui->pb_history,SIGNAL(clicked()),this,SLOT(fun_history()));             //按下Refresh History键（用于查看历史数据曲线）
    //    connect(ui->pb_photo,SIGNAL(clicked()),this,SLOT(on_pb_photo_clicked()));       //按下Collect Photo键               ///***使用Qt标准的槽函数定义格式时，不需要自己额外connect，否则按键触发两次***
    //    connect(ui->pb_R,SIGNAL(clicked()),this,SLOT(on_pb_R_clicked()));               //按下Collect R键
    //    connect(ui->pb_Rwarning,SIGNAL(clicked()),this,SLOT(on_pb_Rwarning_clicked())); //按下Collect Rwarning键
    //    connect(ui->pb_connect,SIGNAL(clicked()),this,SLOT(on_pb_connect_clicked()));   //按下Connect键

    connect(&thread1, SIGNAL(ReceivedR(QString)), this, SLOT(fun_ReceivedR(QString))); // 子线程connect调用主线程函数
    connect(&thread1, SIGNAL(ReceivedRwarning(QString)), this, SLOT(fun_ReceivedRwarning(QString)));
    connect(&thread1, SIGNAL(ReceivedPhoto()), this, SLOT(fun_displayPhoto()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(fun_photo_choose(QString))); // 下拉菜单选择
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 接收并保存到本地的图片
void MainWindow::fun_displayPhoto()
{
    if (localOpened == 0)
    { // 若此时正在浏览本地图片，则动态检测上传的图片先不显示
        QString path = "./img/";
        QString s = QString(QLatin1String(local_file));
        path += s;

        //        ui->lb_pic->setPixmap(QPixmap(path));
        //        ui->lb_pic->setScaledContents(1);  //使图片自适应控件lb_pic的大小（使得图片完整显示）
    }
}

// 子线程connect调用主线程函数
void MainWindow::fun_ReceivedR(QString RString)
{
    ui->text_R->setText(RString);

    // 记录阻值历史数据
    int hisR = RString.toUInt();
    if (n < 50)
    { // 若未存满50个数据
        historyR[n] = hisR;
        n++; // n始终表示当前存储的历史数据总个数
    }
    else
    { // 若已存满50个数据
        int i;
        for (i = 0; i < n - 1; i++)
        {
            historyR[i] = historyR[i + 1];
        }
        historyR[n - 1] = hisR;
    }

    fun_history(); // 每次收到新阻值后就刷新画一次
}
void MainWindow::fun_ReceivedRwarning(QString RwarningString)
{
    ui->text_Rwarning->setText(RwarningString);
}

// 按下Collect Photo键
void MainWindow::on_pb_photo_clicked()
{
    if (photoReceiving == 0)
    {
        ask_jpg();
        photoReceiving = 1;
        ui->pb_photo->setText(QApplication::translate("Qt1", "Close Photo", 0)); // 将Collect Photo按键更换显示为Close Photo

        // 采集图片时无法使用本地图片浏览功能按键
        localOpened = 0; // 关闭本地图片浏览功能，此时可以显示传输图像了
        ui->pb_open->setDisabled(true);
        ui->pb_prev->setDisabled(true);
        ui->pb_next->setDisabled(true);
        ui->pb_delete->setDisabled(true);
        ui->comboBox->clear(); // 清空下拉菜单
    }
    else
    {
        ask_jpg();
        photoReceiving = 0;
        ui->pb_photo->setText(QApplication::translate("Qt1", "Collect Photo", 0)); // 将Collect Photo按键更换显示为Close Photo

        // 恢复本地图片浏览功能按键
        ui->pb_open->setDisabled(false);
    }
}

// 按下Collect R键
void MainWindow::on_pb_R_clicked()
{
    if (RReceiving == 0)
    {
        ask_R();
        RReceiving = 1;
        ui->pb_R->setText(QApplication::translate("Qt1", "Close R", 0)); // 将Collect R按键更换显示为Close R
    }
    else
    {
        ask_R();
        RReceiving = 0;
        ui->pb_R->setText(QApplication::translate("Qt1", "Collect R", 0)); // 将Collect R按键更换显示为Close R
    }
}

// 按下Collect Rwarning键
void MainWindow::on_pb_Rwarning_clicked()
{
    if (RwarningReceiving == 0)
    {
        ask_Rwn();
        RwarningReceiving = 1;
        ui->pb_Rwarning->setText(QApplication::translate("Qt1", "Close Rwarning", 0)); // 将Collect Rwarning按键更换显示为Close Rwarning
    }
    else
    {
        ask_Rwn();
        RwarningReceiving = 0;
        ui->pb_Rwarning->setText(QApplication::translate("Qt1", "Collect Rwarning", 0)); // 将Collect Rwarning按键更换显示为Close Rwarning
    }
}

// 按下Connect键
void MainWindow::on_pb_connect_clicked()
{
    if (TCPconnect() == 0)
    {
        // ui->lb_line->setText("On Line");
        ui->pb_R->setDisabled(false);
        ui->pb_Rwarning->setDisabled(false);
        ui->pb_photo->setDisabled(false);
        ui->pb_connect->setDisabled(true); // 不可重复连接
        thread1.start();                   // 开始子线程持续读
    }
    else
    {
        // ui->lb_line->setText("Off Line");
    }
}

// 绘制历史曲线
void MainWindow::fun_history()
{
    // 1 对画布进行填充覆盖，也可以起到清屏作用
    history_image.fill(qRgb(250, 250, 250));

    // 3 创建QPainter
    QPainter painter(&history_image);
    painter.setRenderHint(QPainter::Antialiasing, true); // 设置反锯齿模式，好看一点

    // 4 设置图像位置与大小
    int pointx = 55, pointy = 291;          // 确定坐标轴起点坐标，这里定义(35,191)
    int width = 461 - pointx, height = 256; // 确定坐标轴宽度跟高度 上文定义画布为600X300，宽高依此而定。

    // 5 绘制坐标轴
    painter.drawRect(15, 15, 471, 301);                        // 外围的矩形，从(10,10)起，到(281,211)结束，周围留了5的间隙。
    painter.drawLine(pointx, pointy, width + pointx, pointy);  // 坐标轴x宽度为width
    painter.drawLine(pointx, pointy - height, pointx, pointy); // 坐标轴y高度为height
    srand(time(NULL));

    // 6 获得数据中最大值、最小值
    int max = historyR[0]; // 数组里的最大值
    int min = historyR[0];
    int maxpos = 0, minpos = 0;
    for (int i = 0; i < n; i++)
    {
        if (historyR[i] > max)
        {
            max = historyR[i];
            maxpos = i;
        }
        if (historyR[i] < min)
        {
            min = historyR[i];
            minpos = i;
        }
    }

    // 7 画数据点和折线
    double kx = (double)width / (n - 1); // x轴的系数
    double ky = (double)height / max;    // y方向的比例系数
    QPen pen, penPoint;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    penPoint.setColor(Qt::black);
    penPoint.setWidth(5);
    for (int i = 0; i < n - 1; i++)
    {
        // 由于y轴是倒着的，所以y轴坐标要pointy-a[i]*ky 其中ky为比例系数
        painter.setPen(pen); // 黑色笔用于连线
        painter.drawLine(pointx + kx * i, pointy - historyR[i] * ky, pointx + kx * (i + 1), pointy - historyR[i + 1] * ky);
        painter.setPen(penPoint); // 黑色的笔，用于标记各个点
        painter.drawPoint(pointx + kx * i, pointy - historyR[i] * ky);
    }
    painter.drawPoint(pointx + kx * (n - 1), pointy - historyR[n - 1] * ky); // 绘制最后一个点

    // 8 绘制最大值、最小值（用红色点画最大值、最小值）
    QPen penMaxMin;
    penMaxMin.setColor(Qt::red);
    penMaxMin.setWidth(7);
    painter.setPen(penMaxMin);
    painter.drawPoint(pointx + kx * maxpos, pointy - historyR[maxpos] * ky);                                        // 标记最大值点
    painter.drawPoint(pointx + kx * minpos, pointy - historyR[minpos] * ky);                                        // 标记最小值点
    painter.drawText(pointx + kx * maxpos - kx, pointy - historyR[maxpos] * ky - 5, "max=" + QString::number(max)); // 显示最大最小值文本
    painter.drawText(pointx + kx * minpos - kx, pointy - historyR[minpos] * ky + 15, "min=" + QString::number(min));

    // 9 绘制刻度线
    QPen penDegree;
    penDegree.setColor(Qt::black);
    penDegree.setWidth(2);
    painter.setPen(penDegree);
    // 画x轴刻度线
    for (int i = 0; i < 10; i++) // 分成10份
    {
        // 选取合适的坐标，绘制一段长度为4的直线，用于表示刻度
        painter.drawLine(pointx + (i + 1) * width / 10, pointy, pointx + (i + 1) * width / 10, pointy - 4);
        painter.drawText(pointx + (i + 0.65) * width / 10, pointy + 15, QString::number((int)((i + 1) * ((double)n / 10))));
    }
    // 画y轴刻度线
    double _maStep = (double)max / 10; // y轴刻度间隔需根据最大值来表示
    for (int i = 0; i < 10; i++)
    {
        // 确定一个位置，然后画一条短短的直线表示刻度。
        painter.drawLine(pointx, pointy - (i + 1) * height / 10, pointx + 4, pointy - (i + 1) * height / 10);
        painter.drawText(pointx - 25, pointy - (i + 0.85) * height / 10, QString::number((int)(_maStep * (i + 1))));
    }
    this->update(); //***每次画完图后均需要update来刷新屏幕***
}

// 按下Open键（打开本地图片并显示）
void MainWindow::on_pb_open_clicked()
{
    // 进入本地图片浏览模式
    localOpened = 1;
    ui->pb_prev->setDisabled(false);
    ui->pb_next->setDisabled(false);
    ui->pb_delete->setDisabled(false);
    picNum = 0;

    // 获取图片文件本地路径
    QString directoryPath = QDir::toNativeSeparators(QFileDialog::getExistingDirectory()); // 手动选择本地图片文件夹路径（getOpenFileName表示获取本地文件;getExistingDirectory表示获取本地文件夹）
    directory = new QDir(directoryPath);                                                   // 创建目录对象，并指定操作的目录路径

    // 图片文件过滤
    QStringList filters; // 用于指定过滤出指定文件类型
    filters << "*.jpg"
            << "*.bmp"
            << "*.png"
            << "*.jpeg";                                            // 指定只获取扩展名为这四种的图像文件名
    files = directory->entryList(filters, QDir::Files, QDir::Time); // 获取目录里面的过滤后的文件名

    // 显示图片
    ui->lb_pic->setPixmap(QPixmap(directory->path() + "/" + files[picNum])); // 路径+文件名即可组成资源文件并转换为QPixmap图片格式
    ui->lb_pic->setScaledContents(1);                                        // 使图片自适应控件lb_pic的大小（使得图片完整显示）

    // 更新下拉菜单，显示当前文件夹所有图片
    ui->comboBox->clear();
    ui->comboBox->addItems(files);
}
// 按下Prev键
void MainWindow::on_pb_prev_clicked()
{
    picNum--;
    if (picNum < 0)
        picNum = files.size() - 1; // 若超出第一张图片，则循环跳回最后一张图片

    ui->lb_pic->setPixmap(QPixmap(directory->path() + "/" + files[picNum]));
    ui->lb_pic->setScaledContents(1); // 使图片自适应控件lb_pic的大小（使得图片完整显示）
}
// 按下Next键
void MainWindow::on_pb_next_clicked()
{
    picNum++;
    if (picNum >= files.size())
        picNum = 0; // 若超出最后一张图片，则循环跳回第一张图片

    ui->lb_pic->setPixmap(QPixmap(directory->path() + "/" + files[picNum]));
    ui->lb_pic->setScaledContents(1); // 使图片自适应控件lb_pic的大小（使得图片完整显示）
}
// 按下Delete键
void MainWindow::on_pb_delete_clicked()
{
    // 删除图片
    directory->remove(files[picNum]); // 删除本地图片文件
    files.removeAt(picNum);           // 将被删除的图片文件名从QStringList列表中移除

    // 更新下拉菜单，去掉已经删除了的图片项目
    ui->comboBox->clear();
    ui->comboBox->addItems(files);

    // 显示下一张图片
    picNum++;
    if (picNum < 0)
        picNum = files.size() - 1; // 若超出第一张图片，则循环跳回最后一张图片
    ui->lb_pic->setPixmap(QPixmap(directory->path() + "/" + files[picNum]));
    ui->lb_pic->setScaledContents(1); // 使图片自适应控件lb_pic的大小（使得图片完整显示）
}

// 下拉菜单选择槽函数(下拉菜单选择本地图片)
void MainWindow::fun_photo_choose(QString F)
{ // F为被选中图片的文件名（不包括图片路径）
    if (localOpened == 1)
    {                              // 只有在打开了本地图片浏览功能后才能进行下拉菜单选择图片功能
        picNum = files.indexOf(F); // 更改当前图片翻页的页数
        ui->lb_pic->setPixmap(QPixmap(directory->path() + "/" + F));
        ui->lb_pic->setScaledContents(1); // 使图片自适应控件lb_pic的大小（使得图片完整显示）
    }
}

// 按下Quit键
void MainWindow::on_pb_quit_clicked()
{
    QApplication *app;
    app->exit(0);
}
