#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "device_con.h"
#include "ui_device_con.h"
#include "editwidget.h"
#include "ui_editwidget.h"
#include "ui_editdialog.h"
#include "drawdraw.h"
#include <QPainter>
#include <QTableWidget>
#include <QDebug>
#include <QStringList>
#include <QThread>
#include <QPushButton>
#include <QTimer>
#include "amr_b_dispatch.h"
#include "amr_d_dispatch.h"
#include "global_variables.h"
#include <QMessageBox>
#include <QTime>
#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <math.h>
using namespace std;

//表格刷新数据部分
int etask_ip[5]   = {0,0,0,0,0};
int etask_type[5] = {0,0,0,0,0};
int etask_list[5] = {0,0,0,0,0};
int etask_sta[5]  = {0,0,0,0,0};
int etask_percent[5] = {0,0,0,0,0};
int etask_source[5] = {0,0,0,0,0};
int etask_time[5] = {0,0,0,0,0};

int  button_clicked_sta = 0;//任务按钮按键按下

int con_delay = 0;//判断是否需要往调度函数中加入延时

int curent = 0;//数据库索引

int task_num = 0;

int b1_deliver_x = 0;
int b1_deliver_y = 0;
int b1_destination_x = 0;
int b1_destination_y = 0;

int b2_deliver_x = 0;
int b2_deliver_y = 0;
int b2_destination_x = 0;
int b2_destination_y = 0;

int d1_deliver_x = 0;
int d1_deliver_y = 0;
int d1_destination_x = 0;
int d1_destination_y = 0;

int d2_deliver_x = 0;
int d2_deliver_y = 0;
int d2_destination_x = 0;
int d2_destination_y = 0;



//代码发送需要用到的变量
//1车
int code_send_sta = 0;//1车发送第三段代码的标志位
int task_whole_B1 = 0;//1车发送第二段代码的标志位
int pot_sta_code1_character_sta = 0;//1车获取代码第一段段尾字母
int pot_sta_code2_character_sta = 0;//1车获取第二段段尾字母
int sc_wait_task_01 = 0;//一个大任务分解过程中，两个任务之间配合的变量
//QStringList AMR_B1_code;//1车代码段
QStringList AMR_B2_code;//2车代码段
QString pot_sta_code1_character;//1车获取代码第一段段尾字母
QString pot_sta_code2_character = "";//1车获取第二段段尾字母

//2车
int code_send_sta_2 = 0;//3车发送第三段代码的标志位
int task_whole_B2 = 0;//3车发送第二段代码的标志位
int pot_sta_code1_character_sta_2 = 0;//3车获取代码第一段段尾字母
int pot_sta_code2_character_sta_2 = 0;//3车获取第二段段尾字母
QString pot_sta_code1_character_2;//3车获取代码第一段段尾字母
QString pot_sta_code2_character_2;//3车获取第二段段尾字母
int sc_wait_task_02 = 0;//一个大任务分解过程中，两个任务之间配合的变量

//3车
int code_send_sta_3 = 0;//4车发送第三段代码的标志位
int task_whole_D1 = 0;//4车发送第二段代码的标志位
int pot_sta_code1_character_sta_3 = 0;//4车获取代码第一段段尾字母
int pot_sta_code2_character_sta_3 = 0;//4车获取第二段段尾字母
QString pot_sta_code1_character_3;//4车获取代码第一段段尾字母
QString pot_sta_code2_character_3;//4车获取第二段段尾字母
int sc_wait_task_03 = 0;//一个大任务分解过程中，两个任务之间配合的变量

//4车
int code_send_sta_4 = 0;//1车发送第三段代码的标志位
int task_whole_D2 = 0;//1车发送第二段代码的标志位
QStringList AMR_D1_code;//1车代码段
int sc_wait_task_04 = 0;//一个大任务分解过程中，两个任务之间配合的变量
//2车代码段
int pot_sta_code1_character_sta_4 = 0;//1车获取代码第一段段尾字母
int pot_sta_code2_character_sta_4 = 0;//1车获取第二段段尾字母
QString pot_sta_code1_character_4;//1车获取代码第一段段尾字母
QString pot_sta_code2_character_4 = "";//1车获取第二段段尾字母
QStringList AMR_D2_code;
QStringList AMR_B1_code;

int code_sta_e3 = 1;
int code_sta_c1 = 0;
int code_sta_e3_2 = 1;
int code_sta_c1_2 = 0;

int end_pot_sta_g1 = 0;//1车终点状态位

int end_pot_sta_g2 = 0;//2车终点状态位

int end_pot_sta_c1 = 0;//4车终点状态位

int end_pot_sta_b2 = 0;//3车终点状态位

QElapsedTimer mstimer13;
QElapsedTimer mstimer14;
float time13 = 0;
float time14 = 0;
QElapsedTimer mstimer23;
QElapsedTimer mstimer24;
float time23 = 0;
float time24 = 0;
QElapsedTimer mstimer31;
QElapsedTimer mstimer32;
float time31 = 0;
float time32 = 0;
QElapsedTimer mstimer41;
QElapsedTimer mstimer42;
float time41 = 0;
float time42 = 0;




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(ui_num);

    //系统时间更新于label显示
    timer6 = new QTimer(this);
    timer6->start(1000);
    connect(timer6,&QTimer::timeout,[=](){
           QDateTime current_time = QDateTime::currentDateTime();
           //显示时间，格式为：年-月-日 时：分：秒 周几
           QString DATE = current_time.toString("yyyy-MM-dd");
           QString TIME = current_time.toString("hh:mm:ss");
           //时间显示格式可自由设定，如hh:mm ddd 显示 时：分 周几
           //具体格式见函数QString QDateTime::​toString(const QString & format) const
            ui->Date->setText(DATE);
            ui->Time->setText(TIME);
       });


    //网络连接相关函数
    connect_test();

    /*
    本主进程共有三个线程 线程1为实现通信以及四两小车位置更新
                     线程2为实现任务管理界面，以及发布指令相关的功能
                     线程3为实现数据库以及日志相关的功能
                     考虑到while循环时会影响ui界面的显示，暂时采用定时器开线程
    */

    /* 线程2-列表功能对应的数据库
       本段代码用于初始化数据库功能，原用于任务管理界面人物列表相关功能的实现*/
    //打开数据库
    openTable();

    /* 线程2-列表对应的定时刷新功能的实现
       功能3-1 tsx0301
    本段功能主要用于定时从数据库中读取任务信息，暂时注释
    */
    //表格数据刷新
    timer3 = new QTimer(this);
    timer3->start(100);
   // connect(timer3,SIGNAL(timeout()),this,SLOT(slotTime()));


    /* 线程2-任务管理界面-功能实现
     *tsx020201
     为实现任务管理界面中的核心内部功能-获取数据库中的任务信息之后，
     顺序执行数据库中的任务信息
    */
//   timer4 = new QTimer(this);
//   timer4->start(5000);
//   connect(ui->starttBtn,ui->starttBtn->click(),this,[=](){
//       connect(timer4,SIGNAL(timeout()),this,SLOT(DB_task()));
//   });
//   connect(ui->starttBtn_2,ui->starttBtn_2->click(),this,[=](){
//      timer4->stop();
//   });

    /* 线程1-位置刷新
     * 代码tsx01
    这属于线程1中位置刷新的功能，前面一部分是冲突区域的设定，后面是分别针对四两小车刷新它们相应的位置
    */
//    timer1 = new QTimer(this);
//    timer1->start(100);
//    connect(timer1,&QTimer::timeout,this,[=](){

//        /*功能1-1
//         * tsx0101
//        初始测试时用到的冲突区域规则
//        */
//        /*
//        if( (x1 - 666) > -100 && (x1 - 666) < 100 && (yy1 - 442) > -100 && (yy1 - 442) < 100 && j == 0)
//        {
//             i = 1;
//        }
//        else
//        {
//             i = 0;
//        }

//        if( (x2 - 666) > -100 && (x2 - 666)< 100 && (yy2 - 442) > -100 && (yy2 - 442) < 100 && i == 0)
//        {
//             j = 1;
//        }
//        else
//        {
//            j = 0;
//        }

//        if( (x1 - 666) > -100 && (x1 - 666) < 100 && (yy1 - 442) > -100 && (yy1 - 442) < 100 && j == 1)
//        {
//                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_.txt");//dhblab_meta_v1\\send_cache
//                file.open(QIODevice::WriteOnly);
//                file.write("1,0,h2");//给1车发布停止指令
//                file.close();
//                qDebug()<<"给1车发布停止命令";//"给1车发布停止命令"//1号车发送任务指令：1,2,e3     2号车发送任务指令：2,2,e3       两车相遇：2,0,e3     最后指令：2,2,e3
//                k = 1;
//        }
//        else if((x2 - 666) > -100 && (x2 - 666) < 100 && (yy2 - 442) > -100 && (yy2 - 442) < 100 && i == 1)
//        {
//            QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_.txt");
//            file.open(QIODevice::WriteOnly);
//            file.write("2,0,j2");//给2车发布停止指令
//            file.close();
//            qDebug()<<"给2车发布停止命令";//"给2车发布停止命令";
//    //        qDebug()<<" j = "<<j<<" i = "<<i;
//    //        qDebug()<<"x2 = "<<x2<<"yy2 = "<<yy2;
//    //        qDebug()<<"x1 = "<<x1<<"yy1 = "<<yy1;
//            k = 1;
//        }
//        else if( i == 1 && j == 0 && k ==1)
//        {
//            QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_.txt");
//            file.open(QIODevice::WriteOnly);
//            file.write("1,2,j2");//1车继续行驶指令
//            file.close();
//            qDebug()<<"2车离开，1车还在";//"2车离开，1车还在";
//            //k = 0;
//        }
//        else if( i == 0 && j == 1 && k ==1)
//        {
//            QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_.txt");
//            file.open(QIODevice::WriteOnly);
//            file.write("2,2,j2");//2车继续行驶指令
//            file.close();
//            qDebug()<<"1车离开，2车还在";//"1车离开，2车还在";
//            //k = 0;
//        }
//    //    else if(k == 1 && (((x1-666)<-100||(x1-666)>100)||((yy1-442)<-100||(yy1-442)>100)||((x2-666)<-100||(x2-666)>100)||((yy2-442)<-100||(yy2-442)>100)))
//    //     {
//    //        // qDebug()<<"k = "<<k;
//    //         QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_.txt");
//    //         file.open(QIODevice::WriteOnly);
//    //         file.write("");
//    //         file.close();
//    //     qDebug()<<"j2区域冲突结束";//"区域冲突结束";
//    //     //qDebug()<<"k = "<<k;
//    //     k = 0;
//    //     }



//        //冲突点e3
//        if( (x1 - 170) > -100 && (x1 - 170) < 100 && (yy1 - 300) > -100 && (yy1 - 300) < 100 && jj1 == 0)
//        {
//             i1 = 1;
//        }
//        else
//        {
//             i1 = 0;
//        }

//        if( (x2 - 170) > -100 && (x2 - 170) < 100 && (yy2 - 300) > -100 && (yy2 - 300) < 100 && i1 == 0)
//        {
//             jj1 = 1;
//        }
//        else
//        {
//            jj1 = 0;
//        }

//        if( (x1 - 170) > -100 && (x1 - 170) < 100 && (yy1 - 300) > -100 && (yy1 - 300) < 100 && jj1 == 1)
//       {
//                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_.txt");//dhblab_meta_v1\\send_cache
//                file.open(QIODevice::WriteOnly);
//                file.write("1,0,e3");//给1车发布停止指令
//                file.close();
//                qDebug()<<"给1车发布停止命令";//"给1车发布停止命令"//1号车发送任务指令：1,2,e3     2号车发送任务指令：2,2,e3       两车相遇：2,0,e3     最后指令：2,2,e3
//                k1 = 1;
//        }
//        else if((x2 - 170) > -100 && (x2 - 170) < 100 && (yy2 - 300) > -100 && (yy2 - 300) < 100 && i1 == 1)
//        {
//            QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_.txt");
//            file.open(QIODevice::WriteOnly);
//            file.write("2,0,e3");//给2车发布停止指令
//            file.close();
//            qDebug()<<"给2车发布停止命令";//"给2车发布停止命令";
//            k1 = 1;
//        }
//        else if( i1 == 1 && jj1 == 0 && k1 == 1)
//        {
//           QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_.txt");
//            file.open(QIODevice::WriteOnly);
//            file.write("1,2,e3");//1车继续行驶指令
//            file.close();
//            qDebug()<<"2车离开，1车还在";//"2车离开，1车还在";
//            //k = 0;
//        }
//        else if( i1 == 0 && jj1 == 1 && k1 == 1)
//        {
//            QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_.txt");
//            file.open(QIODevice::WriteOnly);
//            file.write("2,2,e3");//2车继续行驶指令
//            file.close();
//            qDebug()<<"1车离开，2车还在";//"1车离开，2车还在";
//            //k = 0;
//       }*/

//    /* 线程1-小车位置刷新
//     * tsx0102
//    功能1-2 实现四辆小车位置刷新
//    */
//        QFile file1("D:\\t\\dhblab_meta_socket\\storage\\devices\\_1.txt");//D:\\t\\dhblab_meta_socket\\storage\\devices\\_1.txt
//            //设置打开方式
//        file1.open(QIODevice::ReadOnly);
//        QString string1;
//        string1 = file1.readAll();

//        //double length3 = string.length();
//        QStringList strList1 = string1.split(",", QString::SkipEmptyParts);
//        int abc1 = strList1.size();//检测数组长度用来判断传输的数据是否正确

