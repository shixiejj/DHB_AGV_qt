#include "mythread.h"
#include "mythread2.h"
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QTime>
#include <QDebug>
#include <sys/time.h>
#include <qelapsedtimer.h>
#include <sys/time.h>
#include <qelapsedtimer.h>
#include <QMetaType>
double x1  = 0;
double yy1  = 0;
double theta1 = 0  ;
double p1  = 0 ;//小车取货，送货，回城状态
int  k = 0 ;
int  i = 0;
int  j = 0;
int  k1 = 0 ;
int  i1 = 0;
int  jj1 = 0;
//互斥区判断，指令下发的原型函数
//void issue_command(int x,int y,int z,QString str,QString str2,QString str3,QString str4,QString str5,QString str6,QString str7,QString str8,QString str9)
//{

//    //int k;
//    if( x1 - x > -z && x1 - x < z && yy1 - y > -z && yy1 - y < z && j == 0)
//    {
//         i = 1;
//    }
//    else
//    {
//         i = 0;
//    }

//    if( x2 - x > -z && x2 - x < z && yy2 - y > -z && yy2 - y < z && i == 0)
//    {
//         j = 1;
//    }
//    else
//    {
//        j = 0;
//    }

//    if( x1 - x > -z && x1 - x < z && yy1 - y > -z && yy1 - y < z && j == 1)
//    {
//            QFile file("C:\\Users\\lenovo\\Desktop\\dhblab_meta_v1\\send_cache.txt");//dhblab_meta_v1\\send_cache
//            file.open(QIODevice::WriteOnly);
//            file.write(str.toUtf8());//给1车发布停止指令
//            file.close();
//            qDebug()<<"给1车发布停止命令";//"给1车发布停止命令"//1号车发送任务指令：1,2,e3     2号车发送任务指令：2,2,e3       两车相遇：2,0,e3     最后指令：2,2,e3
//            k = 1;
//    }
//    else if(x2 - x > -z && x2 - x < z && yy2 - y > -z && yy2 - y < z && i == 1)
//    {
//        QFile file("C:\\Users\\lenovo\\Desktop\\dhblab_meta_v1\\send_cache.txt");
//        file.open(QIODevice::WriteOnly);
//        file.write(str2.toUtf8());//给2车发布停止指令
//        file.close();
//        qDebug()<<str5;//"给2车发布停止命令";
////        qDebug()<<" j = "<<j<<" i = "<<i;
////        qDebug()<<"x2 = "<<x2<<"yy2 = "<<yy2;
////        qDebug()<<"x1 = "<<x1<<"yy1 = "<<yy1;
//        k = 1;
//    }
//    else if( i == 1 && j == 0 && k ==1)
//    {
//        QFile file("C:\\Users\\lenovo\\Desktop\\dhblab_meta_v1\\send_cache.txt");
//        file.open(QIODevice::WriteOnly);
//        file.write(str3.toUtf8());//1车继续行驶指令
//        file.close();
//        qDebug()<<str6;//"2车离开，1车还在";
//        //k = 0;
//    }
//    else if( i == 0 && j == 1 && k ==1)
//    {
//        QFile file("C:\\Users\\lenovo\\Desktop\\dhblab_meta_v1\\send_cache.txt");
//        file.open(QIODevice::WriteOnly);
//        file.write(str4.toUtf8());//2车继续行驶指令
//        file.close();
//        qDebug()<<str7;//"1车离开，2车还在";
//        //k = 0;
//    }
//    else if(k == 1 && i == 0 && j == 0)
//    {
//        QFile file("C:\\Users\\lenovo\\Desktop\\dhblab_meta_v1\\send_cache.txt");
//        file.open(QIODevice::WriteOnly);
//        file.write("");
//        file.close();
//    qDebug()<<str8;//"区域冲突结束";
//    k = 0;
//    }
//}
//void issue2_command(int x,int y,int z,QString str,QString str2,QString str3,QString str4,QString str5,QString str6,QString str7,QString str8,QString str9)
//{

//    //int k;
//    if( x1 - x > -z && x1 - x < z && yy1 - y > -z && yy1 - y < z && jj1 == 0)
//    {
//         i1 = 1;
//    }
//    else
//    {
//         i1 = 0;
//    }

//    if( x2 - x > -z && x2 - x < z && yy2 - y > -z && yy2 - y < z && i1 == 0)
//    {
//         jj1 = 1;
//    }
//    else
//    {
//        jj1 = 0;
//    }

