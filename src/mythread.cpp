#include "mythread.h"
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QTime>
#include <QDebug>
#include <sys/time.h>
#include <qelapsedtimer.h>
#include <QMetaType>
#include "global_variables.h"

MyThread::MyThread(QObject *parent ):
    QThread(parent)
{
     stopped = false;
}

void MyThread::run()
{

    while(!stopped)
    {
        QElapsedTimer mstimer;
        mstimer.start();
        QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\_1.txt");//C:\\Users\\Tsx-Y\\Desktop\\dhblab_meta-main\\recv_cache.txt
        //设置打开方式
        file.open(QIODevice::ReadOnly);
        QString string;
        string = file.readAll();
        //qDebug()<<string;
        int length = string.length();
        //qDebug()<<length;
        QStringList strList = string.split(",",QString::SkipEmptyParts);

        int abc1 = strList.size();//检测传输数据是否正确位
        if(abc1 == 13)
        {
        tro_num = strList[2].toDouble();
        if(tro_num == 1)
        {        //数据更新
        x1       = strList[4].toDouble()*100;
        yy1      = 800 - strList[5].toDouble()*100;
        theta1   = -strList[6].toDouble();
        p1       = strList[10].toDouble();

        }
        msleep(1000);
        float time =(double)mstimer.nsecsElapsed()/(double)1000000;
        //qDebug()<<"1时间："<<time;
        file.close();
        }
    stopped = false;

        }//while循环结束

}
void MyThread::stop()
{
    stopped = true;
}