//        if (abc1 == 13)
//        {
//            //tro_net  = strList[4].toDouble()
//            //小车编号,网络,x（4位小数）,y（4位小数） ,角度（4位小数）,速度（4位小数） ,角速度（4位小数）,电量（9-12）int ,状态（1/2/0） ,负载（0/1),

//            tro_num = strList1[2].toDouble();
//            //qDebug()<<"程序进入中间端口";
//            tro_net = strList1[3].toDouble();

//            if (tro_num == 1)
//            {
//                //qDebug()<<"程序进入最里端";
//                tro_net = strList1[3].toDouble();
//                ax1 = strList1[4].toDouble();
//                ay1 = strList1[5].toDouble();
//                atheta1 = strList1[6].toDouble();
//                tro_ele = strList1[9].toDouble();
//                ap1 = strList1[10].toDouble();
//                tro_load = strList1[11].toDouble();
//                //ui->xy_pos->setText(QString("（%1，%2）").arg(ax1).arg(ay1));
//            }
//        }
//        file1.close();

//        QFile file2("D:\\t\\dhblab_meta_socket\\storage\\devices\\_2.txt");//D:\\t\\dhblab_meta_socket\\storage\\devices\\_2.txt
//            //设置打开方式
//        file2.open(QIODevice::ReadOnly);
//        QString string2;
//        string2 = file2.readAll();
//        QStringList strList2 = string2.split(",", QString::SkipEmptyParts);
//        int abc2 = strList2.size();//检测数组长度用来判断传输的数据是否正确

//        if (abc2 == 13)
//        {

//            tro_num2 = strList2[2].toDouble();
//            //qDebug()<<"程序进入中间端口";
//            tro_net2 = strList2[3].toDouble();

//            if (tro_num2 == 2)
//            {
//                //qDebug()<<"程序进入最里端";
//                tro_net2 = strList2[3].toDouble();
//                ax2= strList2[4].toDouble();
//                ay2 = strList2[5].toDouble();
//                atheta2 = strList2[6].toDouble();
//                tro_ele2 = strList2[9].toDouble();
//                ap2 = strList2[10].toDouble();
//                tro_load2 = strList2[11].toDouble();
//                ui->xy_pos2->setText(QString("（%1，%2）").arg(ax2).arg(ay2));
//            }
//        }
//        file2.close();

//        QFile file3("D:\\t\\dhblab_meta_socket\\storage\\devices\\_3.txt");//D:\\t\\dhblab_meta_socket\\storage\\devices\\_1.txt
//            //设置打开方式
//        file3.open(QIODevice::ReadOnly);
//        QString string3;
//        string3 = file3.readAll();

//        //double length3 = string.length();
//        QStringList strList3 = string3.split(",", QString::SkipEmptyParts);
//        int abc3 = strList3.size();//检测数组长度用来判断传输的数据是否正确

//        if (abc3 == 13)
//        {

//            tro_num3 = strList3[2].toDouble();
//            //qDebug()<<"小车编号："<<tro_num3;
//            tro_net3 = strList3[3].toDouble();

//            if (tro_num3 == 3)
//            {
//                //qDebug()<<"程序进入最里端";
//                tro_net3 = strList3[3].toDouble();
//                ax3= strList3[4].toDouble();
//                ay3 = strList3[5].toDouble();
//                atheta3 = strList3[6].toDouble();
//                tro_ele3 = strList3[9].toDouble();
//                ap3 = strList3[10].toDouble();
//                tro_load3 = strList3[11].toDouble();
//                ui->xy_pos3->setText(QString("（%1，%2）").arg(ax3).arg(ay3));
//            }
//        }
//        file3.close();

//        QFile file4("D:\\t\\dhblab_meta_socket\\storage\\devices\\_4.txt");//D:\\t\\dhblab_meta_socket\\storage\\devices\\_1.txt
//            //设置打开方式
//        file4.open(QIODevice::ReadOnly);
//        QString string4;
//        string4 = file4.readAll();
//        //double length3 = string.length();
//        QStringList strList4 = string4.split(",", QString::SkipEmptyParts);
//        int abc4 = strList4.size();//检测数组长度用来判断传输的数据是否正确

//        if (abc4 == 13)
//        {

//            tro_num4 = strList4[2].toDouble();
//            //qDebug()<<"程序进入中间端口";
//            tro_net4 = strList4[3].toDouble();

//            if (tro_num4 == 4)
//            {
//                //qDebug()<<"程序进入最里端";
//                tro_net4 = strList4[3].toDouble();
//                ax4= strList4[4].toDouble();
//                ay4 = strList4[5].toDouble();
//                atheta4 = strList4[6].toDouble();
//                tro_ele4 = strList4[9].toDouble();
//                ap4 = strList4[10].toDouble();
//                tro_load4 = strList4[11].toDouble();
//                ui->xy_pos4->setText(QString("（%1，%2）").arg(ax4).arg(ay4));
//            }
//        }
//        file4.close();

