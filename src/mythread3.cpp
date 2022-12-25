#include "mythread.h"
#include "mythread2.h"
#include "mythread3.h"
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QTime>
#include <QDebug>
#include <sys/time.h>
#include <qelapsedtimer.h>
//#include "./ui_mainwindow.h"
#include "global_variables.h"

MyThread3::MyThread3(QObject *parent ):
 QThread(parent)
{
     stopped = false;
}

void MyThread3::run()
{

    while(!stopped)
    {
        QElapsedTimer mstimer;
        mstimer.start();
        QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\_3.txt");//C:\\Users\\Tsx-Y\\Desktop\\dhblab_meta-main\\recv_cache.txt

        //设置打开方式
        file.open(QIODevice::ReadOnly);
        QString string;
        string = file.readAll();
        int length3 = string.length();
        QStringList strList = string.split(",",QString::SkipEmptyParts);
        int abc3 = strList.size();
        if(abc3 == 13)
        {
        tro_num3 = strList[2].toDouble();
        if(tro_num3 == 3)
        {
        //数据更新
        x3       = strList[4].toDouble()*100;
        yy3       = 800 - strList[5].toDouble()*100;
        theta3   = -strList[6].toDouble();
        p3       = strList[10].toDouble();
        //qDebug()<<QString("in MyThread: %1").arg(x3);
        //qDebug()<<QString("x3 = : %1,yy3 = : %2,theta3 = :%3").arg(strList[5]).arg(strList[6]).arg(strList[7]);
        }
        msleep(0.1);
        float time =(double)mstimer.nsecsElapsed()/(double)1000000;
        //qDebug()<<"2时间："<<time;
        }
    }
    stopped = false;

}
void MyThread3::stop()
{
    stopped = true;
}

