#include "mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include "global_variables.h"
#include <QDebug>
using namespace std;

void Delay_function(unsigned int msec)
{
    QEventLoop loop;//定义一个新的事件循环
        QTimer::singleShot(msec, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
        loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}

void MainWindow::test1_1(int x, int y)
{

    if((x1 - x < 50 && x1 - x > -50) && (yy1 - (800-y) < 50 && yy1 - (800-y) > -50))
    {

        QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_1.txt");
        file.open(QIODevice::WriteOnly);
        file.write("1,2,");
        file.write(AMR_B1_code[1].toUtf8());
        file.close();
        task_whole_B1 = 0;
        code_send_sta = 1;
        code_sta_e3 = 0;
        qDebug()<<"1车发送第二段指令: "<<AMR_B1_code[1];
    }
}

void MainWindow::test1_2(int x, int y)
{

    if((x1 - x < 50 && x1 - x > -50) && (yy1 - (800-y) < 50 && yy1 - (800-y) > -50))
    {

        QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_1.txt");
        file.open(QIODevice::WriteOnly);
        file.write("1,2,");
        file.write(AMR_B1_code[2].toUtf8());
        file.close();
        code_send_sta = 0;
        end_pot_sta_g1 = 1;
        qDebug()<<"1车发送第三段指令: "<<AMR_B1_code[2];
    }
}

void MainWindow::test2_1(int x, int y)
{

    if((x2 - x < 50 && x2 - x > -50) && (yy2 - (800-y) < 50 && yy2 - (800-y) > -50))
    {

        QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_2.txt");
        file.open(QIODevice::WriteOnly);
        file.write("2,2,");
        file.write(AMR_B2_code[1].toUtf8());
        file.close();
        task_whole_B2 = 0;
        code_send_sta_2 = 1;
        code_sta_e3_2 = 0;
        qDebug()<<"二车第二段代码已发送: "<<AMR_B2_code[1];
    }
}

void MainWindow::test2_2(int x, int y)
{

    if((x2 - x < 50 && x2 - x > -50) && (yy2- (800-y) < 50 && yy2 - (800-y) > -50))
    {

        QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_2.txt");
        file.open(QIODevice::WriteOnly);
        file.write("2,2,");
        file.write(AMR_B2_code[2].toUtf8());
        file.close();
        code_send_sta_2 = 0;
        end_pot_sta_g2 = 1;
        qDebug()<<"二车第三段代码已发送: "<<AMR_B2_code[2];

    }
}

void MainWindow::test3_1(int x, int y)
{

    if((x3 - x < 50 && x3 - x > -50) && (yy3 - (800-y) < 50 && yy3 - (800-y)> -50))
    {

        QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_3.txt");
        file.open(QIODevice::WriteOnly);
        file.write("3,2,");
        file.write(AMR_D1_code[1].toUtf8());
        file.close();
        task_whole_D1 = 0;
        code_send_sta_3 = 1;
        code_sta_c1 = 1;
        qDebug()<<"3车第二段代码已发送: "<<AMR_D1_code[1];
    }
}

void MainWindow::test3_2(int x, int y)
{

    if((x3 - x < 50 && x3 - x > -50) && (yy3 - (800-y) < 50 && yy3 - (800-y) > -50))
    {

        QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_3.txt");
        file.open(QIODevice::WriteOnly);
        file.write("3,2,");
        file.write(AMR_D1_code[2].toUtf8());
        file.close();
        end_pot_sta_b2 = 1;
        code_send_sta_3 = 0;
        qDebug()<<"3车第三段代码已送: "<<AMR_D1_code[2];
        }
}

void MainWindow::test4_1(int x, int y)
{

   if((x4 - x < 50 && x4 - x > -50) && (yy4 - (800-y) < 50 && yy4 - (800-y) > -50))
   {

       QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_4.txt");
       file.open(QIODevice::WriteOnly);
       file.write("4,2,");
       file.write(AMR_D2_code[1].toUtf8());
       file.close();
       task_whole_D2 = 0;
       code_send_sta_4 = 1;
       code_sta_c1_2 = 1;
       qDebug()<<"四车第二段代码已发送: "<<AMR_D2_code[1];
    }
}

void MainWindow::test4_2(int x, int y)
{

    if((x4 - x < 50 && x4 - x > -50) && (yy4 - (800-y) < 50 && yy4 - (800-y) > -50))
    {

        QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_4.txt");
        file.open(QIODevice::WriteOnly);
        file.write("4,2,");
        file.write(AMR_D2_code[2].toUtf8());
        file.close();
        end_pot_sta_c1 = 1;
        code_send_sta_4 = 0;
        qDebug()<<"四车第三段代码已发送: "<<AMR_D2_code[2];
     }
}

double max(double x,double y)
{
     return x > y ? x:y;
}