//});//定时器结束

    /*线程2-任务管理
    实现小车位置判断以及指令发送，属于任务管理界面的基础功能
    逻辑架构介绍（代码：tsx0201）:
            01第一步-通过主文件底下的槽函数获取输入的参数，下发第一个任务 槽函数名为：on_s_task1_Button_clicked()，在底部大概2200行位置
            02第二步-分配好整个任务的第一部分任务之后，获取节点代码信息用于定时器部分小车位置的判断，以及指令的发送
            03第三步-获取一俩小车的信息之后，利用task_whole_B2类似代码开启线程
            04第四步-通过一连串的if判断小车整个任务中第一个任务的三段中的第一段终点信息pot_sta_code1_character，然后针对相应信息，输入下一段任务的代码，也就是三段中的第二段任务
            05第五步-小车在完成第二段任务的过程中，会路过一个触发点，这个触发点会引发整个任务中第二个小车任务的分配，以及到达第一个小车第二段任务的终点，
            06第六步-然后是给第一两小车最后一段代码让它执行完任务回到初始点，第二辆小车开始执行任务，通过类似第一辆小车的功能，重复02,03,04步,然后结束任务。
    */
    timer2 = new QTimer(this);
    timer2->start(500);
    connect(timer2,&QTimer::timeout,this,[=](){

        /*线程2- 04步
         * tsx020104
        -通过一连串的if判断小车整个任务中第一个任务的三段中的第一段终点信息pot_sta_code1_character，
         然后针对相应信息，输入下一段任务的代码，也就是三段中的第二段任务
         这个循环一直在检测执行，只要状态位变化
        */
        //1车判断指令发送-检测第一段任务，发送第二段任务
        if (task_whole_B1 == 1)//判断线程状态为是否开启
        {
            //con_delay_function(1000);
            if(pot_sta_code1_character == "s4")//小车第一段任务终点字母代号，在槽函数中获取的
               {
                test1_1(s4_x, s4_y);
              }
            if(pot_sta_code1_character == "u2")
               {
                test1_1(u2_x, u2_y);
              }
            if(pot_sta_code1_character == "f1" )
               {
                test1_1(f1_x, f1_y);
              }
            if(pot_sta_code1_character == "g1")
               {
                test1_1(g1_x, g1_y);
              }
            if(pot_sta_code1_character == "s2" )
               {
                test1_1(s2_x, s2_y);
              }
            if(pot_sta_code1_character == "g2" )
               {
                test1_1(g2_x, g2_y);
              }
            if(pot_sta_code1_character == "l1" )
               {
                test1_1(l1_x, l1_y);
              }
            if(pot_sta_code1_character == "l2" )
               {
                test1_1(l2_x, l2_y);
              }
            if(pot_sta_code1_character == "l3" )
               {
                test1_1(l3_x, l3_y);
              }
            if(pot_sta_code1_character == "l4" )
               {
                test1_1(l4_x, l4_y);
              }
            if(pot_sta_code1_character == "l5" )
               {
                test1_1(l5_x, l5_y);
              }
            if(pot_sta_code1_character == "l6" )
               {
                test1_1(l6_x, l6_y);
              }
            if(pot_sta_code1_character == "l7" )
               {
                test1_1(l7_x, l7_y);
              }
            if(pot_sta_code1_character == "l8"  )
               {
                test1_1(l8_x, l8_y);
              }
            if(pot_sta_code1_character == "l9" )
               {
                test1_1(l9_x, l9_y);
              }
            if(pot_sta_code1_character == "l10" )
               {
                test1_1(l10_x, l10_y);
              }
            if(pot_sta_code1_character == "l11" )
               {
                test1_1(l11_x, l11_y);
              }
            if(pot_sta_code1_character == "l12" )
               {
                test1_1(l12_x, l12_y);
              }
            if(pot_sta_code1_character == "i1" )
               {
                test1_1(i1_x, i1_y);
              }
            if(pot_sta_code1_character == "i2" )
               {
                test1_1(i2_x, i2_y);
              }
            if(pot_sta_code1_character == "i3" )
               {
                test1_1(i3_x, i3_y);
              }
            if(pot_sta_code1_character == "j1" )
               {
                test1_1(j1_x, j1_y);
              }
            if(pot_sta_code1_character == "j2" )
               {
                test1_1(j2_x, j2_y);
              }
            if(pot_sta_code1_character == "j3" )
               {
                test1_1(j3_x, j3_y);
              }
        }
        //1车-检测第二段任务，发送第三段任务
        if (code_send_sta == 1)//在上一步中转换的状态位，发送第二段任务之后这个状态位就会变化，符合该条件
        {

            if(pot_sta_code2_character == "s4")//小车第二段任务的终点字母代号
               {
                test1_2(s4_x, s4_y);
              }
            if(pot_sta_code2_character == "u2")
               {
                test1_2(u2_x, u2_y);
              }
            if(pot_sta_code2_character == "f1" )
               {
                test1_2(f1_x, f1_y);
              }
            if(pot_sta_code2_character == "g1")
               {
                test1_2(g1_x, g1_y);
              }
            if(pot_sta_code2_character == "s2" )
               {
                test1_2(s2_x, s2_y);
              }
            if(pot_sta_code2_character == "g2" )
               {
                test1_2(g2_x, g2_y);
              }
            if(pot_sta_code2_character == "l1" )
               {
                test1_2(l1_x, l1_y);
              }
            if(pot_sta_code2_character == "l2" )
               {
                test1_2(l2_x, l2_y);
              }
            if(pot_sta_code2_character == "l3" )
               {
                test1_2(l3_x, l3_y);
              }
            if(pot_sta_code2_character == "l4" )
               {
                test1_2(l4_x, l4_y);
              }
            if(pot_sta_code2_character == "l5" )
               {
                test1_2(l5_x, l5_y);
              }
            if(pot_sta_code2_character == "l6" )
               {
                test1_2(l6_x, l6_y);
              }
            if(pot_sta_code2_character == "l7" )
               {
                test1_2(l7_x, l7_y);
              }
            if(pot_sta_code2_character == "l8"  )
               {
                test1_2(l8_x, l8_y);
              }
            if(pot_sta_code2_character == "l9" )
               {
                test1_2(l9_x, l9_y);
              }
            if(pot_sta_code2_character == "l10" )
               {
                test1_2(l10_x, l10_y);
              }
            if(pot_sta_code2_character == "l11" )
               {
                test1_2(l11_x, l11_y);
              }
            if(pot_sta_code2_character == "l12" )
               {
                test1_2(l12_x, l12_y);
              }
            if(pot_sta_code2_character == "i1" )
               {
                test1_2(i1_x, i1_y);
              }
            if(pot_sta_code2_character == "i2" )
               {
                test1_2(i2_x, i2_y);
              }
            if(pot_sta_code2_character == "i3" )
               {
                test1_2(i3_x, i3_y);
              }
            if(pot_sta_code2_character == "j1" )
               {
                test1_2(j1_x, j1_y);
              }
            if(pot_sta_code2_character == "j2" )
               {
                test1_2(j2_x, j2_y);
              }
            if(pot_sta_code2_character == "j3" )
               {
                test1_2(j3_x, j3_y);
              }
        }

        //2车判断指令发送的代码 具体看一车介绍
        if (task_whole_B2 == 1)
        {

            if(pot_sta_code1_character_2 == "s4")
               {
                test2_1(s4_x, s4_y);
              }
            if(pot_sta_code1_character_2 == "u2")
               {
                test2_1(u2_x, u2_y);
              }
            if(pot_sta_code1_character_2 == "f1" )
               {
                test2_1(f1_x, f1_y);
              }
            if(pot_sta_code1_character_2 == "g1")
               {
                test2_1(g1_x, g1_y);
              }
            if(pot_sta_code1_character_2 == "s2" )
               {
                test2_1(s2_x, s2_y);
              }
            if(pot_sta_code1_character_2 == "g2" )
               {
                test2_1(g2_x, g2_y);
              }
            if(pot_sta_code1_character_2 == "l1" )
               {
                test2_1(l1_x, l1_y);
              }
            if(pot_sta_code1_character_2 == "l2" )
               {
                test2_1(l2_x, l2_y);
              }
            if(pot_sta_code1_character_2 == "l3" )
               {
                test2_1(l3_x, l3_y);
              }
            if(pot_sta_code1_character_2 == "l4" )
               {
                test2_1(l4_x, l4_y);
              }
            if(pot_sta_code1_character_2 == "l5" )
               {
                test2_1(l5_x, l5_y);
              }
            if(pot_sta_code1_character_2 == "l6" )
               {
                test2_1(l6_x, l6_y);
              }
            if(pot_sta_code1_character_2 == "l7" )
               {
                test2_1(l7_x, l7_y);
              }
            if(pot_sta_code1_character_2 == "l8"  )
               {
                test2_1(l8_x, l8_y);
              }
            if(pot_sta_code1_character_2 == "l9" )
               {
                test2_1(l9_x, l9_y);
              }
            if(pot_sta_code1_character_2 == "l10" )
               {
                test2_1(l10_x, l10_y);
              }
            if(pot_sta_code1_character_2 == "l11" )
               {
                test2_1(l11_x, l11_y);
              }
            if(pot_sta_code1_character_2 == "l12" )
               {
                test2_1(l12_x, l12_y);
              }
            if(pot_sta_code1_character_2 == "i1" )
               {
                test2_1(i1_x, i1_y);
              }
            if(pot_sta_code1_character_2 == "i2" )
               {
                test2_1(i2_x, i2_y);
              }
            if(pot_sta_code1_character_2 == "i3" )
               {
                test2_1(i3_x, i3_y);
              }
            if(pot_sta_code1_character_2 == "j1" )
               {
                test2_1(j1_x, j1_y);
              }
            if(pot_sta_code1_character_2 == "j2" )
               {
                test2_1(j2_x, j2_y);
              }
            if(pot_sta_code1_character_2 == "j3" )
               {
                test2_1(j3_x, j3_y);
              }
        }

        if (code_send_sta_2 == 1)
        {

            if(pot_sta_code2_character_2 == "s4")
               {
                test2_2(s4_x, s4_y);
              }
            if(pot_sta_code2_character_2 == "u2")
               {
                test2_2(u2_x, u2_y);
              }
            if(pot_sta_code2_character_2 == "f1" )
               {
                test2_2(f1_x, f1_y);
              }
            if(pot_sta_code2_character_2 == "g1")
               {
                test2_2(g1_x, g1_y);
              }
            if(pot_sta_code2_character_2 == "s2" )
               {
                test2_2(s2_x, s2_y);
              }
            if(pot_sta_code2_character_2 == "g2" )
               {
                test2_2(g2_x, g2_y);
              }
            if(pot_sta_code2_character_2 == "l1" )
               {
                test2_2(l1_x, l1_y);
              }
            if(pot_sta_code2_character_2 == "l2" )
               {
                test2_2(l2_x, l2_y);
              }
            if(pot_sta_code2_character_2 == "l3" )
               {
                test2_2(l3_x, l3_y);
              }
            if(pot_sta_code2_character_2 == "l4" )
               {
                test2_2(l4_x, l4_y);
              }
            if(pot_sta_code2_character_2 == "l5" )
               {
                test2_2(l5_x, l5_y);
              }
            if(pot_sta_code2_character_2 == "l6" )
               {
                test2_2(l6_x, l6_y);
              }
            if(pot_sta_code2_character_2 == "l7" )
               {
                test2_2(l7_x, l7_y);
              }
            if(pot_sta_code2_character_2 == "l8"  )
               {
                test2_2(l8_x, l8_y);
              }
            if(pot_sta_code2_character_2 == "l9" )
               {
                test2_2(l9_x, l9_y);
              }
            if(pot_sta_code2_character_2 == "l10" )
               {
                test2_2(l10_x, l10_y);
              }
            if(pot_sta_code2_character_2 == "l11" )
               {
                test2_2(l11_x, l11_y);
              }
            if(pot_sta_code2_character_2 == "l12" )
               {
                test2_2(l12_x, l12_y);
              }
            if(pot_sta_code2_character_2 == "i1" )
               {
                test2_2(i1_x, i1_y);
              }
            if(pot_sta_code2_character_2 == "i2" )
               {
                test2_2(i2_x, i2_y);
              }
            if(pot_sta_code2_character_2 == "i3" )
               {
                test2_2(i3_x, i3_y);
              }
            if(pot_sta_code2_character_2 == "j1" )
               {
                test2_2(j1_x, j1_y);
              }
            if(pot_sta_code2_character_2 == "j2" )
               {
                test2_2(j2_x, j2_y);
              }
            if(pot_sta_code1_character_2 == "j3" )
               {
                test2_2(j3_x, j3_y);
              }
        }

        //3车指令判断、具体看一车介绍
        if (task_whole_D1 == 1)
        {

            if(pot_sta_code1_character_3 == "u1")
               {
                test3_1(u1_x, u1_y);
              }

            if(pot_sta_code1_character_3 == "t1")
               {
                test3_1(t1_x, t1_y);
              }
            if(pot_sta_code1_character_3 == "a1" )
               {
                test3_1(a1_x, a1_y);
              }
            if(pot_sta_code1_character_3 == "b1")
               {
                test3_1(b1_x, b1_y);
              }
            if(pot_sta_code1_character_3 == "b2" )
               {
                test3_1(b2_x, b2_y);
              }
            if(pot_sta_code1_character_3 == "b3" )
               {
                test3_1(b3_x, b3_y);
              }
            if(pot_sta_code1_character_3 == "c1" )
               {
                test3_1(c1_x, c1_y);
              }
            if(pot_sta_code1_character_3 == "c2" )
               {
                test3_1(c2_x, c2_y);
              }
            if(pot_sta_code1_character_3 == "c3" )
               {
                test3_1(c3_x, c3_y);
              }
            if(pot_sta_code1_character_3 == "d1" )
               {
                test3_1(d1_x, d1_y);
              }
            if(pot_sta_code1_character_3 == "d2" )
               {
                test3_1(d2_x, d2_y);
              }
            if(pot_sta_code1_character_3 == "d3" )
               {
                test3_1(d3_x, d3_y);
              }
            if(pot_sta_code1_character_3 == "s1" )
               {
                test3_1(s1_x, s1_y);
              }
            if(pot_sta_code1_character_3 == "s3"  )
               {
                test3_1(s3_x, s3_y);
              }
            if(pot_sta_code1_character_3 == "e2" )
               {
                test3_1(e2_x, e2_y);
              }
            if(pot_sta_code1_character_3 == "e1" )
               {
                test3_1(e1_x, e1_y);
              }
            if(pot_sta_code1_character_3 == "f1" )
               {
                test3_1(f1_x, f1_y);
              }
            if(pot_sta_code1_character_3 == "h1" )
               {
                test3_1(h1_x, h1_y);
              }
            if(pot_sta_code1_character_3 == "t2" )
               {
                test3_1(t2_x, t2_y);
              }

        }

        if (code_send_sta_3 == 1)
        {

            if(pot_sta_code1_character_3 == "u1")
               {
                test3_2(u1_x, u1_y);
              }
            if(pot_sta_code2_character_3 == "t1")
               {
                test3_2(t1_x, t1_y);
              }
            if(pot_sta_code2_character_3 == "a1" )
               {
                test3_2(a1_x, a1_y);
              }
            if(pot_sta_code2_character_3 == "b1")
               {
                test3_2(b1_x, b1_y);
              }
            if(pot_sta_code2_character_3 == "b2" )
               {
                test3_2(b2_x, b2_y);
              }
            if(pot_sta_code2_character_3 == "b3" )
               {
                test3_2(b3_x, b3_y);
              }
            if(pot_sta_code2_character_3 == "c1" )
               {
                test3_2(c1_x, c1_y);
              }
            if(pot_sta_code2_character_3 == "c2" )
               {
                test3_2(c2_x, c2_y);
              }
            if(pot_sta_code2_character_3 == "c3" )
               {
                test3_2(c3_x, c3_y);
              }
            if(pot_sta_code2_character_3 == "d1" )
               {
                test3_2(d1_x, d1_y);
              }
            if(pot_sta_code2_character_3 == "d2" )
               {
                test3_2(d2_x, d2_y);
              }
            if(pot_sta_code2_character_3 == "d3" )
               {
                test3_2(d3_x, d3_y);
              }
            if(pot_sta_code2_character_3 == "s1" )
               {
                test3_2(s1_x, s1_y);
              }
            if(pot_sta_code2_character_3 == "s3"  )
               {
                test3_2(s3_x, s3_y);
              }
            if(pot_sta_code2_character_3 == "e2" )
               {
                test3_2(e2_x, e2_y);
              }
            if(pot_sta_code2_character_3 == "e1" )
               {
                test3_2(e1_x, e1_y);
              }
            if(pot_sta_code2_character_3 == "f1" )
               {
                test3_2(f1_x, f1_y);
              }
            if(pot_sta_code2_character_3 == "h1" )
               {
                test3_2(h1_x, h1_y);
              }
            if(pot_sta_code2_character_3 == "t2" )
               {
                test3_2(t2_x, t2_y);
              }

        }

        //4车指令判断 具体看1车介绍
        if (task_whole_D2 == 1)
        {

            if(pot_sta_code1_character_4 == "u1")
               {
                test4_1(u1_x, u1_y);
              }
            if(pot_sta_code1_character_4 == "t1")
               {
                test4_1(t1_x, t1_y);
              }
            if(pot_sta_code1_character_4 == "a1" )
               {
                test4_1(a1_x, a1_y);
              }
            if(pot_sta_code1_character_4 == "b1")
               {
                test4_1(b1_x, b1_y);
              }
            if(pot_sta_code1_character_4 == "b2" )
               {
                test4_1(b2_x, b2_y);
              }
            if(pot_sta_code1_character_4 == "b3" )
               {
                test4_1(b3_x, b3_y);
              }
            if(pot_sta_code1_character_4 == "c1" )
               {
                test4_1(c1_x, c1_y);
              }
            if(pot_sta_code1_character_4 == "c2" )
               {
                test4_1(c2_x, c2_y);
              }
            if(pot_sta_code1_character_4 == "c3" )
               {
                test4_1(c3_x, c3_y);
              }
            if(pot_sta_code1_character_4 == "d1" )
               {
                test4_1(d1_x, d1_y);
              }
            if(pot_sta_code1_character_4 == "d2" )
               {
                test4_1(d2_x, d2_y);
              }
            if(pot_sta_code1_character_4 == "d3" )
               {
                test4_1(d3_x, d3_y);
              }
            if(pot_sta_code1_character_4 == "s1" )
               {
                test4_1(s1_x, s1_y);
              }
            if(pot_sta_code1_character_4 == "s3"  )
               {
                test4_1(s3_x, s3_y);
              }
            if(pot_sta_code1_character_4 == "e2" )
               {
                test4_1(e2_x, e2_y);
              }
            if(pot_sta_code1_character_4 == "e1" )
               {
                test4_1(e1_x, e1_y);
              }
            if(pot_sta_code1_character_4 == "f1" )
               {
                test4_1(f1_x, f1_y);
              }
            if(pot_sta_code1_character_4 == "h1" )
               {
                test4_1(h1_x, h1_y);
              }
            if(pot_sta_code1_character_4 == "t2" )
               {
                test4_1(t2_x, t2_y);
              }

        }

        if (code_send_sta_4 == 1)
        {

            if(pot_sta_code2_character_4 == "u1")
               {
                test4_2(u1_x, u1_y);
              }
            if(pot_sta_code2_character_4 == "t1")
               {
                test4_2(t1_x, t1_y);
              }
            if(pot_sta_code2_character_4 == "a1" )
               {
                test4_2(a1_x, a1_y);
              }
            if(pot_sta_code2_character_4 == "b1")
               {
                test4_2(b1_x, b1_y);
              }
            if(pot_sta_code2_character_4 == "b2" )
               {
                test4_2(b2_x, b2_y);
              }
            if(pot_sta_code2_character_4 == "b3" )
               {
                test4_2(b3_x, b3_y);
              }
            if(pot_sta_code2_character_4 == "c1" )
               {
                test4_2(c1_x, c1_y);
              }
            if(pot_sta_code2_character_4 == "c2" )
               {
                test4_2(c2_x, c2_y);
              }
            if(pot_sta_code2_character_4 == "c3" )
               {
                test4_2(c3_x, c3_y);
              }
            if(pot_sta_code2_character_4 == "d1" )
               {
                test4_2(d1_x, d1_y);
              }
            if(pot_sta_code2_character_4 == "d2" )
               {
                test4_2(d2_x, d2_y);
              }
            if(pot_sta_code2_character_4 == "d3" )
               {
                test4_2(d3_x, d3_y);
              }
            if(pot_sta_code2_character_4 == "s1" )
               {
                test4_2(s1_x, s1_y);
              }
            if(pot_sta_code2_character_4 == "s3"  )
               {
                test4_2(s3_x, s3_y);
              }
            if(pot_sta_code2_character_4 == "e2" )
               {
                test4_2(e2_x, e2_y);
              }
            if(pot_sta_code2_character_4 == "e1" )
               {
                test4_2(e1_x, e1_y);
              }
            if(pot_sta_code2_character_4 == "f1" )
               {
                test4_2(f1_x, f1_y);
              }
            if(pot_sta_code2_character_4 == "h1" )
               {
                test4_2(h1_x, h1_y);
              }
            if(pot_sta_code2_character_4 == "t2" )
               {
                test4_2(t2_x, t2_y);
              }
        }

        //1车任务执行结束检测
        if((x1 - 714 < 30 && x1 - 714 > -30) && (yy1 - 400 < 30 && yy1 - 400 > -30) && end_pot_sta_g1 == 1)
          {
            end_pot_sta_g1 = 0;
            B1_task_percent = 0;
            qDebug()<<"1车到达终点";
//            time41 =(double)mstimer41.nsecsElapsed()/(double)1000000;
//            time42 =(double)mstimer42.nsecsElapsed()/(double)1000000;
          }

        if((x2 - 714 < 30 && x2 - 714 > -30) && (yy2 - 590 < 30 && yy2 - 590 > -30) && end_pot_sta_g2 == 1)
          {
             B2_task_percent = 0;
             end_pot_sta_g2  = 0;
             qDebug()<<"2车到达终点";
//             time31 =(double)mstimer31.nsecsElapsed()/(double)1000000;
//             time32 =(double)mstimer32.nsecsElapsed()/(double)1000000;
//             int whole_time3z = max(time41,time42)/60000;
//             int whole_time3y = (max(time41,time42)-whole_time3z*60000)/1000;
//             int whole_time4z = max(time31,time32)/60000;
//             int whole_time4y = (max(time31,time32)-whole_time4z*60000)/1000;
//             qDebug()<<"整个任务执行时间： "<<whole_time3z<<"min"<<whole_time3y<<"s";
//             qDebug()<<"整个任务执行时间： "<<whole_time4z<<"min"<<whole_time4y<<"s";
//             ui->outTaskf->setText(QString("%1min,%2s").arg(whole_time3z).arg(whole_time3y));//
//             ui->outTasks->setText(QString("%1min,%2s").arg(whole_time4z).arg(whole_time4y));//
          }

        if((x3 - 253 < 30 && x3 - 253 > -30) && (yy3 - 574 < 30 && yy3 - 574 > -30) && end_pot_sta_b2 == 1)
          {
            end_pot_sta_b2 = 0;
            D1_task_percent = 0;
            qDebug()<<"3车到达终点";
            time13 =(double)mstimer13.nsecsElapsed()/(double)1000000;
            time23 =(double)mstimer23.nsecsElapsed()/(double)1000000;

          }

        //四车终点信息检测，如果小车到达终点，则更换小车的状态位信息，以便下一次安排该小车执行任务
        if((x4 - 490 < 30 && x4 - 490 > -30) && (yy4 - 412 < 30 && yy4 - 412 > -30) && end_pot_sta_c1 == 1)
          {
            end_pot_sta_c1 = 0;
            D2_task_percent = 0;
            qDebug()<<"4车到达终点";
//            time14 =(double)mstimer14.nsecsElapsed()/(double)1000000;
//            time24 =(double)mstimer24.nsecsElapsed()/(double)1000000;
//            int whole_time1z = max(time13,time14)/60000;
//            int whole_time1y = (max(time13,time14)-whole_time1z*60000)/1000;
//            int whole_time2z = max(time23,time24)/60000;
//            int whole_time2y = (max(time23,time24)-whole_time2z*60000)/1000;
//            qDebug()<<"整个任务执行时间： "<<whole_time1z<<"min"<<whole_time1y<<"s";
//            qDebug()<<"整个任务执行时间： "<<whole_time2z<<"min"<<whole_time2y<<"s";
//            ui->inTaskf->setText(QString("%1min,%2s").arg(whole_time1z).arg(whole_time1y));//
//            ui->inTasks->setText(QString("%1min,%2s").arg(whole_time2z).arg(whole_time2y));//
          }

        /*线程2-05
         * tsx020105
         第五步-小车在完成第二段任务的过程中，会路过一个触发点，这个触发点会引发整个任务中第二个小车任务的分配，以及到达第一个小车第二段任务的终点，
         四辆小车到达指定地点之后，会触发一次任务下发，根据起始输入的终点信息，以及提取的小车上一个小车到达的接驳台发布下一个区域小车的指令，
         并重新执行01-02-03的功能后回到循环中检测小车的位置，下发指令
        */
        //1车指令转换判断
        if(((x1 - 622 < 30 && x1 - 622 > -30) && (yy1 - 400 <30 && yy1 - 400 > -30 ) ) && sc_wait_task_01 == 1)
        {
            if(code_sta_e3 == 0)//此为状态为信息，为了防止该循环一直执行，故在小车执行完第一段任务时才开启该状态位
            {
                    D_Task = 1;
                    D_Take_x = b1_deliver_x-1655;
                    D_Take_y = b1_deliver_y;
                    D_Deliver_x = b1_destination_x;
                    D_Deliver_y = b1_destination_y;
                code_sta_e3 = 1;
                sc_wait_task_01 = 0;

       double ssse = D_Dispatch_function(con_delay);
       qDebug()<<"出库任务中料箱式小车任务规划时间： "<<ssse;
       ui->outtask21->setText(QString("%1ms").arg(ssse));//

                int D1_size = 0;
                int D2_size = 0;
                //后面该部分的功能可以参考2200行处槽函数的介绍。功能以及流程类似
                if(Path_AMR_D1.size() > 8)
                {
                    qDebug()<<"3车代码："<<Path_AMR_D1.data();
                    QString AMR_D1_fcode = QString::fromStdString(Path_AMR_D1);
                    AMR_D1_code = AMR_D1_fcode.split("|",QString::SkipEmptyParts);
                    D1_size = AMR_D1_code.size();
                    D1_task_percent = 1;
                    qDebug()<<"安排3车执行任务";
                }
                else if(Path_AMR_D2.size() > 8)
                {
                    qDebug()<<"4车代码："<<Path_AMR_D2.data();
                    QString AMR_D2_fcode = QString::fromStdString(Path_AMR_D2);
                    AMR_D2_code = AMR_D2_fcode.split("|",QString::SkipEmptyParts);
                    D2_size = AMR_D2_code.size();
                    D2_task_percent = 1;
                    qDebug()<<"安排4车执行任务";
                }

                if(D2_size == 3)//检测到四车指令的长度
                {
                QStringList pot_sta_Rcode1 =  AMR_D2_code[0].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_Rcode2 =  AMR_D2_code[1].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_Rcode3 =  AMR_D2_code[2].split(",",QString::SkipEmptyParts);

                int pot_sta_Rcode1_size = pot_sta_Rcode1.size();
                int pot_sta_Rcode2_size = pot_sta_Rcode2.size();
                int pot_sta_Rcode3_size = pot_sta_Rcode3.size();

                pot_sta_code1_character_4 = pot_sta_Rcode1[pot_sta_Rcode1_size - 1];
                pot_sta_code2_character_4 = pot_sta_Rcode2[pot_sta_Rcode2_size - 1];

                task_whole_D2 = 1;

                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_4.txt");
                file.open(QIODevice::WriteOnly);
                file.write("4,2,");
                file.write(AMR_D2_code[0].toUtf8());
                file.close();
                }
                if(D1_size == 3)
                {

                QStringList pot_sta_pcode1 =  AMR_D1_code[0].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_pcode2 =  AMR_D1_code[1].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_pcode3 =  AMR_D1_code[2].split(",",QString::SkipEmptyParts);

                int pot_sta_pcode1_size = pot_sta_pcode1.size();
                int pot_sta_pcode2_size = pot_sta_pcode2.size();
                int pot_sta_pcode3_size = pot_sta_pcode3.size();

                pot_sta_code1_character_3 = pot_sta_pcode1[pot_sta_pcode1_size - 1];
                pot_sta_code2_character_3 = pot_sta_pcode2[pot_sta_pcode2_size - 1];

                task_whole_D1 = 1;

                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_3.txt");
                file.open(QIODevice::WriteOnly);
                file.write("3,2,");
                file.write(AMR_D1_code[0].toUtf8());
                file.close();
                }
            }

        }

        //2车指令转换判断
        if( (x2 - 622 < 30 && x2 - 622 > -30) && (yy2 - 590 <30 && yy2 - 590 > -30 ) && sc_wait_task_02 == 1 )
        {
            if(code_sta_e3_2 == 0)
            {
                D_Task = 1;
                D_Take_x = b2_deliver_x-1655;
                D_Take_y = b2_deliver_y;
                D_Deliver_x = b2_destination_x;
                D_Deliver_y = b2_destination_y;

                code_sta_e3_2 = 1;
                sc_wait_task_02 = 0;
               double ssse = D_Dispatch_function(con_delay);//先运行一遍李伟编写的调度函数程序，获取字符串命令
               qDebug()<<"出库任务中料箱式小车规划时间： "<<ssse;
               ui->outtask22->setText(QString("%1ms").arg(ssse));//显示小车坐标信息

                int D1_size = 0;
                int D2_size = 0;

                if(Path_AMR_D1.size() > 8)
                {
                    qDebug()<<"3车代码："<<Path_AMR_D1.data();
                    QString AMR_D1_fcode = QString::fromStdString(Path_AMR_D1);
                    AMR_D1_code = AMR_D1_fcode.split("|",QString::SkipEmptyParts);
                    D1_size = AMR_D1_code.size();
                    D1_task_percent = 1;
                    qDebug()<<"安排3车执行任务";

                }
                else if(Path_AMR_D2.size() > 8)
                {
                    qDebug()<<"4车代码："<<Path_AMR_D2.data();
                    QString AMR_D2_fcode = QString::fromStdString(Path_AMR_D2);
                    AMR_D2_code = AMR_D2_fcode.split("|",QString::SkipEmptyParts);
                    D2_size = AMR_D2_code.size();
                    D2_task_percent = 1;
                    qDebug()<<"安排4车执行任务";
                }
                if(D2_size == 3)
                {

                QStringList pot_sta_Rcode1 =  AMR_D2_code[0].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_Rcode2 =  AMR_D2_code[1].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_Rcode3 =  AMR_D2_code[2].split(",",QString::SkipEmptyParts);

                int pot_sta_Rcode1_size = pot_sta_Rcode1.size();
                int pot_sta_Rcode2_size = pot_sta_Rcode2.size();
                int pot_sta_Rcode3_size = pot_sta_Rcode3.size();

                pot_sta_code1_character_4 = pot_sta_Rcode1[pot_sta_Rcode1_size - 1];
                pot_sta_code2_character_4 = pot_sta_Rcode2[pot_sta_Rcode2_size - 1];

                task_whole_D2 = 1;

                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_4.txt");
                file.open(QIODevice::WriteOnly);
                file.write("4,2,");
                file.write(AMR_D2_code[0].toUtf8());
                file.close();
                }
                if(D1_size == 3)
                {

                QStringList pot_sta_pcode1 =  AMR_D1_code[0].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_pcode2 =  AMR_D1_code[1].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_pcode3 =  AMR_D1_code[2].split(",",QString::SkipEmptyParts);

                int pot_sta_pcode1_size = pot_sta_pcode1.size();
                int pot_sta_pcode2_size = pot_sta_pcode2.size();
                int pot_sta_pcode3_size = pot_sta_pcode3.size();

                pot_sta_code1_character_3 = pot_sta_pcode1[pot_sta_pcode1_size - 1];
                pot_sta_code2_character_3 = pot_sta_pcode2[pot_sta_pcode2_size - 1];

                task_whole_D1 = 1;

                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_3.txt");
                file.open(QIODevice::WriteOnly);
                file.write("3,2,");
                file.write(AMR_D1_code[0].toUtf8());
                file.close();
                }
            }
        }
        //4车调度
        if(((x4 -490 < 30 && x4 - 490 > -30) && (yy4 - 412 <30 && yy4 - 412 > -30 )) && sc_wait_task_04 == 1 )
        {
            if(code_sta_c1_2 == 1)
            {
                B_Task = 2;
                B_Take_x = d2_deliver_x+1655;
                B_Take_y = d2_deliver_y;
                B_Deliver_x = d2_destination_x;
                B_Deliver_y = d2_destination_y;

                code_sta_c1_2 = 0;
                sc_wait_task_04 = 0;

                double ssss = b_Dispatch_function(con_delay);
                qDebug()<<"入库任务配送式规划时间： "<<ssss;
                ui->intask21->setText(QString("%1ms").arg(ssss));//显示小车坐标信息

                int B1_size = 0;
                int B2_size = 0;

                if(Path_AMR_B1.size() > 8 )
                {
                    qDebug()<<"1车代码："<<Path_AMR_B1.data();
                    QString AMR_B1_fcode = QString::fromStdString(Path_AMR_B1);
                    AMR_B1_code = AMR_B1_fcode.split("|",QString::SkipEmptyParts);
                    B1_size = AMR_B1_code.size();
                    B1_task_percent = 1;
                    qDebug()<<"安排1车执行任务";

                }
                else if(Path_AMR_B2.size() > 8)
                {
                    qDebug()<<"2车代码："<<Path_AMR_B2.data();
                    QString AMR_B2_fcode = QString::fromStdString(Path_AMR_B2);
                    AMR_B2_code = AMR_B2_fcode.split("|",QString::SkipEmptyParts);
                    B2_size = AMR_B2_code.size();
                    B2_task_percent = 1;
                    qDebug()<<"安排2车执行任务";
                }

                if( B1_size == 3)
                {
                QStringList pot_sta_ecode1 =  AMR_B1_code[0].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_ecode2 =  AMR_B1_code[1].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_ecode3 =  AMR_B1_code[2].split(",",QString::SkipEmptyParts);

                int pot_sta_ecode1_size = pot_sta_ecode1.size();
                int pot_sta_ecode2_size = pot_sta_ecode2.size();
                //int pot_sta_ecode3_size = pot_sta_ecode3.size();

                pot_sta_code1_character = pot_sta_ecode1[pot_sta_ecode1_size - 1];
                pot_sta_code2_character = pot_sta_ecode2[pot_sta_ecode2_size - 1];

                task_whole_B1 = 1;

                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_1.txt");
                file.open(QIODevice::WriteOnly);
                file.write("1,2,");
                file.write(AMR_B1_code[0].toUtf8());
                file.close();
                }
                if(B2_size == 3)
                {

                QStringList pot_sta_scode1 =  AMR_B2_code[0].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_scode2 =  AMR_B2_code[1].split(",",QString::SkipEmptyParts);
                //QStringList pot_sta_scode3 =  AMR_B2_code[2].split(",",QString::SkipEmptyParts);

                int pot_sta_scode1_size = pot_sta_scode1.size();
                int pot_sta_scode2_size = pot_sta_scode2.size();

                pot_sta_code1_character_2 = pot_sta_scode1[pot_sta_scode1_size - 1];
                pot_sta_code2_character_2 = pot_sta_scode2[pot_sta_scode2_size - 1];

                task_whole_B2 = 1;

                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_2.txt");
                file.open(QIODevice::WriteOnly);
                file.write("2,2,");
                file.write(AMR_B2_code[0].toUtf8());
                file.close();
                }
            }

        }

        //3车调度
        if(((x3 - 490 < 30 && x3 - 490 > -30) && (yy3 - 590 <30 && yy3 - 590 > -30 )) && sc_wait_task_03 == 1)
        {
            if(code_sta_c1 == 1)
            {

                B_Task = 2;
                B_Take_x = d1_deliver_x+1655;
                B_Take_y = d1_deliver_y;
                B_Deliver_x = d1_destination_x;
                B_Deliver_y = d1_destination_y;

                code_sta_c1 = 0;
                sc_wait_task_03 = 0;
               int ssss = b_Dispatch_function(con_delay);
               qDebug()<<"入库任务配送式规划时间： "<<ssss;
               ui->intask22->setText(QString("%1").arg(ssss));//显示小车坐标信息

                int B1_size = 0;
                int B2_size = 0;

                if(Path_AMR_B1.size() > 8)
                {
                    qDebug()<<"1车代码："<<Path_AMR_B1.data();
                    QString AMR_B1_fcode = QString::fromStdString(Path_AMR_B1);
                    AMR_B1_code = AMR_B1_fcode.split("|",QString::SkipEmptyParts);
                    B1_size = AMR_B1_code.size();
                    B1_task_percent = 1;
                    qDebug()<<"安排1车执行任务";

                }
                else if(Path_AMR_B2.size() > 8)
                {
                    qDebug()<<"2车代码："<<Path_AMR_B2.data();
                    QString AMR_B2_fcode = QString::fromStdString(Path_AMR_B2);
                    AMR_B2_code = AMR_B2_fcode.split("|",QString::SkipEmptyParts);
                    B2_size = AMR_B2_code.size();
                    B2_task_percent = 1;
                    qDebug()<<"安排2车执行任务";
                }

                if( B1_size == 3)
                {
                QStringList pot_sta_ecode1 =  AMR_B1_code[0].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_ecode2 =  AMR_B1_code[1].split(",",QString::SkipEmptyParts);
                //QStringList pot_sta_ecode3 =  AMR_B1_code[2].split(",",QString::SkipEmptyParts);

                int pot_sta_ecode1_size = pot_sta_ecode1.size();
                int pot_sta_ecode2_size = pot_sta_ecode2.size();
                //int pot_sta_ecode3_size = pot_sta_ecode3.size();

                pot_sta_code1_character = pot_sta_ecode1[pot_sta_ecode1_size - 1];
                pot_sta_code2_character = pot_sta_ecode2[pot_sta_ecode2_size - 1];

                task_whole_B1 = 1;

                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_1.txt");
                file.open(QIODevice::WriteOnly);
                file.write("1,2,");
                file.write(AMR_B1_code[0].toUtf8());
                file.close();
                }
                if(B2_size == 3)
                {

                QStringList pot_sta_scode1 =  AMR_B2_code[0].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_scode2 =  AMR_B2_code[1].split(",",QString::SkipEmptyParts);
                //QStringList pot_sta_scode3 =  AMR_B2_code[2].split(",",QString::SkipEmptyParts);

                int pot_sta_scode1_size = pot_sta_scode1.size();
                int pot_sta_scode2_size = pot_sta_scode2.size();
                //int pot_sta_scode3_size = pot_sta_scode3.size();

                pot_sta_code1_character_2 = pot_sta_scode1[pot_sta_scode1_size - 1];
                pot_sta_code2_character_2 = pot_sta_scode2[pot_sta_scode2_size - 1];

                task_whole_B2 = 1;

                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_2.txt");
                file.open(QIODevice::WriteOnly);
                file.write("2,2,");
                file.write(AMR_B2_code[0].toUtf8());
                file.close();
                }
            }
        }

    });

    this->setWindowTitle("多AMR调度控制系统");



