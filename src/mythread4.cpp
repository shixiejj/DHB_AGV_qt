#include "mythread.h"
#include "mythread2.h"
#include "mythread3.h"
#include "mythread4.h"
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QTime>
#include <QDebug>
#include <sys/time.h>
#include <qelapsedtimer.h>

double x4  = 0;
double yy4 = 0;
double theta4 = 0  ;
int p4  = 0 ;//小车取货，送货，回城状态

MyThread4::MyThread4(QObject *parent ):
 QThread(parent)
{
     stopped = false;
}

void MyThread4::run()
{

    while(!stopped)
    {
        QElapsedTimer mstimer;
        mstimer.start();
        QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\_4.txt");//C:\\Users\\Tsx-Y\\Desktop\\dhblab_meta-main\\recv_cache.txt

        //设置打开方式
        file.open(QIODevice::ReadOnly);
        QString string;
        string = file.readAll();
        int length4 = string.length();
        QStringList strList = string.split(",",QString::SkipEmptyParts);
        int abc4 = strList.size();
        if(abc4 == 13)
        {
        tro_num4 = strList[2].toDouble();
        if(tro_num4 == 4)
        {
        //数据更新
        x4       = strList[4].toDouble()*100;
        yy4       = 800 - strList[5].toDouble()*100;
        theta4   = -strList[6].toDouble();
        p4       = strList[10].toDouble();
        //qDebug()<<QString("in MyThread: %1").arg(x3);
        //qDebug()<<QString("x3 = : %1,yy3 = : %2,theta3 = :%3").arg(strList[5]).arg(strList[6]).arg(strList[7]);
        }
        //msleep(0.1);
        float time =(double)mstimer.nsecsElapsed()/(double)1000000;
        //qDebug()<<"2时间："<<time;
        }
    }
    stopped = false;

}
void MyThread4::stop()
{
    stopped = true;
}

