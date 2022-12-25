#include "mythread.h"
#include "mythread2.h"
#include "global_variables.h"
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QTime>
#include <QDebug>
#include <sys/time.h>
#include <qelapsedtimer.h>

MyThread2::MyThread2(QObject *parent ):
 QThread(parent)
{
     stopped = false;
}


void MyThread2::run()
{
    while(!stopped)
    {
        QElapsedTimer mstimer;
        mstimer.start();
        QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\_2.txt");//C:\\Users\\Tsx-Y\\Desktop\\dhblab_meta_v1\\send_cache.txt

        //设置打开方式
        file.open(QIODevice::ReadOnly);
        QString string;
        string = file.readAll();
        int length2 = string.length();
        QStringList strList = string.split(",",QString::SkipEmptyParts);
        int abc2 = strList.size();
        if(abc2 == 13)
        {
        tro_num2 = strList[2].toDouble();
        if(tro_num2 == 2)
        {
        //数据更新
        x2       = strList[4].toDouble()*100;//坐标变换，x同方向，传过来的数据单位为米，上位机显示的单位为厘米
        yy2       = 800 - strList[5].toDouble()*100;//进行了简单的坐标变换
        theta2   = -strList[6].toDouble();
        p2       = strList[10].toDouble();
        //qDebug()<<QString("in MyThread: %1").arg(x2);
        //qDebug()<<QString("x2 = : %1,yy2 = : %2,theta2 = :%3").arg(strList[5]).arg(strList[5]).arg(strList[5]);
        }
        msleep(1);
        float time =(double)mstimer.nsecsElapsed()/(double)1000000;
        //qDebug()<<"2时间："<<time;
        }
    }
    stopped = false;
}


void MyThread2::stop()
{
    stopped = true;
}