//    //嵌入unity
//    util = new ShowUnityWindowsInQt(this);
//    unity_task = new QThread;
//    util->moveToThread(unity_task);
//    QString titleName("My project");
//    connect(util, &ShowUnityWindowsInQt::unityProgramStarted, this, [&]()
//    {
//        util->setWindowParent((HWND)ui->unity->winId(), titleName);
//    });
//    // start your unity program
//    QString unityExePath(R"(G:\QT\projects\DHBLAB(4files)\DHBLAB\My project.exe)");
//    util->startUnityProgram(unityExePath);



    //侧边导航栏设置
    ui->netManage->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->offerManage->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->waishePanel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->stateMonitor->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->dataCollect->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->AMRManage->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->diaoduManage->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->elecMap->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->workData->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->userManage->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    //选项文字居中
    ui->newOfferEnd->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->newOfferKind->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->newOfferStart->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->newstartHigh->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->newendHigh->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox_206->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox_207->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox_208->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox_209->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox_210->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox_211->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox_212->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->newPriority->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->lineEdit_221->setAlignment(Qt::AlignCenter);


    ui->subOrder_6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自动适配表格大小
    ui->subOrder_6->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->subOrder_6->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(0,67,98);}");
    ui->subOrder_6->horizontalHeader()->setMinimumHeight(40);            //设置表头行高


    //tabWidget相关设置
    ui->tabWidget->removeTab(2);        //隐藏任务编辑栏
    ui->TabAMRManage->removeTab(2);

    ui->tableTest->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableTest->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableTest->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Custom);    //自定义第一列宽度
    ui->tableTest->setColumnWidth(0,300);                               //设置第一列宽度
    ui->tableTest->horizontalHeader()->setMinimumHeight(50);            //设置表头行高
    ui->tableTest->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");       //设置表头字体格式
    ui->tableTest->setAlternatingRowColors(true);
    ui->tableTest->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableTest->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->offerConfirmTable->horizontalHeader()->setVisible(true);
    ui->offerConfirmTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->offerConfirmTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //行高自动适配表格大小
    ui->offerConfirmTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->offerConfirmTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Custom);    //自定义第一列宽度
    ui->offerConfirmTable->horizontalHeader()->setMinimumHeight(50);            //设置表头行高


    ui->tableTest_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableTest_2->horizontalHeader()->setMinimumHeight(40);            //设置表头行高
    ui->tableTest_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(0,67,98);}");       //设置表头字体格式

    //为状态监控界面的AMR状态表添加电量条
    ui->subOrder_6->setCellWidget(0, 2, ui->powerLeft_1);
    ui->subOrder_6->setCellWidget(1, 2, ui->powerLeft_2);
    ui->subOrder_6->setCellWidget(2, 2, ui->powerLeft_3);
    ui->subOrder_6->setCellWidget(3, 2, ui->powerLeft_4);

    ui->debug_show->setCurrentIndex(1);

    ui->paintMap->GainChange(1);
    ui->paintMap2->GainChange(0.9);
    ui->managePaint->GainChange(0.9);

}


