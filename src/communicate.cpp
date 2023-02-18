/*********************************************
 * 此文件为网络管理部分
 * 包含新车相关通信功能，上线按钮创建通信线程
 * v1.0 添加指令下发和状态接收双线程功能
 * 2022.12.20 添加unity3d程序位置更新
 * 2022.12.21 添加指示灯与连接提醒
*********************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "communicate.h"
#include "global_variables.h"

RecvThread::RecvThread()
{
}

void RecvThread::run()
{
    xt = new XStateClient("192.168.3.120");
    xt->x_connect();
    m_stop=false;//启动线程时令m_stop=false

    while(!m_stop)//循环主体
    {
            string loc_info = xt->get_location();   //获取位置信息
            string task_info = xt->get_task_status();
            QString loc_info_s = QString::fromStdString(loc_info);
            QString task_info_s = QString::fromStdString(task_info);
            //qDebug()<<"ksjs "<<loc_info_s;
            QJsonDocument doc;
            doc = doc.fromJson(loc_info_s.toUtf8());      //生成jsondocument对象,进行类型转换string->qstring->bytearrary
            m_x = doc.object().take("x").toDouble();
            m_y = doc.object().take("y").toDouble();
            m_angle = doc.object().take("angle").toDouble();
            doc = doc.fromJson(task_info_s.toUtf8());
            m_task_status = doc.object().take("task_status").toInt();

            qDebug()<<"x = "<<m_x<<"y = "<<m_y;

            emit recv_value(m_x,m_y,m_angle);
            msleep(300); //线程休眠500ms
    }

//  在  m_stop==true时结束线程任务
    xt->x_close();
    delete xt;
    quit();//相当于  exit(0),退出线程的事件循环
}

void RecvThread::stopThread()
{
    m_stop=true;
}

NetThread::NetThread(QObject *parent) : QObject(parent)
{}

//连接发送端口
void NetThread::connectSend(unsigned short port, QString ip)
{
    m_tcp = new QTcpSocket;
    m_tcp->connectToHost(QHostAddress(ip),port);
}


//发送指令
void NetThread::writeTcpData(quint16 sendCommand, const QByteArray &sendData, quint16 number)
{

    int size = 0;
    uint8_t* headBuf = Q_NULLPTR;
    int headSize = 0;
    SeerData* seerData = Q_NULLPTR;
    if(sendData.isEmpty()){
        headSize = sizeof(SeerHeader);
        headBuf = new uint8_t[headSize];
        seerData = (SeerData*)headBuf;
        size = seerData->setData(sendCommand,Q_NULLPTR,0,number);
    }else{
        std::string json_str = sendData.toStdString();
        headSize = sizeof(SeerHeader) + json_str.length();
        headBuf = new uint8_t[headSize];
        seerData = (SeerData*)headBuf;
        size = seerData->setData(sendCommand,
                                 (uint8_t*)json_str.data(),
                                 json_str.length(),
                                 number);
    }

    m_tcp->write((char*)seerData, size);        //发送tcp数据

    delete[] headBuf;
}

void NetThread::disconnectSend()
{
    m_tcp->close();
    m_tcp->deleteLater();
}


NetThread::~NetThread()
{}

void MainWindow::connect_test()
{
    //仙工tcp测试
    send_task = new QThread;
    send = new  NetThread(this);
    send->moveToThread(send_task);
    connect(this,&MainWindow::startConnectSend,send,&NetThread::connectSend);
    connect(this,&MainWindow::disconnect,send,&NetThread::disconnectSend);
    connect(&recv_task,SIGNAL(recv_value(double,double,double)),this,SLOT(getCarData(double,double,double)));
    connect(this,&MainWindow::writeTcpData,send,&NetThread::writeTcpData);

    //开启线程
    send_task->start();
    ui->startButton_10->setDisabled(false);
    ui->stopButton_10->setDisabled(true);
}

//上线按钮，连接两个端口
void MainWindow::on_startButton_10_clicked()
{
//    QString ip = "192.168.3.120";  //网络页面输入ip地址
//    unsigned short port = 19206;    //发送指令端口
//    emit startConnectSend(port,ip);
//    recv_task.start();
//    ui->startButton_10->setDisabled(true);
//    ui->stopButton_10->setDisabled(false);
//    setStatusLed(ui->status_10,1);
    ui->startButton_10->setEnabled(false);
    ui->stopButton_10->setEnabled(true);
    setStatusLed(ui->status_7,1);
    QString DeviceName = ui->netDevice_10->text();
    QString DeviceIp = ui->netIP_10->text();
    QSqlQuery query;
    QString temp = QString("update devcon set devName = '%1' , devIp = '%2' where number = 7").arg(DeviceName).arg(DeviceIp);
    query.exec(temp);//执行修改信息的操作
}

//下线按钮，解除连接
void MainWindow::on_stopButton_10_clicked()
{
//    recv_task.stopThread();//结束线程的run()函数执行
//    recv_task.wait();//
//    emit disconnect();
//    ui->startButton_10->setDisabled(false);
//    ui->stopButton_10->setDisabled(true);
//    setStatusLed(ui->status_10,0);
    QSqlQuery query;
    QString temp = QString("update devcon set devName = '' , devIp = '' where number = 7");
    query.exec(temp);//执行修改信息的操作
    ui->netDevice_10->setText("");
    ui->netIP_10->setText("");
    setStatusLed(ui->status_7,0);
}

void MainWindow::getCarData(double x,double y,double angle)
{
    ui->xy_pos->setText(QString("（%1,%2）").arg(x).arg(y));
    //更新全局变量坐标
    x1 = x*100;
    yy1 = y*100;
    theta1 = angle;
    //写入文件以更新unity3d小车位置
    QFile file("G:\\QT\\projects\\DHBLAB(4files)\\DHBLAB\\My project_Data\\StreamingAssets\\recv_cache.txt");
    file.open(QIODevice::WriteOnly);
    QString car_status = QString("1,1,1,1,1,%1,%2,%3,1").arg(x).arg(y).arg(angle);  //TODO:设置为字符数组以存储小车状态
    file.write(car_status.toUtf8());
    file.close();
}

//定时接收小车状态信息
void MainWindow::after_connect()
{
   timer5 = new QTimer(this);
   timer5->start(300);
   connect(timer5,SIGNAL(timeout()),this,SLOT(getCarData()));
}

/*****************************************
 * 状态灯切换函数
 * label:要设置的状态灯  color：0红 1绿 2黄
*****************************************/
void MainWindow::setStatusLed(QLabel *label, int color)
{
    QString background = "background-color:";
    switch (color) {
    case 0: //红色
        background += "rgb(255,0,0)";
        break;
    case 1: //绿色
        background += "rgb(0,255,0)";
        break;
    case 2: //黄色
        background += "rgb(255,255,0)";
        break;
    }
    label->setStyleSheet(background);
}