//    if( x1 - x > -z && x1 - x < z && yy1 - y > -z && yy1 - y < z && jj1 == 1)
//    {
//            QFile file("C:\\Users\\lenovo\\Desktop\\dhblab_meta_v1\\send_cache.txt");//dhblab_meta_v1\\send_cache
//            file.open(QIODevice::WriteOnly);
//            file.write(str.toUtf8());//给1车发布停止指令
//            file.close();
//            qDebug()<<"给1车发布停止命令";//"给1车发布停止命令"//1号车发送任务指令：1,2,e3     2号车发送任务指令：2,2,e3       两车相遇：2,0,e3     最后指令：2,2,e3
//            k1 = 1;
//    }
//    else if(x2 - x > -z && x2 - x < z && yy2 - y > -z && yy2 - y < z && i1 == 1)
//    {
//        QFile file("C:\\Users\\lenovo\\Desktop\\dhblab_meta_v1\\send_cache.txt");
//        file.open(QIODevice::WriteOnly);
//        file.write(str2.toUtf8());//给2车发布停止指令
//        file.close();
//        qDebug()<<str5;//"给2车发布停止命令";

//        k1 = 1;
//    }
//    else if( i1 == 1 && jj1 == 0 && k1 ==1)
//    {
//        QFile file("C:\\Users\\lenovo\\Desktop\\dhblab_meta_v1\\send_cache.txt");
//        file.open(QIODevice::WriteOnly);
//        file.write(str3.toUtf8());//1车继续行驶指令
//        file.close();
//        qDebug()<<str6;//"2车离开，1车还在";
//        //k = 0;
//    }
//    else if( i1 == 0 && jj1 == 1 && k1 ==1)
//    {
//        QFile file("C:\\Users\\lenovo\\Desktop\\dhblab_meta_v1\\send_cache.txt");
//        file.open(QIODevice::WriteOnly);
//        file.write(str4.toUtf8());//2车继续行驶指令
//        file.close();
//        qDebug()<<str7;//"1车离开，2车还在";
//        //k = 0;
//    }
//    else if(k1 == 1 && i1 == 0 && jj1 == 0)
//    {
//        QFile file("C:\\Users\\lenovo\\Desktop\\dhblab_meta_v1\\send_cache.txt");
//        file.open(QIODevice::WriteOnly);
//        file.write("");
//        file.close();
//    qDebug()<<str8;//"区域冲突结束";
//    k1 = 0;
//    }
//}
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
        QFile file("C:\\Users\\lenovo\\Desktop\\dhblab_meta_v1\\recv_cache.txt");//C:\\Users\\lenovo\\Desktop\\dhblab_meta-main\\recv_cache.txt

        //设置打开方式
        file.open(QIODevice::ReadOnly);
        QString string;
        string = file.readAll();
        //qDebug()<<string;
        int length = string.length();
        //qDebug()<<length;
        QStringList strList = string.split(",",Qt::SkipEmptyParts);

        int abc1 = strList.size();//检测传输数据是否正确位
        if(abc1 == 14)
        {
        tro_num = strList[3].toDouble();
        if(tro_num == 1)
        {        //数据更新
        x1       = strList[5].toDouble()*100;
        yy1      = 600 - strList[6].toDouble()*100;
        theta1   = -strList[7].toDouble();
        p1       = strList[11].toDouble();
        //qDebug()<<QString("in MyThread: %1").arg(x1);
        //qDebug()<<QString("x1 = : %1,yy1 = : %2,theta1 = :%3").arg(strList[5]).arg(strList[6]).arg(strList[7]);
        //qDebug()<<"1";
        }
        msleep(1);
        float time =(double)mstimer.nsecsElapsed()/(double)1000000;
        //qDebug()<<"1时间："<<time;
        file.close();
//        if(x1 > 370 && yy1 > 270 && yy1 < 330)
//        {
//            QFile file("C:\\Users\\lenovo\\Desktop\\dhblab_meta_v1\\send_cache.txt");

//           file.open(QIODevice::WriteOnly);
//            //1车进入互斥区，2车禁止进入
//            file.write("1车进入互斥区，2车禁止进入");
//            file.close();
//        }


        }
    stopped = false;

        }//while循环结束

}
void MyThread::stop()
{
    stopped = true;
}