MainWindow::~MainWindow()
{
    delete ui;
    send_task->quit();
    send_task->wait();
    send->deleteLater();
    send_task->deleteLater();
}

void MainWindow::cfunction_string(int task_info,int QgsPointX,int QgsPointY,int QgePointX,int QgePointY)
{
    Task = task_info;
    Take_x = QgsPointX;
    Take_y = QgsPointY;
    Deliver_x = QgePointX;
    Deliver_y = QgePointY;

    int aaa = Task;

    //2-根据输入坐标信息分配任务
    if (Task == 1 && (Conection_1_State == 0 || Conection_2_State == 0))
        {
            B_Task = 1;
            B_Take_x = Take_x;
            B_Take_y = Take_y;

            if (Conection_1_State == 0 && Conection_2_State == 0)
            {
                B_Deliver_x = 7785;
                B_Deliver_y = 3807;
            }
            if (Conection_1_State == 1 && Conection_2_State == 0)
            {
                B_Deliver_x = 7785;
                B_Deliver_y = 1653;
            }
            if (Conection_1_State == 0 && Conection_2_State == 1)
            {
                B_Deliver_x = 7785;
                B_Deliver_y = 3807;
            }

            if (B_Deliver_y == 3807)
            {
                Conection_1_State = 1;
            }
            if (B_Deliver_y == 1653)
            {
                Conection_2_State = 1;
            }
            Task = 0;
        }

    if (Task == 2 && (Conection_1_State == 0 || Conection_2_State == 0))
        {
            D_Task = 2;
            D_Take_x = Take_x;
            D_Take_y = Take_y;

            if (Conection_1_State == 0 && Conection_2_State == 0)
            {
                D_Deliver_x = 6130;
                D_Deliver_y = 3807;
            }
            if (Conection_1_State == 1 && Conection_2_State == 0)
            {
                D_Deliver_x = 6130;
                D_Deliver_y = 1653;
            }
            if (Conection_1_State == 0 && Conection_2_State == 1)
            {
                D_Deliver_x = 6130;
                D_Deliver_y = 3807;
            }

            if (D_Deliver_y == 3807)
            {
                Conection_1_State = 1;
            }
            if (D_Deliver_y == 1653)
            {
                Conection_2_State = 1;
            }

            Task = 0;
        }

    if (Task == 3)
        {
            B_Task = 3;
            B_Take_x=Take_x;
            B_Take_y=Take_y;
            B_Deliver_x=Deliver_x;
            B_Deliver_y=Deliver_y;
        }


    //3-将任务分配好后的字符串进行处理，分成三段，提供给下一步进行识别发送
    if(aaa == 1)//如果选择的为出库任务--（先执行1 2车的程序，也就是料箱式小车的任务）
    {
        //3-将任务分配好后的字符串进行处理，分成三段，提供给下一步进行识别发送

       double ssss = b_Dispatch_function(con_delay);//先运行一遍李伟编写的调度函数程序，获取字符串命令
       qDebug()<<"第一次规划时间： "<<ssss<<"ms";


        //获取命令行的三段代码
        int AMR_B1_size = 0;//初始化定义获取到的代码长度
        int AMR_B2_size = 0;
        if(Path_AMR_B1.size()!=0)//如果检测到调度文件中有命令，则
        {
        //下列代码为将字符串分为三串的操作，存储在AMR_B1_code，后续有类似代码功能雷同，存储数组不同
        QString AMR_B1_ncode = QString::fromStdString(Path_AMR_B1);
        AMR_B1_code = AMR_B1_ncode.split("|",QString::SkipEmptyParts);
        AMR_B1_size = AMR_B1_code.size();
        qDebug()<<"B1车";
        }
        else if(Path_AMR_B2.size()!=0)
        {
        QString AMR_B2_ncode = QString::fromStdString(Path_AMR_B2);
        AMR_B2_code = AMR_B2_ncode.split("|",QString::SkipEmptyParts);
        AMR_B2_size = AMR_B2_code.size();
        qDebug()<<"B2车";
        }

       // 4-发送第一串代码，提取每一段代码的最后一个字符用于下一步终点判断，
        if(AMR_B1_size == 3)
            {
            ui->outtask11->setText(QString("%1ms").arg(ssss));

                //不是长久之计
                b1_deliver_x = B_Deliver_x;
                b1_deliver_y = B_Deliver_y;
                b1_destination_x = Deliver_x;
                b1_destination_y = Deliver_y;

                sc_wait_task_01 = 1;//相邻两个小任务之间触发的判断状态位
                B1_task_percent = 1;//这个为小车忙碌或空闲状态的全局变量，用于判断是否可以安排下车执行任务，执行到这一步表明该小车接到任务，为忙碌状态

                //下列代码功能为提取三段任务中，每段任务的终点，用于判断需不需要发送下一串指令，后续有类似功能
                QStringList pot_sta_code1 =  AMR_B1_code[0].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_code2 =  AMR_B1_code[1].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_code3 =  AMR_B1_code[2].split(",",QString::SkipEmptyParts);

                int pot_sta_code1_size = pot_sta_code1.size();
                int pot_sta_code2_size = pot_sta_code2.size();
                int pot_sta_code3_size = pot_sta_code3.size();

                pot_sta_code1_character = pot_sta_code1[pot_sta_code1_size - 1];
                pot_sta_code2_character = pot_sta_code2[pot_sta_code2_size - 1];

                //5-开启任务
                task_whole_B1 = 1;

                //发送第一串代码 并开始计时
                mstimer13.start();
                mstimer14.start();
                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_1.txt");
                file.open(QIODevice::WriteOnly);
                file.write("1,2,");
                file.write(AMR_B1_code[0].toUtf8());
                file.close();
            //显示指令成功发送的提示
            qDebug()<<"1车指令： "<<AMR_B1_code[0]<<"  "<<AMR_B1_code[1]<<"   "<<AMR_B1_code[2];
            QMessageBox::information(this,"指令","指令下发成功");
            }
        else if(AMR_B2_size == 3)
            {
              ui->outtask12->setText(QString("%1ms").arg(ssss));
                b2_deliver_x = B_Deliver_x;
                b2_deliver_y = B_Deliver_y;
                b2_destination_x = Deliver_x;
                b2_destination_y = Deliver_y;

                sc_wait_task_02 = 1;//相邻两个小任务之间触发的判断状态位
                B2_task_percent= 1;
                QStringList pot_sta_code1_2 =  AMR_B2_code[0].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_code2_2 =  AMR_B2_code[1].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_code3_2 =  AMR_B2_code[2].split(",",QString::SkipEmptyParts);

                int pot_sta_code1_size_2 = pot_sta_code1_2.size();
                int pot_sta_code2_size_2 = pot_sta_code2_2.size();
                int pot_sta_code3_size_2 = pot_sta_code3_2.size();

                pot_sta_code1_character_2 = pot_sta_code1_2[pot_sta_code1_size_2 - 1];
                pot_sta_code2_character_2 = pot_sta_code2_2[pot_sta_code2_size_2 - 1];

                task_whole_B2 = 1;

                mstimer23.start();
                mstimer24.start();
                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_2.txt");
                file.open(QIODevice::WriteOnly);
                file.write("2,2,");
                file.write(AMR_B2_code[0].toUtf8());
                file.close();

            qDebug()<<"2车指令： "<<AMR_B2_code[0]<<"  "<<AMR_B2_code[1]<<"   "<<AMR_B2_code[2];
            QMessageBox::information(this,"指令","指令下发成功");

            }

        //指令异常判断
        else if(AMR_B1_size == 0 && AMR_B2_size == 0)
            {
            QMessageBox::information(this,"指令","指令下发失败");
            }

    }

    //3-将任务分配好后的字符串进行处理，分成三段，提供给下一步进行识别发送（因为任务类别不同，所需执行函数有差异，采用并列形式）
    else if(aaa == 2)//执行入库任务
    {

       double ssse = D_Dispatch_function(con_delay);//先运行一遍李伟编写的调度函数程序，获取字符串命令
       qDebug()<<"入库任务规划时间： "<<ssse<<"ms";//先运行一遍李伟编写的调度函数程序，获取字符串命令

        //获取命令行的三段代码
        int AMR_D1_size = 0;
        int AMR_D2_size = 0;
        if(Path_AMR_D1.size()!=0)
        {
            QString AMR_D1_ncode = QString::fromStdString(Path_AMR_D1);
            AMR_D1_code = AMR_D1_ncode.split("|",QString::SkipEmptyParts);
            AMR_D1_size = AMR_D1_code.size();

            qDebug()<<"D1车";

        }
        else if(Path_AMR_D2.size()!=0)
        {
            QString AMR_D2_ncode = QString::fromStdString(Path_AMR_D2);
            AMR_D2_code = AMR_D2_ncode.split("|",QString::SkipEmptyParts);
            AMR_D2_size = AMR_D2_code.size();
            qDebug()<<"D2车";

        }

         // 4-发送第一串代码，提取每一段代码的最后一个字符用于下一步终点判断，
        if(AMR_D2_size == 3)
        {
            ui->intask21->setText(QString("%1ms").arg(ssse));//显示小车坐标信息

            d2_deliver_x = D_Deliver_x;
            d2_deliver_y = D_Deliver_y;
            d2_destination_x = Deliver_x;
            d2_destination_y = Deliver_y;

                sc_wait_task_04 = 1;//相邻两个小任务之间触发的判断状态位
                D2_task_percent = 1;
                QStringList pot_sta_code1_4 =  AMR_D2_code[0].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_code2_4 =  AMR_D2_code[1].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_code3_4 =  AMR_D2_code[2].split(",",QString::SkipEmptyParts);

                int pot_sta_code1_size_4 = pot_sta_code1_4.size();
                int pot_sta_code2_size_4 = pot_sta_code2_4.size();
                //int pot_sta_code3_size = pot_sta_code3_2.size();

                pot_sta_code1_character_4 = pot_sta_code1_4[pot_sta_code1_size_4 - 1];
                pot_sta_code2_character_4 = pot_sta_code2_4[pot_sta_code2_size_4 - 1];

                task_whole_D2 = 1;//开启任务
                mstimer41.start();
                mstimer42.start();
                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_4.txt");
                file.open(QIODevice::WriteOnly);
                file.write("4,2,");
                file.write(AMR_D2_code[0].toUtf8());
                file.close();

            qDebug()<<"4车指令： "<<AMR_D2_code[0]<<"  "<<AMR_D2_code[1]<<"   "<<AMR_D2_code[2];
            QMessageBox::information(this,"指令","指令下发成功");
         }

        // 4-发送第一串代码，提取每一段代码的最后一个字符用于下一步终点判断，
        else if(AMR_D1_size == 3)
        {
            ui->intask22->setText(QString("%1ms").arg(ssse));//显示小车坐标信息

            d1_deliver_x = D_Deliver_x;
            d1_deliver_y = D_Deliver_y;
            d1_destination_x = Deliver_x;
            d1_destination_y = Deliver_y;

                sc_wait_task_03 = 1;//相邻两个小任务之间触发的判断状态位
                D1_task_percent = 1;
                QStringList pot_sta_code1_3 =  AMR_D1_code[0].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_code2_3 =  AMR_D1_code[1].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_code3_3 =  AMR_D1_code[2].split(",",QString::SkipEmptyParts);

                int pot_sta_code1_size_3 = pot_sta_code1_3.size();
                int pot_sta_code2_size_3 = pot_sta_code2_3.size();
                //int pot_sta_code3_size = pot_sta_code3_2.size();

                pot_sta_code1_character_3 = pot_sta_code1_3[pot_sta_code1_size_3 - 1];
                pot_sta_code2_character_3 = pot_sta_code2_3[pot_sta_code2_size_3 - 1];

                task_whole_D1 = 1;//
                mstimer31.start();
                mstimer32.start();
                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_3.txt");
                file.open(QIODevice::WriteOnly);
                file.write("3,2,");
                file.write(AMR_D1_code[0].toUtf8());
                file.close();

            qDebug()<<"3车指令： "<<AMR_D1_code[0]<<"  "<<AMR_D1_code[1]<<"   "<<AMR_D1_code[2];
            QMessageBox::information(this,"指令","指令下发成功");
         }
        else if(AMR_D1_size == 0 && AMR_D2_size == 0)
            {
            QMessageBox::information(this,"指令","指令下发失败");
        }
    }

    else if(aaa == 3)//如果选择的为移库任务
    {

        //3-将任务分配好后的字符串进行处理，分成三段，提供给下一步进行识别发送

       double ssss = b_Dispatch_function(con_delay);//先运行一遍李伟编写的调度函数程序，获取字符串命令
       qDebug()<<"移库规划时间： "<<ssss<<"ms";

        //获取命令行的三段代码
        int AMR_B1_size = 0;//初始化定义获取到的代码长度
        int AMR_B2_size = 0;
        if(Path_AMR_B1.size()!=0)//如果检测到调度文件中有命令，则
        {
        //下列代码为将字符串分为三串的操作，存储在AMR_B1_code，后续有类似代码功能雷同，存储数组不同
        QString AMR_B1_ncode = QString::fromStdString(Path_AMR_B1);
        AMR_B1_code = AMR_B1_ncode.split("|",QString::SkipEmptyParts);
        AMR_B1_size = AMR_B1_code.size();
        qDebug()<<"B1车";
        }
        else if(Path_AMR_B2.size()!=0)
        {
        QString AMR_B2_ncode = QString::fromStdString(Path_AMR_B2);
        AMR_B2_code = AMR_B2_ncode.split("|",QString::SkipEmptyParts);
        AMR_B2_size = AMR_B2_code.size();
        qDebug()<<"B2车";
        }

       // 4-发送第一串代码，提取每一段代码的最后一个字符用于下一步终点判断，
        if(AMR_B1_size == 3)
            {

                B1_task_percent = 1;//这个为小车忙碌或空闲状态的全局变量，用于判断是否可以安排下车执行任务，执行到这一步表明该小车接到任务，为忙碌状态
                //下列代码功能为提取三段任务中，每段任务的终点，用于判断需不需要发送下一串指令，后续有类似功能
                QStringList pot_sta_code1 =  AMR_B1_code[0].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_code2 =  AMR_B1_code[1].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_code3 =  AMR_B1_code[2].split(",",QString::SkipEmptyParts);

                int pot_sta_code1_size = pot_sta_code1.size();
                int pot_sta_code2_size = pot_sta_code2.size();
                int pot_sta_code3_size = pot_sta_code3.size();

                pot_sta_code1_character = pot_sta_code1[pot_sta_code1_size - 1];
                pot_sta_code2_character = pot_sta_code2[pot_sta_code2_size - 1];

                //5-开启任务
                task_whole_B1 = 1;

                //发送第一串代码 并开始计时


                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_1.txt");
                file.open(QIODevice::WriteOnly);
                file.write("1,2,");
                file.write(AMR_B1_code[0].toUtf8());
                file.close();
            //显示指令成功发送的提示
            qDebug()<<"1车指令： "<<AMR_B1_code[0]<<"  "<<AMR_B1_code[1]<<"   "<<AMR_B1_code[2];
            QMessageBox::information(this,"指令","指令下发成功");
            }
        else if(AMR_B2_size == 3)
            {

                B2_task_percent= 1;
                QStringList pot_sta_code1_2 =  AMR_B2_code[0].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_code2_2 =  AMR_B2_code[1].split(",",QString::SkipEmptyParts);
                QStringList pot_sta_code3_2 =  AMR_B2_code[2].split(",",QString::SkipEmptyParts);

                int pot_sta_code1_size_2 = pot_sta_code1_2.size();
                int pot_sta_code2_size_2 = pot_sta_code2_2.size();
                int pot_sta_code3_size_2 = pot_sta_code3_2.size();

                pot_sta_code1_character_2 = pot_sta_code1_2[pot_sta_code1_size_2 - 1];
                pot_sta_code2_character_2 = pot_sta_code2_2[pot_sta_code2_size_2 - 1];

                task_whole_B2 = 1;


                QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_2.txt");
                file.open(QIODevice::WriteOnly);
                file.write("2,2,");
                file.write(AMR_B2_code[0].toUtf8());
                file.close();

            qDebug()<<"2车指令： "<<AMR_B2_code[0]<<"  "<<AMR_B2_code[1]<<"   "<<AMR_B2_code[2];
            QMessageBox::information(this,"指令","指令下发成功");

            }

        //指令异常判断
        else if(AMR_B1_size == 0 && AMR_B2_size == 0)
            {
            QMessageBox::information(this,"指令","指令下发失败");
            }

    }


}


//下列四个槽函数为小车地图上四个小车位置更新的进程连接按钮的功能实现，点击链接，槽函数会触发相应的进程开启。
void MainWindow::on_startButton_clicked()
{
    thread.start();
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}
void MainWindow::on_stopButton_clicked()
{
    if(thread.isRunning())
    {
        thread.stop();

        ui->startButton->setEnabled(true);
        ui->stopButton->setEnabled(false);

    }
}
void MainWindow::on_startButton_2_clicked()
{
    thread2.start();
    //thread2.start();
    ui->startButton_2->setEnabled(false);
    ui->stopButton_2->setEnabled(true);
}


void MainWindow::on_stopButton_2_clicked()
{
    if(thread2.isRunning())
    {
        thread2.stop();

        ui->startButton_2->setEnabled(true);
        ui->stopButton_2->setEnabled(false);

    }
}

void MainWindow::on_startButton_3_clicked()
{
    thread3.start();
    //thread2.start();
    ui->startButton_3->setEnabled(false);
    ui->stopButton_3->setEnabled(true);
}


void MainWindow::on_stopButton_3_clicked()
{
    if(thread3.isRunning())
    {
        thread3.stop();

        ui->startButton_3->setEnabled(true);
        ui->stopButton_3->setEnabled(false);

    }
}
void MainWindow::on_startButton_4_clicked()
{
    thread4.start();
    ui->startButton_4->setEnabled(false);
    ui->stopButton_4->setEnabled(true);
}


void MainWindow::on_stopButton_4_clicked()
{
    if(thread4.isRunning())
    {
        thread4.stop();
        ui->startButton_4->setEnabled(true);
        ui->stopButton_4->setEnabled(false);

    }
}//小车进程按钮功能结束

//为了调试便利写的手动下发指令的窗口
void MainWindow::on_f_code_Button_clicked()//测试窗口，手动下发命令
{
    quint16 sendCommand = 3066;     //编号3066为指定路径导航api
    QString sendDataStr = ui->f_code_code->toPlainText();
    QByteArray sendData = sendDataStr.toLatin1();
    qDebug()<<"ip: "<< sendData;
    quint16 number = ui->f_code_num->currentIndex();
    emit writeTcpData(sendCommand,sendData, number);

//    QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_.txt");

//    file.open(QIODevice::WriteOnly);
//    QString msg = ui->f_code_code->toPlainText();
//    QString str_num = ui->f_code_num->currentText();
//    QString code_type = ui->f_code_type->currentText();


//    file.write(str_num.toUtf8());
//    file.write(",");
//    file.write(code_type.toUtf8());
//    file.write(",");
//    file.write(msg.toUtf8());
//    file.close();
}

/*-线程2 01-02-03步在此
 *tsx020101-tsx020103
 * 这个槽函数为线程2中第一步的功能，具体功能分块介绍如下：
 1-获取输入值，并进行数值转换
 2-根据输入坐标信息分配任务
 3-将任务分配好后的字符串进行处理，分成三段，提供给下一步进行识别发送
 4-发送第一串代码，提取没有段代码的最后一个字符用于下一步终点判断，
 5-开启任务
*/

void MainWindow::on_s_task1_Button_clicked()
{
    //1-获取输入值，并进行数值转换
    int B_task1_type = ui->s_task1_type->currentIndex();//任务类型 0无  1出库  2入库
    QString s_start1_x = ui->s_task1_start_x->text();//起点
    QString s_start1_y = ui->s_task1_start_y->text();
    QString s_end1_x = ui->s_task1_end_x->text();//终点
    QString s_end1_y = ui->s_task1_end_y->text();

    Task = B_task1_type;//数值类型转换
    Take_x = s_start1_x.toInt();
    Take_y = s_start1_y.toInt();
    Deliver_x = s_end1_x.toInt();
    Deliver_y = s_end1_y.toInt();

   cfunction_string(B_task1_type,s_start1_x.toInt(),s_start1_y.toInt(),s_end1_x.toInt(),s_end1_y.toInt());
}


/*void MainWindow::on_s_task2_Button_clicked()
{

    int D_task2_type = ui->s_task2_type->currentIndex();
    QString s_start2_x = ui->s_task2_start_x->text();
    QString s_start2_y = ui->s_task2_start_y->text();
    QString s_end2_x = ui->s_task2_end_x->text();
    QString s_end2_y = ui->s_task2_end_y->text();

    qDebug()<<"初始输入值："<<D_task2_type<<s_start2_x<<s_start2_y<<s_end2_x<<s_end2_y;
    D_Task = D_task2_type;
    D_Take_x = s_start2_x.toInt();
    D_Take_y = s_start2_y.toInt();
    D_Deliver_x = s_end2_x.toInt();
    D_Deliver_y = s_end2_y.toInt();
    qDebug()<<"函数输入值："<<D_Task<<D_Take_x<<D_Take_y<<D_Deliver_x<<D_Deliver_y;

    int sece = 1;
       double ssse = D_Dispatch_function(sece);//先运行一遍李伟编写的调度函数程序，获取字符串命令
       qDebug()<<"延迟时间： "<<ssse;

    QString AMR_D1_ncode = QString::fromStdString(Path_AMR_D1);
    QString AMR_D2_ncode = QString::fromStdString(Path_AMR_D2);


     AMR_D1_code = AMR_D1_ncode.split("|",QString::SkipEmptyParts);
     AMR_D2_code = AMR_D2_ncode.split("|",QString::SkipEmptyParts);

    int AMR_D1_size = AMR_D1_code.size();
    int AMR_D2_size = AMR_D2_code.size();

    //qDebug()<<"测试输出： "<<Path_AMR_D1.data();

    if(AMR_D1_size == 3)
    {
        /*QStringList pot_sta_code1_3 =  AMR_D1_code[0].split(",",QString::SkipEmptyParts);
        QStringList pot_sta_code2_3 =  AMR_D1_code[1].split(",",QString::SkipEmptyParts);
        QStringList pot_sta_code3_3 =  AMR_D1_code[2].split(",",QString::SkipEmptyParts);

        int pot_sta_code1_size_3 = pot_sta_code1_3.size();
        int pot_sta_code2_size_3 = pot_sta_code2_3.size();
        //int pot_sta_code3_size = pot_sta_code3_2.size();

        pot_sta_code1_character_3 = pot_sta_code1_3[pot_sta_code1_size_3 - 1];
        pot_sta_code2_character_3 = pot_sta_code2_3[pot_sta_code2_size_3 - 1];

        task_whole_D1 = 1;
        QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_.txt");
        file.open(QIODevice::WriteOnly);
        file.write("3,2,");
        file.write(AMR_D1_code[0].toUtf8());
        file.close();

    qDebug()<<"3车指令： "<<AMR_D1_code[0]<<"  "<<AMR_D1_code[1]<<"   "<<AMR_D1_code[2];
    QMessageBox::information(this,"指令","指令下发成功");
    }
    if(AMR_D2_size == 3)
    {
        QStringList pot_sta_code1_4 =  AMR_D2_code[0].split(",",QString::SkipEmptyParts);
        QStringList pot_sta_code2_4 =  AMR_D2_code[1].split(",",QString::SkipEmptyParts);
        //QStringList pot_sta_code3_4 =  AMR_D2_code[2].split(",",QString::SkipEmptyParts);

        int pot_sta_code1_size_4 = pot_sta_code1_4.size();
        int pot_sta_code2_size_4 = pot_sta_code2_4.size();
        //int pot_sta_code3_size = pot_sta_code3_2.size();

        pot_sta_code1_character_4 = pot_sta_code1_4[pot_sta_code1_size_4 - 1];
        pot_sta_code2_character_4 = pot_sta_code2_4[pot_sta_code2_size_4 - 1];

        task_whole_D2 = 1;


        QFile file("D:\\t\\dhblab_meta_socket\\storage\\devices\\unicast_.txt");
        file.open(QIODevice::WriteOnly);
        file.write("4,2,");
        file.write(AMR_D2_code[0].toUtf8());
        file.close();
    qDebug()<<"测试："<<pot_sta_code1_character_4<<"  "<<pot_sta_code2_character_4;
    qDebug()<<"测试2："<<pot_sta_code1_4<<"  "<<pot_sta_code2_4;

    qDebug()<<"4车指令： "<<AMR_D2_code[0]<<"  "<<AMR_D2_code[1]<<"   "<<AMR_D2_code[2];
    QMessageBox::information(this,"指令","指令下发成功");
    }
    if(AMR_D1_size != 3 && AMR_D2_size != 3)
    {
       QMessageBox::information(this,"指令","指令下发失败，请检查输入坐标是否正确");
    }
}
*/

void MainWindow::on_netManage_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_offerManage_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_diaoduManage_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_stateMonitor_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_AMRManage_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_waishePanel_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_elecMap_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_dataCollect_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_workData_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_userManage_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

//void MainWindow::slotTime()
//{

//    QSqlQuery query;
//    QString sql = "select * from task3";
//    query.exec(sql);

//    /*int k = 0;
//    query.last();
//    k = query.at();
//    qDebug()<<"k = "<<k;
//    if(k == j)
//    {
//        qDebug()<<"无新增数据";
//    }
//    else if(j<k)
//    {
//        qDebug()<<"有新增数据，正在刷新";
//    j = j + 1;
//    }
//    query.seek(j-5);*/

//    //qDebug()<<" j = "<<j;
//    for (int i = 0; i < 5; i++)
//    {
//        query.next();
//        etask_ip[i] = query.value(1).toInt();
//        etask_type[i] = query.value(2).toInt();
//        etask_list[i] = query.value(3).toInt();
//        etask_sta[i] = query.value(4).toInt();
//        etask_percent[i] = query.value(5).toInt();
//        etask_source[i] = query.value(6).toInt();
//        etask_time[i] = query.value(7).toInt();
//    }
//    //etask_ip[0] = etask_ip[0] +10;
//    for (int h = 0; h < 5; h++)
//    {
//        switch (etask_type[h])
//        {
//        case 0:
//            ui->tableWidget_2->setItem(h, 1, new QTableWidgetItem(QString("出库")));
//            break;
//        case 1:ui->tableWidget_2->setItem(h, 1, new QTableWidgetItem(QString("入库")));
//            break;
//        case 2:ui->tableWidget_2->setItem(h, 1, new QTableWidgetItem(QString("移库")));
//            break;
//        default:
//            break;
//        }


//        ui->tableWidget_2->setItem(h, 0, new QTableWidgetItem(QString("2022-1120-0201-03-010%1").arg(etask_ip[0])));

//        switch (etask_list[h])
//        {
//        case(0):ui->tableWidget_2->setItem(h, 2, new QTableWidgetItem(QString("顺序")));
//            break;
//        case(1):ui->tableWidget_2->setItem(h, 2, new QTableWidgetItem(QString("优先")));
//            break;
//        default:
//            break;
//        }

//        switch (etask_sta[h])
//        {
//        case(0):ui->tableWidget_2->setItem(h, 3, new QTableWidgetItem(QString("待执行")));
//            break;
//        case(1):ui->tableWidget_2->setItem(h, 3, new QTableWidgetItem(QString("执行中")));
//            break;
//        case(2):ui->tableWidget_2->setItem(h, 3, new QTableWidgetItem(QString("已完成")));
//            break;
//        default:
//            break;
//        }

//        ui->tableWidget_2->setItem(h, 4, new QTableWidgetItem(QString("%1%").arg(etask_percent[h])));

//        switch (etask_source[h])
//        {
//        case(0):ui->tableWidget_2->setItem(h, 5, new QTableWidgetItem(QString("wms")));
//            break;
//        case(1):ui->tableWidget_2->setItem(h, 5, new QTableWidgetItem(QString("a")));
//            break;
//        case(2):ui->tableWidget_2->setItem(h, 5, new QTableWidgetItem(QString("b")));
//            break;
//        default:
//            break;
//        }



//        ui->tableWidget_2->setItem(h, 6, new QTableWidgetItem(QString("2022-%1").arg(etask_time[h])));

//    }




//    //qDebug()<<etask_ip[0].data()<<etask_ip[1].data()<<etask_ip[2].data()<<etask_ip[3].data()<<etask_ip[4].data();

//}


//侧边栏按下效果
void MainWindow::on_netManage_toggled(bool checked)
{
    if(checked)
    {
        ui->netManage->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->netManage->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->netManage->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");   //此处可插入背景图片作为选中效果
    }
    else
    {
        ui->netManage->setIconSize(QSize(50,50));
        ui->netManage->setFont(QFont("宋体",17,QFont::Bold));
        ui->netManage->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_offerManage_toggled(bool checked)
{
    if(checked)
    {
        ui->offerManage->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->offerManage->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->offerManage->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->offerManage->setIconSize(QSize(50,50));
        ui->offerManage->setFont(QFont("宋体",17,QFont::Bold));
        ui->offerManage->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_diaoduManage_toggled(bool checked)
{
    if(checked)
    {
        ui->diaoduManage->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->diaoduManage->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->diaoduManage->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->diaoduManage->setIconSize(QSize(50,50));
        ui->diaoduManage->setFont(QFont("宋体",17,QFont::Bold));
        ui->diaoduManage->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_stateMonitor_toggled(bool checked)
{
    if(checked)
    {
        ui->stateMonitor->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->stateMonitor->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->stateMonitor->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->stateMonitor->setIconSize(QSize(50,50));
        ui->stateMonitor->setFont(QFont("宋体",17,QFont::Bold));
        ui->stateMonitor->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_AMRManage_toggled(bool checked)
{
    if(checked)
    {
        ui->AMRManage->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->AMRManage->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->AMRManage->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->AMRManage->setIconSize(QSize(50,50));
        ui->AMRManage->setFont(QFont("宋体",17,QFont::Bold));
        ui->AMRManage->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_waishePanel_toggled(bool checked)
{
    if(checked)
    {
        ui->waishePanel->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->waishePanel->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->waishePanel->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->waishePanel->setIconSize(QSize(50,50));
        ui->waishePanel->setFont(QFont("宋体",17,QFont::Bold));
        ui->waishePanel->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_elecMap_toggled(bool checked)
{
    if(checked)
    {
        ui->elecMap->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->elecMap->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->elecMap->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->elecMap->setIconSize(QSize(50,50));
        ui->elecMap->setFont(QFont("宋体",17,QFont::Bold));
        ui->elecMap->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_dataCollect_toggled(bool checked)
{
    if(checked)
    {
        ui->dataCollect->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->dataCollect->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->dataCollect->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->dataCollect->setIconSize(QSize(50,50));
        ui->dataCollect->setFont(QFont("宋体",17,QFont::Bold));
        ui->dataCollect->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_workData_toggled(bool checked)
{
    if(checked)
    {
        ui->workData->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->workData->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->workData->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->workData->setIconSize(QSize(50,50));
        ui->workData->setFont(QFont("宋体",17,QFont::Bold));
        ui->workData->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_userManage_toggled(bool checked)
{
    if(checked)
    {
        ui->userManage->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->userManage->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->userManage->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->userManage->setIconSize(QSize(50,50));
        ui->userManage->setFont(QFont("宋体",17,QFont::Bold));
        ui->userManage->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_mapSwitch_stateChanged(int arg1)
{
    bool status = ui->mapSwitch->isChecked();
    if(status == true)
    {
       ui->mapChange->setCurrentIndex(1);
    }
    else
    {
        ui->mapChange->setCurrentIndex(0);
    }
}

/*************************************************数据库部分*********************************************************/
//编辑对话框显示相应记录条
void MainWindow::updateRecord(int recNo)
{
    QSqlRecord  curRec=qryModel->record(recNo); //获取当前记录
    QString empNo=curRec.value("offerID").toString();//获取EmpNo

    QSqlQuery query; //查询出当前记录的所有字段
    query.prepare("select * from test where offerID = :ID");
    query.bindValue(":ID",empNo);
    query.exec();
    query.first();

    if (!query.isValid()) //是否为有效记录
        return;

    curRec=query.record();//获取当前记录的数据
    editDialog    *dataDialog=new editDialog(this); //创建对话框
    Qt::WindowFlags    flags=dataDialog->windowFlags();

    dataDialog->setUpdateRecord(curRec);//调用对话框函数更新数据和界面
    int ret = dataDialog->exec();// 以模态方式显示对话框
    if (ret==QDialog::Accepted) //OK键被按下
    {
        QSqlRecord  recData=dataDialog->getRecordData(); //获得对话框返回的记录

        query.prepare("update test set offerPriority=:offerPriority where offerID = :ID");

        query.bindValue(":offerPriority",recData.value("offerPriority"));
        query.bindValue(":ID",empNo);

        if (!query.exec())
            QMessageBox::critical(this, "错误", "记录更新错误\n"+query.lastError().text(),
                                     QMessageBox::Ok,QMessageBox::NoButton);
        else
            qryModel->query().exec();//数据模型重新查询数据，更新tableView显示
    }
    delete dataDialog;

}

//打开连接数据库
void MainWindow::openTable()
{
    //打开数据库
    DB=QSqlDatabase::addDatabase("QSQLITE"); //添加 SQL LITE数据库驱动
    DB.setDatabaseName("demodb.db3"); //设置数据库名称
    if (!DB.open())   //打开数据库
    {
        QMessageBox::warning(this, "错误", "打开数据库失败", QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }
    qryModel=new CustomSqlQueryModel(this);
    qryModel4=new CustomSqlQueryModel(this);
    qryModel5=new CustomSqlQueryModel(this);
    theSelection=new QItemSelectionModel(qryModel);

    qryModel->setQuery("SELECT offerID, offerKind, offerPriority, offerState, offerProcess, offerSourse, recieveTime FROM test LIMIT 1,11");
    if (qryModel->lastError().isValid())
    {
        QMessageBox::information(this, "错误", "数据表查询错误,错误信息\n"+qryModel->lastError().text(),
                                 QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    qryModel4->setQuery("SELECT offerID, offerState FROM test");

    qryModel5->setQuery("SELECT offerStart, offerEnd, offerPriority, recieveTime FROM offerConfirm");
    ui->offerNum->setText(QString::number(qryModel5->rowCount()));
    qryModel5->setQuery("SELECT offerStart, offerEnd, offerPriority, recieveTime FROM offerConfirm LIMIT 0,1");


    qryModel->setHeaderData(0,Qt::Horizontal,"任务ID");
    qryModel->setHeaderData(1,Qt::Horizontal,"任务类型");
    qryModel->setHeaderData(2,Qt::Horizontal,"优先级");
    qryModel->setHeaderData(3,Qt::Horizontal,"执行状态");
    qryModel->setHeaderData(4,Qt::Horizontal,"执行进度");
    qryModel->setHeaderData(5,Qt::Horizontal,"任务来源");
    qryModel->setHeaderData(6,Qt::Horizontal,"接收时间");

    qryModel4->setHeaderData(0,Qt::Horizontal,"任务ID");
    qryModel4->setHeaderData(1,Qt::Horizontal,"任务状态");

    qryModel5->setHeaderData(0,Qt::Horizontal,"任务起点");
    qryModel5->setHeaderData(1,Qt::Horizontal,"任务终点");
    qryModel5->setHeaderData(2,Qt::Horizontal,"优先级");
    qryModel5->setHeaderData(3,Qt::Horizontal,"接收时间");

    ui->tableTest->setModel(qryModel);
    ui->tableTest->setSelectionModel(theSelection);
    ui->tableTest_2->setModel(qryModel4);
    ui->offerConfirmTable->setModel(qryModel5);

}

//删除一条任务
void MainWindow::on_shanchu_clicked()
{
    if(QMessageBox::question(this,"确认删除","确认要删除？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        int curRecNo=theSelection->currentIndex().row();
        QSqlRecord  curRec=qryModel->record(curRecNo); //获取当前记录
        if (curRec.isEmpty()) //当前为空记录
            return;

        QString empNo=curRec.value("offerID").toString();//获取员工编号
        QSqlQuery query;
        query.prepare("delete from test where offerID = :ID");
        query.bindValue(":ID",empNo);

        if (!query.exec())
            QMessageBox::critical(this, "错误", "删除记录出现错误\n"+query.lastError().text(),
                                     QMessageBox::Ok,QMessageBox::NoButton);
        else //插入，删除记录后需要重新设置SQL语句查询
        {
            qryModel->query().exec();//数据模型重新查询数据，更新tableView显示
        }
    }
}

//读取数据库任务并进行下发
void MainWindow::task_timeinfo()
{
    qryModel2 = new QSqlQueryModel(this);
    qryModel2->setQuery("SELECT Task_type, SPointx, SPointy, EPointx, EPointy FROM test");
    if (qryModel2->lastError().isValid())
    {
        QMessageBox::information(this, "错误", "数据表查询错误,错误信息\n"+qryModel2->lastError().text(),
                                 QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }

//    if(D1_task_percent == 0)
//    {
//        task_num += 1;
//    }
    //qDebug()<<"任务序号："<<curent;
   if(curent<qryModel2->rowCount() && (D1_task_percent == 0||D2_task_percent == 0)&&(B1_task_percent == 0||B2_task_percent == 0))
   {
       QSqlRecord conData = qryModel2->record(curent); //获取当前记录
       int tk_type  = conData.value("Task_type").toInt();
       int stPointx = conData.value("SPointx").toInt();//获取坐标
       int stPointy = conData.value("SPointy").toInt();//获取坐标
       int etPointx = conData.value("EPointx").toInt();//获取坐标
       int etPointy = conData.value("EPointy").toInt();//获取坐标
       cfunction_string(tk_type,stPointx,stPointy,etPointx,etPointy);
       curent++;
   }


}


/******************************************************
 * 测试：打通数据库下发(仙工小车）
 * 一次性下发数据库中多条指令任务，根据任务列表构造json数据内容
 * 此处用指针数组+循环方式进行json内容构造
******************************************************/
void MainWindow::DB_task()
{
    qryModel3 = new CustomSqlQueryModel(this);
    qryModel3->setQuery("SELECT offerStart, offerEnd, offerProcess, offerID FROM test");
    quint16 sendCommand = 3066;     //编号3066为指定路径导航api
    if(DB_current<qryModel3->rowCount())
    {
        QSqlRecord taskData = qryModel3->record(DB_current); //获取当前记录
        if(taskData.value("offerProcess").toInt() == 0 && recv_task.m_task_status == 0 && recv_task.m_task_status == 4)
        {
        QString end = taskData.value("offerEnd").toString();
        QString start = taskData.value("offerStart").toString();
        QString id = taskData.value("offerID").toString();

        //构造Json格式字符串
        QJsonObject task_list;
        task_list.insert("id",end);
        task_list.insert("source_id",start);
        task_list.insert("task_id",id);
        QJsonArray task_array;
        task_array.append(QJsonValue(task_list));
        QJsonObject whole_list;
        whole_list.insert("move_task_list",QJsonValue(task_array));

        QJsonDocument doc;
        doc.setObject(whole_list);

        QByteArray sendData = doc.toJson(QJsonDocument::Indented);
        qDebug()<<"ip: "<< sendData;
        quint16 number = 1;
        emit writeTcpData(sendCommand,sendData, number);

        QSqlQuery query; //查询出当前记录的所有字段
        query.prepare("update test set offerProcess=:offerProcess where offerID = :ID");
        query.bindValue(":ID",id);
        query.bindValue(":offerProcess",100);
        query.exec();

        DB_current++;
        }
        else if(taskData.value("offerProcess").toInt() != 0)
        {
           DB_current++;
        }
    }
}


//编辑按钮或者双击列表都可以打开相应任务编辑页面
void MainWindow::on_xiugai_clicked()
{
    int curRecNo=theSelection->currentIndex().row();
    updateRecord(curRecNo);
}

void MainWindow::on_tableTest_doubleClicked(const QModelIndex &index)
{
    int curRecNo=index.row();
    updateRecord(curRecNo);
}

//新建任务数据保存到记录mRecord
QSqlRecord MainWindow::getRecordData(QSqlQuery quer)
{
    //newRecord获得空记录
    newRecord = quer.record();
    //为记录赋值
    newRecord.setValue("offerKind",ui->newOfferKind->currentText());
    newRecord.setValue("offerStart",ui->newOfferStart->currentText());
    newRecord.setValue("startHigh",ui->newstartHigh->currentText());
    newRecord.setValue("offerEnd",ui->newOfferEnd->currentText());
    newRecord.setValue("endHigh",ui->newendHigh->currentText());
    newRecord.setValue("offerPriority",ui->newPriority->currentText());

    return  newRecord; //以记录作为返回值
}

void MainWindow::on_newOk_clicked()
{
    //此处要先读一条空记录才能赋值记录
    QSqlQuery query;
    query.exec("select * from test where offerID =-1"); //实际不查询出记录，只查询字段信息
    //获取新建任务的具体信息
    QSqlRecord  recData = getRecordData(query);
    recData.setValue("offerID","dlkeqw");

    //新建query对象以实现插入记录操作
    query.prepare("INSERT INTO test (offerID, offerState, offerProcess, offerSourse, recieveTime, offerKind, offerStart, startHigh, offerEnd, endHigh, offerPriority) "
                  "VALUES(:offerID, :offerState, :offerProcess, :offerSourse, :recieveTime, :offerKind, :offerStart, :startHigh, :offerEnd, :endHigh, :offerPriority)");
    //绑定对应的值
    query.bindValue(":offerID",recData.value("offerID"));
    query.bindValue(":offerState","待执行");
    query.bindValue(":offerProcess", 0);
    query.bindValue(":offerSourse", "TSX");
    query.bindValue(":recieveTime", "22:14:20");
    query.bindValue(":offerKind",recData.value("offerKind"));
    query.bindValue(":offerStart",recData.value("offerStart"));
    query.bindValue(":startHigh",recData.value("startHigh"));
    query.bindValue(":offerEnd",recData.value("offerEnd"));
    query.bindValue(":endHigh",recData.value("endHigh"));
    query.bindValue(":offerPriority",recData.value("offerPriority"));

    if (!query.exec())
        QMessageBox::critical(this, "错误", "插入记录错误\n"+query.lastError().text(),
                                 QMessageBox::Ok,QMessageBox::NoButton);
    else //插入，删除记录后需要重新设置SQL语句查询
    {
        QMessageBox::information(this, "新建成功", "牛逼",
                                 QMessageBox::Ok,QMessageBox::NoButton);
        //此处要重新执行查询语句，不然显示的最大行数会被限制
        QString sqlStr=qryModel->query().executedQuery();//  执行过的SELECT语句
        qryModel->setQuery(sqlStr);         //重新查询数据
    }
}



void MainWindow::on_debugSwitch_stateChanged(int arg1)
{
    bool status = ui->debugSwitch->isChecked();
    if(status == true)
    {
       ui->debug_show->setCurrentIndex(0);
    }
    else
    {
        ui->debug_show->setCurrentIndex(1);
    }
}


//拒绝当前任务
void MainWindow::on_rejectOffer_clicked()
{
    QSqlQuery query;
    query.prepare("delete from offerConfirm where offerID = (select offerID from offerConfirm limit 0,1)");

    if (!query.exec())
        QMessageBox::critical(this, "错误", "删除记录出现错误\n"+query.lastError().text(),
                                 QMessageBox::Ok,QMessageBox::NoButton);
    else //插入，删除记录后需要重新设置SQL语句查询
    {
        qryModel5->setQuery("SELECT offerStart, offerEnd, offerPriority, recieveTime FROM offerConfirm");
        ui->offerNum->setText(QString::number(qryModel5->rowCount()));
        qryModel5->setQuery("SELECT offerStart, offerEnd, offerPriority, recieveTime FROM offerConfirm LIMIT 0,1");
    }
}

void MainWindow::on_acceptOffer_clicked()
{
     QSqlQuery query;
     query.exec("SELECT offerStart, offerEnd, offerPriority, recieveTime FROM offerConfirm LIMIT 0,1");
     //需要特别注意，刚执行完query.exec()这个函数时得到结果集，query是指向结果集以外的,此处要用next函数
     query.next();
     if (!query.isValid()) //是否为有效记录
     {
         qDebug()<<"error!";
         return;
     }
     //QSqlRecord  recData = qryModel5->record(0);
     QSqlRecord  recData = query.record();
     query.prepare("INSERT INTO test (offerID, offerState, offerProcess, offerSourse, recieveTime, offerKind, offerStart, startHigh, offerEnd, endHigh, offerPriority) "
                   "VALUES(:offerID, :offerState, :offerProcess, :offerSourse, :recieveTime, :offerKind, :offerStart, :startHigh, :offerEnd, :endHigh, :offerPriority)");
     //绑定对应的值
     query.bindValue(":offerID","100");
     query.bindValue(":offerState","待执行");
     query.bindValue(":offerProcess", 0);
     query.bindValue(":offerSourse", "TSX");
     query.bindValue(":recieveTime", recData.value("recieveTime"));
     query.bindValue(":offerKind","出库");
     query.bindValue(":offerStart",recData.value("offerStart"));
     query.bindValue(":startHigh",0);
     query.bindValue(":offerEnd",recData.value("offerEnd"));
     query.bindValue(":endHigh",0);
     query.bindValue(":offerPriority",recData.value("offerPriority"));
     if (!query.exec())
         QMessageBox::critical(this, "错误", "删除记录出现错误\n"+query.lastError().text(),
                                  QMessageBox::Ok,QMessageBox::NoButton);
     else //插入，删除记录后需要重新设置SQL语句查询
     {
         query.exec("delete from offerConfirm where offerID = (select offerID from offerConfirm limit 0,1)");
         qryModel5->setQuery("SELECT offerStart, offerEnd, offerPriority, recieveTime FROM offerConfirm");
         ui->offerNum->setText(QString::number(qryModel5->rowCount()));
         qryModel5->setQuery("SELECT offerStart, offerEnd, offerPriority, recieveTime FROM offerConfirm LIMIT 0,1");
     }

}
