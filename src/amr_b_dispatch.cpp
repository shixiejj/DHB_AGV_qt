#include "amr_b_dispatch.h"
#include<iostream>
#include <QDebug>
#include "mainwindow.h"
#include "global_variables.h"
#include <sys/time.h>
#include <qelapsedtimer.h>
using namespace std;
void Delay_MSec(float msec)
{
    QEventLoop loop;//定义一个新的事件循环
        QTimer::singleShot(msec, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
        loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}
//定义4个机器人类
Robot AMR_B1;
Robot AMR_B2;
Robot AMR_D1;
Robot AMR_D2;


    double b_Dispatch_function(int sec)
    {
     QElapsedTimer mstimer;
     mstimer.start();
     Path_AMR_B1 = "";
     Path_AMR_B2 = "";

     //B2_task_percent=1;

     qDebug()<<"b1状态："<<B1_task_percent;
     qDebug()<<"b2状态："<<B2_task_percent;
     AMR_B1.Task_State=B1_task_percent;
     AMR_B2.Task_State=B2_task_percent;

        AMR_B1.x0 = 9250;
        AMR_B1.y0 = 4990;
        AMR_B1.x[0] = AMR_B1.x0;
        AMR_B1.y[0] = AMR_B1.y0;

        AMR_B2.x0 = 9250;
        AMR_B2.y0 = 2625;
        AMR_B2.x[0] = AMR_B2.x0;
        AMR_B2.y[0] = AMR_B2.y0;

        if(sec == 1)
        {
           Delay_MSec(1);
        }



        //出库任务
        if (B_Task == 1)
        {
            if (AMR_B1.Task_State == 0 && AMR_B2.Task_State == 0)
            {
                if (B_Take_y == 4990)
                {
                    AMR_B1.Outbound_Date = 1;
                }

                if (B_Take_y == 2625)
                {
                    AMR_B2.Outbound_Date = 1;
                }
            }

            if (AMR_B1.Task_State == 0 && AMR_B2.Task_State == 1)
            {
                AMR_B1.Outbound_Date = 1;
            }

            if (AMR_B1.Task_State == 1 && AMR_B2.Task_State == 0)
            {
                AMR_B2.Outbound_Date = 1;
            }

            if (AMR_B1.Outbound_Date == 1 || AMR_B2.Outbound_Date == 1)
            {
                B_Task = 0;
            }
        }

        if (B_Task == 2)
        {
            if (AMR_B1.Task_State == 0 && AMR_B2.Task_State == 0)
            {
                if (B_Deliver_y == 4990)
                {
                    AMR_B1.Inbound_Date = 1;
                }

                if (B_Deliver_y == 2625)
                {
                    AMR_B2.Inbound_Date = 1;
                }
            }

            if (AMR_B1.Task_State == 0 && AMR_B2.Task_State == 1)
            {
                AMR_B1.Inbound_Date = 1;
            }

            if (AMR_B1.Task_State == 1 && AMR_B2.Task_State == 0)
            {
                AMR_B2.Inbound_Date = 1;
            }

            if (AMR_B1.Inbound_Date == 1 || AMR_B2.Inbound_Date == 1)
            {
                B_Task = 0;
            }
        }

        if (B_Task == 3)
        {
            if (AMR_B1.Task_State == 0 && AMR_B2.Task_State == 0)
            {
                if (B_Take_y == 4990 && B_Deliver_y == 4990)
                {
                    AMR_B1.Shift_Warehouse_Date = 1;
                }

                if (B_Take_y == 4990 && B_Deliver_y == 2625)
                {
                    AMR_B1.Route = abs(AMR_B1.x0 - B_Take_x) + abs(B_Take_x - 11096) + 2365 + abs(11096 - B_Deliver_x) + abs(B_Deliver_x - 11096) + 2365 + abs(11096 - AMR_B1.x0);
                    AMR_B2.Route = abs(AMR_B2.x0 - 11096) + 2365 + abs(11096 - B_Take_x) + abs(B_Take_x - 11096) + 2365 + abs(11096 - B_Deliver_x) + abs(B_Deliver_x - AMR_B2.x0);
                    if (AMR_B1.Route < AMR_B2.Route)
                    {
                        AMR_B1.Shift_Warehouse_Date = 1;
                    }
                    if (AMR_B1.Route >= AMR_B2.Route)
                    {
                        AMR_B2.Shift_Warehouse_Date = 1;
                    }
                }

                if (B_Take_y == 2625 && B_Deliver_y == 4990)
                {
                    AMR_B1.Route = abs(AMR_B1.x0 - 11096) + 2365 + abs(11096 - B_Take_x) + abs(B_Take_x - 11096) + 2365 + abs(11096 - B_Deliver_x) + abs(B_Deliver_x - AMR_B1.x0);
                    AMR_B2.Route = abs(AMR_B2.x0 - Take_x) + abs(B_Take_x - 11096) + 2365 + abs(11096 - B_Deliver_x) + abs(B_Deliver_x - 11096) + 2365 + abs(11096 - AMR_B2.x0);
                    if (AMR_B1.Route < AMR_B2.Route)
                    {
                        AMR_B1.Shift_Warehouse_Date = 1;
                    }
                    if (AMR_B1.Route >= AMR_B2.Route)
                    {
                        AMR_B2.Shift_Warehouse_Date = 1;
                    }
                }

                if (B_Take_y == 2625 && B_Deliver_y == 2625)
                {
                    AMR_B2.Shift_Warehouse_Date = 1;
                }
            }

            if (AMR_B1.Task_State == 0 && AMR_B2.Task_State == 1)
            {
                AMR_B1.Shift_Warehouse_Date = 1;
            }

            if (AMR_B1.Task_State == 1 && AMR_B2.Task_State == 0)
            {
                AMR_B2.Shift_Warehouse_Date = 1;
            }

            if (AMR_B1.Shift_Warehouse_Date == 1 || AMR_B2.Shift_Warehouse_Date == 1)
            {
                B_Task = 0;
            }
        }

        //出库数据更新
        if (AMR_B1.Outbound_Date == 1 && AMR_B1.Task_State == 0)
        {
            AMR_B1.Outbound_Task = 1;
            AMR_B1.State = 1;
            AMR_B1.Take_x = B_Take_x;
            AMR_B1.Take_y = B_Take_y;
            AMR_B1.Deliver_x = B_Deliver_x;
            AMR_B1.Deliver_y = B_Deliver_y;
            AMR_B1.Destination_x = Deliver_x;
            AMR_B1.Destination_y = Deliver_y;
            AMR_B1.Outbound_Date = 0;


        }

        if (AMR_B2.Outbound_Date == 1 && AMR_B2.Task_State == 0)
        {
            AMR_B2.Outbound_Task = 1;
            AMR_B2.State = 1;
            AMR_B2.Take_x = B_Take_x;
            AMR_B2.Take_y = B_Take_y;
            AMR_B2.Deliver_x = B_Deliver_x;
            AMR_B2.Deliver_y = B_Deliver_y;
            AMR_B2.Destination_x = Deliver_x;
            AMR_B2.Destination_y = Deliver_y;
            AMR_B2.Outbound_Date = 0;
        }


        //入库数据更新
        if (AMR_B1.Inbound_Date == 1 && AMR_B1.Task_State == 0)
        {
            AMR_B1.Inbound_Task = 1;
            AMR_B1.State = 3;
            AMR_B1.Take_x = B_Take_x;
            AMR_B1.Take_y = B_Take_y;
            AMR_B1.Deliver_x = B_Deliver_x;
            AMR_B1.Deliver_y = B_Deliver_y;
            AMR_B1.Inbound_Date = 0;
        }

        if (AMR_B2.Inbound_Date == 1 && AMR_B2.Task_State == 0)
        {
            AMR_B2.Inbound_Task = 1;
            AMR_B2.State = 3;
            AMR_B2.Take_x = B_Take_x;
            AMR_B2.Take_y = B_Take_y;
            AMR_B2.Deliver_x = B_Deliver_x;
            AMR_B2.Deliver_y = B_Deliver_y;
            AMR_B2.Inbound_Date = 0;
        }

        //移库数据更新
        if (AMR_B1.Shift_Warehouse_Date == 1)
        {
            AMR_B1.Shift_Warehouse_Task = 1;
            AMR_B1.State = 5;
            AMR_B1.Take_x = B_Take_x;
            AMR_B1.Take_y = B_Take_y;
            AMR_B1.Deliver_x = B_Deliver_x;
            AMR_B1.Deliver_y = B_Deliver_y;
            AMR_B1.Shift_Warehouse_Date = 0;
        }

        if (AMR_B2.Shift_Warehouse_Date == 1)
        {
            AMR_B2.Shift_Warehouse_Task = 1;
            AMR_B2.State = 5;
            AMR_B2.Take_x = B_Take_x;
            AMR_B2.Take_y = B_Take_y;
            AMR_B2.Deliver_x = B_Deliver_x;
            AMR_B2.Deliver_y = B_Deliver_y;
            AMR_B2.Shift_Warehouse_Date = 0;
        }


        for (int m = 0; m < 1999; m++)
        {
            //执行任务
            if (AMR_B1.Outbound_Task == 1 || AMR_B1.Inbound_Task == 1 || AMR_B1.Shift_Warehouse_Task == 1)
            {
                AMR_B1.Task_State = 1;
            //执行出库任务
                //执行出库到料架取料箱任务
                if (AMR_B1.State == 1)
                {
                    //AMR_B1.Take_y==4990的情况
                    if (AMR_B1.Take_y == 4990)
                    {
                        //执行出库到料架取料箱任务
                        if (AMR_B1.x[m] - AMR_B1.Take_x <= 0 && abs(AMR_B1.y[m] - AMR_B1.Take_y) <= 10 && AMR_B1.State == 1)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        //到达取物料区等待取物料
                        if (abs(AMR_B1.x[m] - AMR_B1.Take_x) <= 10 && abs(AMR_B1.y[m] - AMR_B1.Take_y) <= 10 && AMR_B1.State == 1)
                        {
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                            switch (AMR_B1.Take_x)
                            {
                            case 8948:Path_AMR_B1.append("l1|"); break;
                            case 9446:Path_AMR_B1.append("l2|"); break;
                            case 9925:Path_AMR_B1.append("l3|"); break;
                            case 12230:Path_AMR_B1.append("l4|"); break;
                            case 12768:Path_AMR_B1.append("l5|"); break;
                            case 13258:Path_AMR_B1.append("l6|"); break;
                            }
                            AMR_B1.State = 2;
                        }
                    }

                    //AMR_B1.Take_y==2625的情况
                    if (AMR_B1.Take_y == 2625)
                    {
                        if (AMR_B1.x[m] - 11096 <= 0 && abs(AMR_B1.y[m] - AMR_B1.y0) <= 10 && AMR_B1.State == 1)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        //输出路点
                        if (abs(AMR_B1.x[m] - 11096) <= 10 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 1)
                        {
                            Path_AMR_B1.append("i1,");
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - 11096) <= 10 && AMR_B1.y[m] - AMR_B1.Take_y > 0 && AMR_B1.State == 1)
                        {
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = -B1_Vy;
                        }

                        //输出路点
                        if (abs(AMR_B1.x[m] - 11096) <= 10 && abs(AMR_B1.y[m] - AMR_B1.Take_y) <= 10 && AMR_B1.State == 1)
                        {
                            Path_AMR_B1.append("i2,");
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                        }

                        //分为AMR_B1.Take_x <= 11096时, 和AMR_B1.Take_x > 11096时
                        if (AMR_B1.x[m] - AMR_B1.Take_x > 0 && abs(AMR_B1.y[m] - AMR_B1.Take_y) <= 10 && AMR_B1.State == 1)
                        {
                            AMR_B1.Vx[m] = -B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }
                        if (AMR_B1.x[m] - AMR_B1.Take_x <= 0 && abs(AMR_B1.y[m] - AMR_B1.Take_y) <= 10 && AMR_B1.State == 1)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        //到达取物料区等待取物料
                        if (abs(AMR_B1.x[m] - AMR_B1.Take_x) <= 10 && abs(AMR_B1.y[m] - AMR_B1.Take_y) <= 10 && AMR_B1.State == 1)
                        {
                            switch (AMR_B1.Take_x)
                            {
                            case 8948:Path_AMR_B1.append("l7|"); break;
                            case 9446:Path_AMR_B1.append("l8|"); break;
                            case 9925:Path_AMR_B1.append("l9|"); break;
                            case 12230:Path_AMR_B1.append("l10|"); break;
                            case 12768:Path_AMR_B1.append("l11|"); break;
                            case 13258:Path_AMR_B1.append("l12|"); break;
                            }
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                            AMR_B1.State = 2;
                        }
                    }
                }

                //执行出库送料箱到出入库接驳点任务
                if (AMR_B1.State == 2)
                {
                    if (AMR_B1.x[m] - 11096 <= 0 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 2)
                    {
                        AMR_B1.Vx[m] = B1_Vx;
                        AMR_B1.Vy[m] = 0;
                    }
                    if (AMR_B1.x[m] - 11096 > 0 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 2)
                    {
                        AMR_B1.Vx[m] = -B1_Vx;
                        AMR_B1.Vy[m] = 0;
                    }

                    if (abs(AMR_B1.x[m] - 11096) <= 10 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 2)
                    {
                        Path_AMR_B1.append("i2,");
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = 0;
                    }

                    if (abs(AMR_B1.x[m] - 11096) <= 10 && AMR_B1.y[m] - 4990 <= 0 && AMR_B1.State == 2)
                    {
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = B1_Vy;
                    }

                    if (abs(AMR_B1.x[m] - 11096) <= 10 && abs(AMR_B1.y[m] - AMR_B1.y0) <= 10 && AMR_B1.State == 2)
                    {
                        Path_AMR_B1.append("i1,");
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = 0;
                    }


                    if (AMR_B1.x[m] - AMR_B1.Deliver_x > 0 && abs(AMR_B1.y[m] - AMR_B1.y0) <= 10 && AMR_B1.State == 2)
                    {
                        AMR_B1.Vx[m] = -B1_Vx;
                        AMR_B1.Vy[m] = 0;
                    }

                    if (abs(AMR_B1.x[m] - AMR_B1.Deliver_x) <= 10 && abs(AMR_B1.y[m] - AMR_B1.y0) <= 10 && AMR_B1.State == 2)
                    {
                        Path_AMR_B1.append("g1,");
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = 0;
                    }

                    if (abs(AMR_B1.x[m] - AMR_B1.Deliver_x) <= 10 && AMR_B1.y[m] - AMR_B1.Deliver_y > 0 && AMR_B1.State == 2)
                    {
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = -B1_Vy;
                    }

                    if (abs(AMR_B1.x[m] - AMR_B1.Deliver_x) <= 10 && abs(AMR_B1.y[m] - AMR_B1.Deliver_y) <= 10 && AMR_B1.State == 2)
                    {
                        switch (AMR_B1.Deliver_y)
                        {
                        case 3807:Path_AMR_B1.append("s2|"); break;
                        case 1653:Path_AMR_B1.append("s4|"); break;
                        }
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = 0;
                        AMR_B1.State = 8;
                    }
                }

                //执行入库任务
                    //执行入库到出入库接驳点取料箱任务
                if (AMR_B1.State == 3)
                {
                    if (AMR_B1.x[m] - AMR_B1.Take_x > 0 && abs(AMR_B1.y[m] - AMR_B1.y0) <= 10 && AMR_B1.State == 3)
                    {
                        AMR_B1.Vx[m] = -B1_Vx;
                        AMR_B1.Vy[m] = 0;
                    }

                    if (abs(AMR_B1.x[m] - AMR_B1.Take_x) <= 10 && abs(AMR_B1.y[m] - AMR_B1.y0) <= 10 && AMR_B1.State == 3)
                    {
                        Path_AMR_B1.append("g1,");
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = 0;
                    }

                    if (abs(AMR_B1.x[m] - AMR_B1.Take_x) <= 10 && AMR_B1.y[m] - AMR_B1.Take_y > 0 && AMR_B1.State == 3)
                    {
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = -B1_Vy;
                    }

                    if (abs(AMR_B1.x[m] - AMR_B1.Take_x) <= 10 && abs(AMR_B1.y[m] - AMR_B1.Take_y) <= 10 && AMR_B1.State == 3)
                    {
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = 0;
                        if (AMR_B1.Take_y == 3807)
                        {
                            Path_AMR_B1.append("s2|");
                            Conection_1_State = 0;
                        }
                        if (AMR_B1.Take_y == 1653)
                        {
                            Path_AMR_B1.append("s4|");
                            Conection_2_State = 0;
                        }
                        AMR_B1.State = 4;
                    }
                }

                //执行入库送料箱到料架任务
                if (AMR_B1.State == 4)
                {
                    //AMR_B1.Deliver_y == 4990的情况
                    if (AMR_B1.Deliver_y == 4990)
                    {
                        if (abs(AMR_B1.x[m] - AMR_B1.Take_x) <= 10 && AMR_B1.y[m] - 4990 < 0 && AMR_B1.State == 4)
                        {
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = B1_Vy;
                        }

                        if (abs(AMR_B1.x[m] - AMR_B1.Take_x) <= 10 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 4)
                        {
                            Path_AMR_B1.append("g1,");
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (AMR_B1.x[m] - AMR_B1.Deliver_x < 0 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 4)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - AMR_B1.Deliver_x) <= 10 && abs(AMR_B1.y[m] - AMR_B1.Deliver_y) <= 10 && AMR_B1.State == 4)
                        {
                            switch (AMR_B1.Deliver_x)
                            {
                            case 8948:Path_AMR_B1.append("l1|"); break;
                            case 9446:Path_AMR_B1.append("l2|"); break;
                            case 9925:Path_AMR_B1.append("l3|"); break;
                            case 12230:Path_AMR_B1.append("l4|"); break;
                            case 12768:Path_AMR_B1.append("l5|"); break;
                            case 13258:Path_AMR_B1.append("l6|"); break;
                            }
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                            AMR_B1.State = 8;
                        }
                    }

                    //AMR_B1.Deliver_y == 2625的情况
                    if (AMR_B1.Deliver_y == 2625)
                    {
                        if (abs(AMR_B1.x[m] - AMR_B1.Take_x) <= 10 && AMR_B1.y[m] - 4990 < 0 && AMR_B1.State == 4)
                        {
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = B1_Vy;
                        }

                        if (abs(AMR_B1.x[m] - AMR_B1.Take_x) <= 10 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 4)
                        {
                            Path_AMR_B1.append("g1,");
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (AMR_B1.x[m] - 11096 < 0 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 4)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - 11096) <= 10 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 4)
                        {
                            Path_AMR_B1.append("i1,");
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - 11096) <= 10 && AMR_B1.y[m] - AMR_B1.Deliver_y > 0 && AMR_B1.State == 4)
                        {
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = -B1_Vy;
                        }

                        if (abs(AMR_B1.x[m] - 11096) <= 10 && abs(AMR_B1.y[m] - AMR_B1.Deliver_y) <= 10 && AMR_B1.State == 4)
                        {
                            Path_AMR_B1.append("i2,");
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (AMR_B1.x[m] - AMR_B1.Deliver_x > 0 && abs(AMR_B1.y[m] - AMR_B1.Deliver_y) <= 10 && AMR_B1.State == 4)
                        {
                            AMR_B1.Vx[m] = -B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }
                        if (AMR_B1.x[m] > 8000 && AMR_B1.x[m] - AMR_B1.Deliver_x < 0 && abs(AMR_B1.y[m] - AMR_B1.Deliver_y) <= 10 && AMR_B1.State == 4)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - AMR_B1.Deliver_x) <= 10 && abs(AMR_B1.y[m] - AMR_B1.Deliver_y) <= 10 && AMR_B1.State == 4)
                        {
                            switch (AMR_B1.Deliver_x)
                            {
                            case 8948:Path_AMR_B1.append("l7|"); break;
                            case 9446:Path_AMR_B1.append("l8|"); break;
                            case 9925:Path_AMR_B1.append("l9|"); break;
                            case 12230:Path_AMR_B1.append("l10|"); break;
                            case 12768:Path_AMR_B1.append("l11|"); break;
                            case 13258:Path_AMR_B1.append("l12|"); break;
                            }
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                            AMR_B1.State = 8;
                        }
                    }
                }

                //执行移库任务
                    //执行移库去取料箱任务
                if (AMR_B1.State == 5)
                {
                    if (AMR_B1.Take_y == 4990)
                    {
                        if (AMR_B1.x[m] - AMR_B1.Take_x < 0 && abs(AMR_B1.y[m] - AMR_B1.Take_y) <= 10 && AMR_B1.State == 5)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - AMR_B1.Take_x) <= 10 && abs(AMR_B1.y[m] - AMR_B1.Take_y) <= 10 && AMR_B1.State == 5)
                        {
                            switch (AMR_B1.Take_x)
                            {
                            case 8948:Path_AMR_B1.append("l1|"); break;
                            case 9446:Path_AMR_B1.append("l2|"); break;
                            case 9925:Path_AMR_B1.append("l3|"); break;
                            case 12230:Path_AMR_B1.append("l4|"); break;
                            case 12768:Path_AMR_B1.append("l5|"); break;
                            case 13258:Path_AMR_B1.append("l6|"); break;
                            }
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                            AMR_B1.State = 6;
                        }
                    }

                    if (AMR_B1.Take_y == 2625)
                    {
                        if (AMR_B1.x[m] - 11096 < 0 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 5)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - 11096) <= 10 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 5)
                        {
                            Path_AMR_B1.append("i1,");
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - 11096) <= 10 && AMR_B1.y[m] - 2625 > 0 && AMR_B1.State == 5)
                        {
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = -B1_Vy;
                        }

                        if (abs(AMR_B1.x[m] - 11096) <= 10 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 5)
                        {
                            Path_AMR_B1.append("i2,");
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (AMR_B1.x[m] - AMR_B1.Take_x > 0 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 5)
                        {
                            AMR_B1.Vx[m] = -B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }
                        if (AMR_B1.x[m] - AMR_B1.Take_x < 0 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 5)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - AMR_B1.Take_x) <= 10 && abs(AMR_B1.y[m] - AMR_B1.Take_y) <= 10 && AMR_B1.State == 5)
                        {
                            switch (AMR_B1.Take_x)
                            {
                            case 8948:Path_AMR_B1.append("l7|"); break;
                            case 9446:Path_AMR_B1.append("l8|"); break;
                            case 9925:Path_AMR_B1.append("l9|"); break;
                            case 12230:Path_AMR_B1.append("l10|"); break;
                            case 12768:Path_AMR_B1.append("l11|"); break;
                            case 13258:Path_AMR_B1.append("l12|"); break;
                            }
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                            AMR_B1.State = 6;
                        }
                    }
                }

                //执行移库送料箱到目标库位任务
                if (AMR_B1.State == 6)
                {
                    if (AMR_B1.Take_y == 4990 && AMR_B1.Deliver_y == 4990)
                    {
                        if (AMR_B1.x[m] - AMR_B1.Deliver_x > 0 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = -B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }
                        if (AMR_B1.x[m] - AMR_B1.Deliver_x < 0 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - AMR_B1.Deliver_x) <= 10 && abs(AMR_B1.y[m] - AMR_B1.Deliver_y) <= 10 && AMR_B1.State == 6)
                        {
                            switch (AMR_B1.Deliver_x)
                            {
                            case 8948:Path_AMR_B1.append("l1|"); break;
                            case 9446:Path_AMR_B1.append("l2|"); break;
                            case 9925:Path_AMR_B1.append("l3|"); break;
                            case 12230:Path_AMR_B1.append("l4|"); break;
                            case 12768:Path_AMR_B1.append("l5|"); break;
                            case 13258:Path_AMR_B1.append("l6|"); break;
                            }
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                            AMR_B1.State = 8;
                        }
                    }

                    if (AMR_B1.Take_y == 4990 && AMR_B1.Deliver_y == 2625)
                    {
                        if (AMR_B1.x[m] - 11096 > 0 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = -B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }
                        if (AMR_B1.x[m] - 11096 < 0 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - 11096) <= 10 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 6)
                        {
                            Path_AMR_B1.append("i1,");
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - 11096) <= 10 && AMR_B1.y[m] - 2625 > 0 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = -B1_Vy;
                        }

                        if (abs(AMR_B1.x[m] - 11096) <= 10 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 6)
                        {
                            Path_AMR_B1.append("i2,");
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (AMR_B1.x[m] - AMR_B1.Deliver_x > 0 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = -B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }
                        if (AMR_B1.x[m] - AMR_B1.Deliver_x < 0 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - AMR_B1.Deliver_x) <= 10 && abs(AMR_B1.y[m] - AMR_B1.Deliver_y) <= 10 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                            switch (AMR_B1.Deliver_x)
                            {
                            case 8948:Path_AMR_B1.append("l7|"); break;
                            case 9446:Path_AMR_B1.append("l8|"); break;
                            case 9925:Path_AMR_B1.append("l9|"); break;
                            case 12230:Path_AMR_B1.append("l10|"); break;
                            case 12768:Path_AMR_B1.append("l11|"); break;
                            case 13258:Path_AMR_B1.append("l12|"); break;
                            }
                            AMR_B1.State = 8;
                        }
                    }

                    if (AMR_B1.Take_y == 2625 && AMR_B1.Deliver_y == 2625)
                    {
                        if (AMR_B1.x[m] - AMR_B1.Deliver_x > 0 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = -B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }
                        if (AMR_B1.x[m] - AMR_B1.Deliver_x < 0 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - AMR_B1.Deliver_x) <= 10 && abs(AMR_B1.y[m] - AMR_B1.Deliver_y) <= 10 && AMR_B1.State == 6)
                        {
                            switch (AMR_B1.Deliver_x)
                            {
                            case 8948:Path_AMR_B1.append("l7|"); break;
                            case 9446:Path_AMR_B1.append("l8|"); break;
                            case 9925:Path_AMR_B1.append("l9|"); break;
                            case 12230:Path_AMR_B1.append("l10|"); break;
                            case 12768:Path_AMR_B1.append("l11|"); break;
                            case 13258:Path_AMR_B1.append("l12|"); break;
                            }
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                            AMR_B1.State = 8;
                        }
                    }

                    if (AMR_B1.Take_y == 2625 && AMR_B1.Deliver_y == 4990)
                    {
                        if (AMR_B1.x[m] - 11096 > 0 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = -B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }
                        if (AMR_B1.x[m] - 11096 < 0 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - 11096) <= 10 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 6)
                        {
                            Path_AMR_B1.append("i2,");
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - 11096) <= 10 && AMR_B1.y[m] - 4990 < 0 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = B1_Vy;
                        }

                        if (abs(AMR_B1.x[m] - 11096) <= 10 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 6)
                        {
                            Path_AMR_B1.append("i1,");
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (AMR_B1.x[m] - AMR_B1.Deliver_x > 0 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = -B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }
                        if (AMR_B1.x[m] - AMR_B1.Deliver_x < 0 && abs(AMR_B1.y[m] - 4990) <= 10 && AMR_B1.State == 6)
                        {
                            AMR_B1.Vx[m] = B1_Vx;
                            AMR_B1.Vy[m] = 0;
                        }

                        if (abs(AMR_B1.x[m] - AMR_B1.Deliver_x) <= 10 && abs(AMR_B1.y[m] - AMR_B1.Deliver_y) <= 10 && AMR_B1.State == 6)
                        {
                            switch (AMR_B1.Deliver_x)
                            {
                            case 8948:Path_AMR_B1.append("l1|"); break;
                            case 9446:Path_AMR_B1.append("l2|"); break;
                            case 9925:Path_AMR_B1.append("l3|"); break;
                            case 12230:Path_AMR_B1.append("l4|"); break;
                            case 12768:Path_AMR_B1.append("l5|"); break;
                            case 13258:Path_AMR_B1.append("l6|"); break;
                            }
                            AMR_B1.Vx[m] = 0;
                            AMR_B1.Vy[m] = 0;
                            AMR_B1.State = 8;
                        }
                    }
                }

                //返回待命点
                if (AMR_B1.State == 8)
                {
                    if (AMR_B1.x[m] - 11096 < 0 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 8)
                    {
                        AMR_B1.Vx[m] = B1_Vx;
                        AMR_B1.Vy[m] = 0;
                    }
                    if (AMR_B1.x[m] - 11096 > 0 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 8)
                    {
                        AMR_B1.Vx[m] = -B1_Vx;
                        AMR_B1.Vy[m] = 0;
                    }

                    if (abs(AMR_B1.x[m] - 11096) <= 10 && abs(AMR_B1.y[m] - 2625) <= 10 && AMR_B1.State == 8)
                    {
                        Path_AMR_B1.append("i2,");
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = 0;
                    }

                    if (abs(AMR_B1.x[m] - 11096) <= 10 && AMR_B1.y[m] - AMR_B1.y0 < 0 && AMR_B1.State == 8)
                    {
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = B1_Vy;
                    }

                    if (abs(AMR_B1.x[m] - 11096) <= 10 && abs(AMR_B1.y[m] - AMR_B1.y0) <= 10 && AMR_B1.State == 8)
                    {
                        Path_AMR_B1.append("i1,");
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = 0;
                    }

                    if (AMR_B1.x[m] - AMR_B1.x0 > 0 && abs(AMR_B1.y[m] - AMR_B1.y0) <= 10 && AMR_B1.State == 8)
                    {
                        AMR_B1.Vx[m] = -B1_Vx;
                        AMR_B1.Vy[m] = 0;
                    }


                    if (abs(AMR_B1.x[m] - 7785) <= 10 && AMR_B1.y[m] - AMR_B1.y0 > 0 && AMR_B1.State == 8)
                    {
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = -B1_Vy;
                    }
                    if (abs(AMR_B1.x[m] - 7785) <= 10 && AMR_B1.y[m] - AMR_B1.y0 < 0 && AMR_B1.State == 8)
                    {
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = B1_Vy;
                    }

                    if (abs(AMR_B1.x[m] - 7785) <= 10 && abs(AMR_B1.y[m] - AMR_B1.y0) <= 10 && AMR_B1.State == 8)
                    {
                        Path_AMR_B1.append("g1,");
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = 0;
                    }

                    if (AMR_B1.x[m] - AMR_B1.x0 <= 0 && abs(AMR_B1.y[m] - AMR_B1.y0) <= 10 && AMR_B1.State == 8)
                    {
                        AMR_B1.Vx[m] = B1_Vx;
                        AMR_B1.Vy[m] = 0;
                    }

                    if (abs(AMR_B1.x[m] - AMR_B1.x0) <= 15 && abs(AMR_B1.y[m] - AMR_B1.y0) <= 10 && AMR_B1.State == 8)
                    {
                        Path_AMR_B1.append("l2");
                        AMR_B1.Vx[m] = 0;
                        AMR_B1.Vy[m] = 0;
                        AMR_B1.State = 0;
                        AMR_B1.Task_State = 0;
                        AMR_B1.Outbound_Task = 0;
                        AMR_B1.Inbound_Task = 0;
                        AMR_B1.Shift_Warehouse_Task = 0;
                    }
                }
            }
            if (AMR_B1.State == 0)
            {
                AMR_B1.Vx[m] = 0;
                AMR_B1.Vy[m] = 0;
            }

            if (AMR_B2.Outbound_Task == 1 || AMR_B2.Inbound_Task == 1 || AMR_B2.Shift_Warehouse_Task == 1)
            {
                AMR_B2.Task_State = 1;
                //执行出库任务
                    //执行出库到料架取料箱任务
                if (AMR_B2.State == 1)
                {
                    if (AMR_B2.Take_y == 2625)
                    {
                        if (AMR_B2.x[m] - AMR_B2.Take_x < 0 && abs(AMR_B2.y[m] - AMR_B2.Take_y) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - AMR_B2.Take_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Take_y) <= 10)
                        {
                            switch (AMR_B2.Take_x)
                            {
                            case 8948:Path_AMR_B2.append("l7|"); break;
                            case 9446:Path_AMR_B2.append("l8|"); break;
                            case 9925:Path_AMR_B2.append("l9|"); break;
                            case 12230:Path_AMR_B2.append("l10|"); break;
                            case 12768:Path_AMR_B2.append("l11|"); break;
                            case 13258:Path_AMR_B2.append("l12|"); break;
                            }
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                            AMR_B2.State = 2;
                        }
                    }

                    if (AMR_B2.Take_y == 4990)
                    {
                        if (AMR_B2.x[m] - 11096 < 0 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                        {
                            Path_AMR_B2.append("i2,");
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && AMR_B2.y[m] - AMR_B2.Take_y <= 10)
                        {
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = B2_Vy;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Take_y) <= 10)
                        {
                            Path_AMR_B2.append("i1,");
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                        }

                        //分为S2_Take_x < 11096时, 和S2_Take_x > 11096时
                        if (AMR_B2.x[m] - AMR_B2.Take_x > 0 && abs(AMR_B2.y[m] - AMR_B2.Take_y) <= 10)
                        {
                            AMR_B2.Vx[m] = -B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }
                        if (AMR_B2.x[m] - AMR_B2.Take_x < 0 && abs(AMR_B2.y[m] - AMR_B2.Take_y) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        //到达取物料区等待取物料
                        if (abs(AMR_B2.x[m] - AMR_B2.Take_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Take_y) <= 10)
                        {
                            switch (AMR_B2.Take_x)
                            {
                            case 8948:Path_AMR_B2.append("l1|"); break;
                            case 9446:Path_AMR_B2.append("l2|"); break;
                            case 9925:Path_AMR_B2.append("l3|"); break;
                            case 12230:Path_AMR_B2.append("l4|"); break;
                            case 12768:Path_AMR_B2.append("l5|"); break;
                            case 13258:Path_AMR_B2.append("l6|"); break;
                            }
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                            AMR_B2.State = 2;
                        }
                    }
                }

                //执行出库送料箱到出入库接驳点任务
                if (AMR_B2.State == 2)
                {
                    if (AMR_B2.x[m] - 11096 < 0 && abs(AMR_B2.y[m] - 4990) <= 10)
                    {
                        AMR_B2.Vx[m] = B2_Vx;
                        AMR_B2.Vy[m] = 0;
                    }
                    if (AMR_B2.x[m] - 11096 > 0 && abs(AMR_B2.y[m] - 4990) <= 10)
                    {
                        AMR_B2.Vx[m] = -B2_Vx;
                        AMR_B2.Vy[m] = 0;
                    }

                    if (abs(AMR_B2.x[m] - 11096) <= 10 && abs(AMR_B2.y[m] - 4990) <= 10)
                    {
                        Path_AMR_B2.append("i1,");
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = 0;
                    }

                    if (abs(AMR_B2.x[m] - 11096) <= 10 && AMR_B2.y[m] - AMR_B2.y0 > 0)
                    {
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = -B2_Vy;
                    }

                    if (abs(AMR_B2.x[m] - 11096) <= 10 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                    {
                        Path_AMR_B2.append("i2,");
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = 0;
                    }

                    if (AMR_B2.x[m] - AMR_B2.Deliver_x > 0 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                    {
                        AMR_B2.Vx[m] = -B2_Vx;
                        AMR_B2.Vy[m] = 0;
                    }

                    if (abs(AMR_B2.x[m] - AMR_B2.Deliver_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                    {
                        Path_AMR_B2.append("g2,");
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = 0;
                    }

                    if (abs(AMR_B2.x[m] - AMR_B2.Deliver_x) <= 10 && AMR_B2.y[m] - AMR_B2.Deliver_y < 0)
                    {
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = B2_Vy;
                    }
                    if (abs(AMR_B2.x[m] - AMR_B2.Deliver_x) <= 10 && AMR_B2.y[m] - AMR_B2.Deliver_y > 0)
                    {
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = -B2_Vy;
                    }

                    if (abs(AMR_B2.x[m] - AMR_B2.Deliver_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Deliver_y) <= 10)
                    {
                        switch (AMR_B2.Deliver_y)
                        {
                        case 3807:Path_AMR_B2.append("s2|"); break;
                        case 1653:Path_AMR_B2.append("s4|"); break;
                        }
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = 0;
                        AMR_B2.State = 8;
                    }
                }

                //执行入库任务
                    //执行入库到出入库接驳点取料箱任务
                if (AMR_B2.State == 3)
                {
                    if (AMR_B2.x[m] - AMR_B2.Take_x > 0 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                    {
                        AMR_B2.Vx[m] = -B2_Vx;
                        AMR_B2.Vy[m] = 0;
                    }

                    if (abs(AMR_B2.x[m] - AMR_B2.Take_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                    {
                        Path_AMR_B2.append("g2,");
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = 0;
                    }

                    if (abs(AMR_B2.x[m] - AMR_B2.Take_x) <= 10 && AMR_B2.y[m] - AMR_B2.Take_y < 0)
                    {
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = B2_Vy;
                    }
                    if (abs(AMR_B2.x[m] - AMR_B2.Take_x) <= 10 && AMR_B2.y[m] - AMR_B2.Take_y > 0)
                    {
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = -B2_Vy;
                    }

                    if (abs(AMR_B2.x[m] - AMR_B2.Take_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Take_y) <= 10)
                    {
                        switch (AMR_B2.Take_y)
                        {
                        case 3807:Path_AMR_B2.append("s2|"); break;
                        case 1653:Path_AMR_B2.append("s4|"); break;
                        }
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = 0;
                        if (AMR_B2.Take_y == 3807)
                        {
                            Conection_1_State = 0;
                        }
                        if (AMR_B2.Take_y == 1653)
                        {
                            Conection_2_State = 0;
                        }
                        AMR_B2.State = 4;
                    }
                }

                //执行入库送料箱到料架任务
                if (AMR_B2.State == 4)
                {
                    //AMR_B2.Deliver_y == 2625的情况
                    if (AMR_B2.Deliver_y == 2625)
                    {
                        if (abs(AMR_B2.x[m] - AMR_B2.Take_x) <= 10 && AMR_B2.y[m] - AMR_B2.Deliver_y < 0)
                        {
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = B2_Vy;
                        }
                        if (abs(AMR_B2.x[m] - AMR_B2.Take_x) <= 10 && AMR_B2.y[m] - AMR_B2.Deliver_y > 0)
                        {
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = -B2_Vy;
                        }

                        if (abs(AMR_B2.x[m] - AMR_B2.Take_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Deliver_y) <= 10)
                        {
                            Path_AMR_B2.append("g2,");
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (AMR_B2.x[m] - AMR_B2.Deliver_x < 0 && abs(AMR_B2.y[m] - AMR_B2.Deliver_y) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - AMR_B2.Deliver_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Deliver_y) <= 10)
                        {
                            switch (AMR_B2.Deliver_x)
                            {
                            case 8948:Path_AMR_B2.append("l7|"); break;
                            case 9446:Path_AMR_B2.append("l8|"); break;
                            case 9925:Path_AMR_B2.append("l9|"); break;
                            case 12230:Path_AMR_B2.append("l10|"); break;
                            case 12768:Path_AMR_B2.append("l11|"); break;
                            case 13258:Path_AMR_B2.append("l12|"); break;
                            }
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                            AMR_B2.State = 8;
                        }
                    }

                    //AMR_B2.Deliver_y == 4990的情况
                    if (AMR_B2.Deliver_y == 4990)
                    {
                        if (abs(AMR_B2.x[m] - AMR_B2.Take_x) <= 10 && AMR_B2.y[m] - AMR_B2.y0 < 0)
                        {
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = B2_Vy;
                        }
                        if (abs(AMR_B2.x[m] - AMR_B2.Take_x) <= 10 && AMR_B2.y[m] - AMR_B2.y0 > 0)
                        {
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = -B2_Vy;
                        }

                        if (abs(AMR_B2.x[m] - AMR_B2.Take_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                        {
                            Path_AMR_B2.append("g2,");
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (AMR_B2.x[m] - 11096 < 0 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                        {
                            Path_AMR_B2.append("i2,");
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && AMR_B2.y[m] - AMR_B2.Deliver_y < 0)
                        {
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = B2_Vy;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Deliver_y) <= 10)
                        {
                            Path_AMR_B2.append("i1,");
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (AMR_B2.x[m] - AMR_B2.Deliver_x > 0 && abs(AMR_B2.y[m] - AMR_B2.Deliver_y) <= 10)
                        {
                            AMR_B2.Vx[m] = -B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }
                        if (AMR_B2.x[m] - AMR_B2.Deliver_x < 0 && abs(AMR_B2.y[m] - AMR_B2.Deliver_y) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - AMR_B2.Deliver_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Deliver_y) <= 10)
                        {
                            switch (AMR_B2.Deliver_x)
                            {
                            case 8948:Path_AMR_B2.append("l1|"); break;
                            case 9446:Path_AMR_B2.append("l2|"); break;
                            case 9925:Path_AMR_B2.append("l3|"); break;
                            case 12230:Path_AMR_B2.append("l4|"); break;
                            case 12768:Path_AMR_B2.append("l5|"); break;
                            case 13258:Path_AMR_B2.append("l6|"); break;
                            }
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                            AMR_B2.State = 8;
                        }
                    }
                }

                //执行移库任务
                    //执行移库去取料箱任务
                if (AMR_B2.State == 5)
                {
                    if (AMR_B2.Take_y == 2625)
                    {
                        if (AMR_B2.x[m] - AMR_B2.Take_x < 0 && abs(AMR_B2.y[m] - AMR_B2.Take_y) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - AMR_B2.Take_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Take_y) <= 10)
                        {
                            switch (AMR_B2.Take_x)
                            {
                            case 8948:Path_AMR_B2.append("l7|"); break;
                            case 9446:Path_AMR_B2.append("l8|"); break;
                            case 9925:Path_AMR_B2.append("l9|"); break;
                            case 12230:Path_AMR_B2.append("l10|"); break;
                            case 12768:Path_AMR_B2.append("l11|"); break;
                            case 13258:Path_AMR_B2.append("l12|"); break;
                            }
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                            AMR_B2.State = 6;
                        }
                    }

                    if (AMR_B2.Take_y == 4990)
                    {
                        if (AMR_B2.x[m] - 11096 < 0 && abs(AMR_B2.y[m] - 2625) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && abs(AMR_B2.y[m] - 2625) <= 10)
                        {
                            Path_AMR_B2.append("i2,");
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && AMR_B2.y[m] - 4990 < 0)
                        {
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = B2_Vy;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && abs(AMR_B2.y[m] - 4990) <= 10)
                        {
                            Path_AMR_B2.append("i1,");
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (AMR_B2.x[m] - AMR_B2.Take_x > 0 && abs(AMR_B2.y[m] - 4990) <= 10)
                        {
                            AMR_B2.Vx[m] = -B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }
                        if (AMR_B2.x[m] - AMR_B2.Take_x < 0 && abs(AMR_B2.y[m] - 4990) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - AMR_B2.Take_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Take_y) <= 10)
                        {
                            switch (AMR_B2.Take_x)
                            {
                            case 8948:Path_AMR_B2.append("l1|"); break;
                            case 9446:Path_AMR_B2.append("l2|"); break;
                            case 9925:Path_AMR_B2.append("l3|"); break;
                            case 12230:Path_AMR_B2.append("l4|"); break;
                            case 12768:Path_AMR_B2.append("l5|"); break;
                            case 13258:Path_AMR_B2.append("l6|"); break;
                            }
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                            AMR_B2.State = 6;
                        }
                    }
                }

                //执行移库送料箱到目标库位任务
                if (AMR_B2.State == 6)
                {
                    if (AMR_B2.Take_y == 2625 && AMR_B2.Deliver_y == 2625)
                    {
                        if (AMR_B2.x[m] - AMR_B2.Deliver_x > 0 && abs(AMR_B2.y[m] - 2625) <= 10)
                        {
                            AMR_B2.Vx[m] = -B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }
                        if (AMR_B2.x[m] - AMR_B2.Deliver_x < 0 && abs(AMR_B2.y[m] - 2625) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - AMR_B2.Deliver_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Deliver_y) <= 10)
                        {
                            switch (AMR_B2.Deliver_x)
                            {
                            case 8948:Path_AMR_B2.append("l7|"); break;
                            case 9446:Path_AMR_B2.append("l8|"); break;
                            case 9925:Path_AMR_B2.append("l9|"); break;
                            case 12230:Path_AMR_B2.append("l10|"); break;
                            case 12768:Path_AMR_B2.append("l11|"); break;
                            case 13258:Path_AMR_B2.append("l12|"); break;
                            }
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                            AMR_B2.State = 8;
                        }
                    }

                    if (AMR_B2.Take_y == 2625 && AMR_B2.Deliver_y == 4990)
                    {
                        if (AMR_B2.x[m] - 11096 > 0 && abs(AMR_B2.y[m] - 2625) <= 10)
                        {
                            AMR_B2.Vx[m] = -B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }
                        if (AMR_B2.x[m] - 11096 < 0 && abs(AMR_B2.y[m] - 2625) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && abs(AMR_B2.y[m] - 2625) <= 10)
                        {
                            Path_AMR_B2.append("i2,");
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && AMR_B2.y[m] - 4990 < 0)
                        {
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = B2_Vy;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && abs(AMR_B2.y[m] - 4990) <= 10)
                        {
                            Path_AMR_B2.append("i1,");
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (AMR_B2.x[m] - AMR_B2.Deliver_x > 0 && abs(AMR_B2.y[m] - 4990) <= 10)
                        {
                            AMR_B2.Vx[m] = -B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }
                        if (AMR_B2.x[m] - AMR_B2.Deliver_x < 0 && abs(AMR_B2.y[m] - 4990) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - AMR_B2.Deliver_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Deliver_y) <= 10)
                        {
                            switch (AMR_B2.Deliver_x)
                            {
                            case 8948:Path_AMR_B2.append("l1|"); break;
                            case 9446:Path_AMR_B2.append("l2|"); break;
                            case 9925:Path_AMR_B2.append("l3|"); break;
                            case 12230:Path_AMR_B2.append("l4|"); break;
                            case 12768:Path_AMR_B2.append("l5|"); break;
                            case 13258:Path_AMR_B2.append("l6|"); break;
                            }
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                            AMR_B2.State = 8;
                        }
                    }

                    if (AMR_B2.Take_y == 4990 && AMR_B2.Deliver_y == 2625)
                    {
                        if (AMR_B2.x[m] - 11096 > 0 && abs(AMR_B2.y[m] - 4990) <= 10)
                        {
                            AMR_B2.Vx[m] = -B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }
                        if (AMR_B2.x[m] - 11096 < 0 && abs(AMR_B2.y[m] - 4990) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && abs(AMR_B2.y[m] - 4990) <= 10)
                        {
                            Path_AMR_B2.append("i1,");
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && AMR_B2.y[m] - 2625 > 0)
                        {
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = -B2_Vy;
                        }

                        if (abs(AMR_B2.x[m] - 11096) <= 10 && abs(AMR_B2.y[m] - 2625) <= 10)
                        {
                            Path_AMR_B2.append("i2,");
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (AMR_B2.x[m] - AMR_B2.Deliver_x > 0 && abs(AMR_B2.y[m] - 2625) <= 10)
                        {
                            AMR_B2.Vx[m] = -B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }
                        if (AMR_B2.x[m] - AMR_B2.Deliver_x < 0 && abs(AMR_B2.y[m] - 2625) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - AMR_B2.Deliver_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Deliver_y) <= 10)
                        {
                            switch (AMR_B2.Deliver_x)
                            {
                            case 8948:Path_AMR_B2.append("l7|"); break;
                            case 9446:Path_AMR_B2.append("l8|"); break;
                            case 9925:Path_AMR_B2.append("l9|"); break;
                            case 12230:Path_AMR_B2.append("l10|"); break;
                            case 12768:Path_AMR_B2.append("l11|"); break;
                            case 13258:Path_AMR_B2.append("l12|"); break;
                            }
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                            AMR_B2.State = 8;
                        }
                    }

                    if (AMR_B2.Take_y == 4990 && AMR_B2.Deliver_y == 4990)
                    {
                        if (AMR_B2.x[m] - AMR_B2.Deliver_x > 0 && abs(AMR_B2.y[m] - 4990) <= 10)
                        {
                            AMR_B2.Vx[m] = -B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }
                        if (AMR_B2.x[m] - AMR_B2.Deliver_x < 0 && abs(AMR_B2.y[m] - 4990) <= 10)
                        {
                            AMR_B2.Vx[m] = B2_Vx;
                            AMR_B2.Vy[m] = 0;
                        }

                        if (abs(AMR_B2.x[m] - AMR_B2.Deliver_x) <= 10 && abs(AMR_B2.y[m] - AMR_B2.Deliver_y) <= 10)
                        {
                            switch (AMR_B2.Deliver_x)
                            {
                            case 8948:Path_AMR_B2.append("l1|"); break;
                            case 9446:Path_AMR_B2.append("l2|"); break;
                            case 9925:Path_AMR_B2.append("l3|"); break;
                            case 12230:Path_AMR_B2.append("l4|"); break;
                            case 12768:Path_AMR_B2.append("l5|"); break;
                            case 13258:Path_AMR_B2.append("l6|"); break;
                            }
                            AMR_B2.Vx[m] = 0;
                            AMR_B2.Vy[m] = 0;
                            AMR_B2.State = 8;
                        }
                    }
                }

                //返回待命点
                if (AMR_B2.State == 8)
                {
                    if (AMR_B2.x[m] - 11096 < 0 && abs(AMR_B2.y[m] - 4990) <= 10)
                    {
                        AMR_B2.Vx[m] = B2_Vx;
                        AMR_B2.Vy[m] = 0;
                    }
                    if (AMR_B2.x[m] - 11096 > 0 && abs(AMR_B2.y[m] - 4990) <= 10)
                    {
                        AMR_B2.Vx[m] = -B2_Vx;
                        AMR_B2.Vy[m] = 0;
                    }

                    if (abs(AMR_B2.x[m] - 11096) <= 10 && abs(AMR_B2.y[m] - 4990) <= 10)
                    {
                        Path_AMR_B2.append("i1,");
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = 0;
                    }

                    if (abs(AMR_B2.x[m] - 11096) <= 10 && AMR_B2.y[m] - AMR_B2.y0 > 0)
                    {
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = -B2_Vy;
                    }

                    if (abs(AMR_B2.x[m] - 11096) <= 10 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                    {
                        Path_AMR_B2.append("i2,");
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = 0;
                    }

                    if (AMR_B2.x[m] - AMR_B2.x0 > 0 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                    {
                        AMR_B2.Vx[m] = -B2_Vx;
                        AMR_B2.Vy[m] = 0;
                    }

                    if (abs(AMR_B2.x[m] - 7785) <= 10 && AMR_B2.y[m] - AMR_B2.y0 > 0)
                    {
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = -B2_Vy;
                    }
                    if (abs(AMR_B2.x[m] - 7785) <= 10 && AMR_B2.y[m] - AMR_B2.y0 < 0)
                    {
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = B2_Vy;
                    }

                    if (abs(AMR_B2.x[m] - 7785) <= 10 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                    {
                        Path_AMR_B2.append("g2,");
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = 0;
                    }

                    if (AMR_B2.x[m] - AMR_B2.x0 < 0 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                    {
                        AMR_B2.Vx[m] = B2_Vx;
                        AMR_B2.Vy[m] = 0;
                    }

                    if (abs(AMR_B2.x[m] - AMR_B2.x0) <= 15 && abs(AMR_B2.y[m] - AMR_B2.y0) <= 10)
                    {
                        Path_AMR_B2.append("l7");
                        AMR_B2.Vx[m] = 0;
                        AMR_B2.Vy[m] = 0;
                        AMR_B2.State = 0;
                        AMR_B2.Task_State = 0;
                        AMR_B2.Outbound_Task = 0;
                        AMR_B2.Inbound_Task = 0;
                        AMR_B2.Shift_Warehouse_Task = 0;
                    }
                }

            }
            if (AMR_B2.State == 0)
            {
                AMR_B2.Vx[m] = 0;
                AMR_B2.Vy[m] = 0;
            }

            //AMR_B1位置计算
            AMR_B1.x[m + 1] = AMR_B1.x[m] + AMR_B1.Vx[m] * delta_t;
            AMR_B1.y[m + 1] = AMR_B1.y[m] + AMR_B1.Vy[m] * delta_t;

            //AMR_B2位置计算
            AMR_B2.x[m + 1] = AMR_B2.x[m] + AMR_B2.Vx[m] * delta_t;
            AMR_B2.y[m + 1] = AMR_B2.y[m] + AMR_B2.Vy[m] * delta_t;
            t[m + 1] = t[m] + delta_t;

        }
        float time =(double)mstimer.nsecsElapsed()/(double)1000000;
        return time;



}

    double D_Dispatch_function(int sec)
    {
           // D_dispatch(1, 6130, 1653, 870, 6170);
        QElapsedTimer mstimer;
        mstimer.start();


                Path_AMR_D1 = "";
                Path_AMR_D2 = "";
                qDebug()<<"d1状态："<<D1_task_percent;
                qDebug()<<"d2状态："<<D2_task_percent;
                AMR_D1.Task_State=D1_task_percent;
                AMR_D2.Task_State=D2_task_percent;


                    AMR_D1.x0 = 2847;
                    AMR_D1.y0 = 2625;
                    AMR_D1.x[0] = AMR_D1.x0;
                    AMR_D1.y[0] = AMR_D1.y0;


                    AMR_D2.x0 = 6130;
                    AMR_D2.y0 = 4990;
                    AMR_D2.x[0] = AMR_D2.x0;
                    AMR_D2.y[0] = AMR_D2.y0;


                    if(sec == 1)
                    {
                       Delay_MSec(1);
                    }

                    if (D_Task == 1)
                    {
                        if (AMR_D1.Task_State == 0 && AMR_D2.Task_State == 0)
                        {
                            if (D_Deliver_x == 870)
                            {
                                AMR_D1.Outbound_Date = 1;
                            }

                            if (D_Deliver_x == 8735)
                            {
                                AMR_D2.Outbound_Date = 1;
                            }
                        }

                        if (AMR_D1.Task_State == 0 && AMR_D2.Task_State == 1)
                        {
                            AMR_D1.Outbound_Date = 1;
                        }

                        if (AMR_D1.Task_State == 1 && AMR_D2.Task_State == 0)
                        {
                            AMR_D2.Outbound_Date = 1;
                        }

                        if (AMR_D1.Outbound_Date == 1 || AMR_D2.Outbound_Date == 1)
                        {
                            D_Task = 0;
                        }
                    }

                    //AMR_D入库任务判断
                    if (D_Task == 2)
                    {
                        if (AMR_D1.Task_State == 0 && AMR_D2.Task_State == 0)
                        {
                            if (D_Take_x == 870)
                            {
                                AMR_D1.Inbound_Date = 1;
                            }

                            if (D_Take_x == 8735)
                            {
                                AMR_D2.Inbound_Date = 1;
                            }
                        }

                        if (AMR_D1.Task_State == 0 && AMR_D2.Task_State == 1)
                        {
                            AMR_D1.Inbound_Date = 1;
                        }

                        if (AMR_D1.Task_State == 1 && AMR_D2.Task_State == 0)
                        {
                            AMR_D2.Inbound_Date = 1;
                        }

                        if (AMR_D1.Inbound_Date == 1 || AMR_D2.Inbound_Date == 1)
                        {
                            D_Task = 0;
                        }
                    }

                    //出库数据更新
                    if (AMR_D1.Outbound_Date == 1 && AMR_D1.Task_State == 0)
                    {
                        AMR_D1.Outbound_Task = 1;
                        AMR_D1.State = 1;
                        AMR_D1.Take_x = D_Take_x;
                        AMR_D1.Take_y = D_Take_y;
                        AMR_D1.Deliver_x = D_Deliver_x;
                        AMR_D1.Deliver_y = D_Deliver_y;
                        AMR_D1.Outbound_Date = 0;
                    }
                    if (AMR_D2.Outbound_Date == 1 && AMR_D2.Task_State == 0)
                    {
                        AMR_D2.Outbound_Task = 1;
                        AMR_D2.State = 1;
                        AMR_D2.Take_x = D_Take_x;
                        AMR_D2.Take_y = D_Take_y;
                        AMR_D2.Deliver_x = D_Deliver_x;
                        AMR_D2.Deliver_y = D_Deliver_y;
                        AMR_D2.Outbound_Date = 0;
                    }

                    //入库数据更新
                    if (AMR_D1.Inbound_Date == 1 && AMR_D1.Task_State == 0)
                    {
                        AMR_D1.Inbound_Task = 1;
                        AMR_D1.State = 3;
                        AMR_D1.Take_x = D_Take_x;
                        AMR_D1.Take_y = D_Take_y;
                        AMR_D1.Deliver_x = D_Deliver_x;
                        AMR_D1.Deliver_y = D_Deliver_y;
                        AMR_D1.Destination_x = Deliver_x;
                        AMR_D1.Destination_y = Deliver_y;
                        AMR_D1.Inbound_Date = 0;
                    }
                    if (AMR_D2.Inbound_Date == 1 && AMR_D2.Task_State == 0)
                    {
                        AMR_D2.Inbound_Task = 1;
                        AMR_D2.State = 3;
                        AMR_D2.Take_x = D_Take_x;
                        AMR_D2.Take_y = D_Take_y;
                        AMR_D2.Deliver_x = D_Deliver_x;
                        AMR_D2.Deliver_y = D_Deliver_y;
                        AMR_D2.Destination_x = Deliver_x;
                        AMR_D2.Destination_y = Deliver_y;
                        AMR_D2.Inbound_Date = 0;
                    }


                    for (int m = 0; m < 1999; m++)
                    {
                        if (AMR_D1.Outbound_Task == 1 || AMR_D1.Inbound_Task == 1)
                        {
                            AMR_D1.Task_State = 1;

                            //执行出库任务
                                //执行出库到出入库接驳点取料箱任务
                            if (AMR_D1.State == 1)
                            {
                                if (AMR_D1.x[m] - AMR_D1.Take_x < 0 && abs(AMR_D1.y[m] - 2625) <= 10)
                                {
                                    AMR_D1.Vx[m] = D1_Vx;
                                    AMR_D1.Vy[m] = 0;
                                }

                                if (abs(AMR_D1.x[m] - 6130) <= 10 && abs(AMR_D1.y[m] - 2625) <= 10)
                                {
                                    Path_AMR_D1.append("d2,");
                                }

                                if (abs(AMR_D1.x[m] - 6130) <= 10 && AMR_D1.y[m] - AMR_D1.Take_y < 0)
                                {
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = D1_Vy;
                                }
                                if (abs(AMR_D1.x[m] - 6130) <= 10 && AMR_D1.y[m] - AMR_D1.Take_y > 0)
                                {
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = -D1_Vy;
                                }

                                if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && abs(AMR_D1.y[m] - AMR_D1.Take_y) <= 10)
                                {
                                    switch (AMR_D1.Take_y)
                                    {
                                    case 3807:Path_AMR_D1.append("s1|"); break;
                                    case 1653:Path_AMR_D1.append("s3|"); break;
                                    }
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = 0;
                                    if (AMR_D1.Take_y == 3807)
                                    {
                                        Conection_1_State = 0;
                                    }
                                    if (AMR_D1.Take_y == 2625)
                                    {
                                        Conection_2_State = 0;
                                    }
                                    AMR_D1.State = 2;
                                }
                            }

                            //执行出库送料箱到指定机台任务
                            if (AMR_D1.State == 2)
                            {
                                //出库送到（870,6170)位置
                                if (AMR_D1.Deliver_x == 870 && AMR_D1.Deliver_y == 6170)
                                {
                                    if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && AMR_D1.y[m] - 2625 > 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = -D1_Vy;
                                    }
                                    if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && AMR_D1.y[m] - 2625 < 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && abs(AMR_D1.y[m] - 2625) <= 10)
                                    {
                                        Path_AMR_D1.append("d2,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (AMR_D1.x[m] - AMR_D1.x0 > 0 && abs(AMR_D1.y[m] - 2625) <= 10)
                                    {
                                        AMR_D1.Vx[m] = -D1_Vx;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.x0) <= 10 && abs(AMR_D1.y[m] - 2625) <= 10)
                                    {
                                        Path_AMR_D1.append("b2,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.x0) <= 10 && AMR_D1.y[m] - 4990 < 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.x0) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D1.append("b1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (AMR_D1.x[m] - AMR_D1.Deliver_x > 0 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        AMR_D1.Vx[m] = -D1_Vx;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Deliver_x) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D1.append("a1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Deliver_x) <= 10 && AMR_D1.y[m] - AMR_D1.Deliver_y < 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Deliver_x) <= 10 && abs(AMR_D1.y[m] - AMR_D1.Deliver_y) <= 10)
                                    {
                                        Path_AMR_D1.append("t1|");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                        AMR_D1.State = 6;
                                    }
                                }

                                //出库送到（8735,6170)位置
                                if (AMR_D1.Deliver_x == 8735 && AMR_D1.Deliver_y == 6170)
                                {
                                    if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && AMR_D1.y[m] - 2625 > 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = -D1_Vy;
                                    }
                                    if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && AMR_D1.y[m] - 2625 < 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && abs(AMR_D1.y[m] - 2625) <= 10)
                                    {
                                        Path_AMR_D1.append("d2,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (AMR_D1.x[m] - AMR_D1.x0 > 0 && abs(AMR_D1.y[m] - 2625) <= 10)
                                    {
                                        AMR_D1.Vx[m] = -D1_Vx;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.x0) <= 10 && abs(AMR_D1.y[m] - 2625) <= 10)
                                    {
                                        Path_AMR_D1.append("b2,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.x0) <= 10 && AMR_D1.y[m] - 4990 < 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.x0) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D1.append("b1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (AMR_D1.x[m] - 6785 < 0 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        AMR_D1.Vx[m] = D1_Vx;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - 6785) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D1.append("e2,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - 6785) <= 10 && AMR_D1.y[m] - 6815 < 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - 6785) <= 10 && abs(AMR_D1.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D1.append("e1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (AMR_D1.x[m] - AMR_D1.Deliver_x < 0 && abs(AMR_D1.y[m] - 6815) <= 10)
                                    {
                                        AMR_D1.Vx[m] = D1_Vx;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                  if (abs(AMR_D1.x[m] - 7785) <= 10 && abs(AMR_D1.y[m] - 6815) <= 10)
                                  {
                                        Path_AMR_D1.append("f1,");
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Deliver_x) <= 10 && abs(AMR_D1.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D1.append("h1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Deliver_x) <= 10 && AMR_D1.y[m] - AMR_D1.Deliver_y > 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = -D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Deliver_x) <= 10 && abs(AMR_D1.y[m] - AMR_D1.Deliver_y) <= 10)
                                    {
                                        Path_AMR_D1.append("t2|");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                        AMR_D1.State = 6;
                                    }
                                }
                            }

                            //执行入库任务
                                //执行入库到指定机台取料箱任务
                            if (AMR_D1.State == 3)
                            {
                                if (AMR_D1.Take_x == 870 && AMR_D1.Take_y == 6170)
                                {
                                    if (abs(AMR_D1.x[m] - AMR_D1.x0) <= 10 && AMR_D1.y[m] - 4990 < 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.x0) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D1.append("b1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (AMR_D1.x[m] - AMR_D1.Take_x > 0 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        AMR_D1.Vx[m] = -D1_Vx;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D1.append("a1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && AMR_D1.y[m] - AMR_D1.Take_y < 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && abs(AMR_D1.y[m] - AMR_D1.Take_y) <= 10)
                                    {
                                        Path_AMR_D1.append("t1|");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                        AMR_D1.State = 4;
                                    }
                                }

                                if (AMR_D1.Take_x == 8735 && AMR_D1.Take_y == 6170)
                                {
                                    if (abs(AMR_D1.x[m] - AMR_D1.x0) <= 10 && AMR_D1.y[m] - 4990 < 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.x0) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D1.append("b1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (AMR_D1.x[m] - 6785 < 0 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        AMR_D1.Vx[m] = D1_Vx;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - 6785) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D1.append("e2,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - 6785) <= 10 && AMR_D1.y[m] - 6815 < 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - 6785) <= 10 && abs(AMR_D1.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D1.append("e1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (AMR_D1.x[m] - AMR_D1.Take_x < 0 && abs(AMR_D1.y[m] - 6815) <= 10)
                                    {
                                        AMR_D1.Vx[m] = D1_Vx;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                if (abs(AMR_D1.x[m] - 7785) <= 10 && abs(AMR_D1.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D1.append("f1,");
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && abs(AMR_D1.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D1.append("h1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && AMR_D1.y[m] - AMR_D1.Take_y > 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = -D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && abs(AMR_D1.y[m] - AMR_D1.Take_y) <= 10)
                                    {
                                        Path_AMR_D1.append("t2|");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                        AMR_D1.State = 4;
                                    }
                                }
                            }

                            //执行入库送料箱到接驳点任务
                            if (AMR_D1.State == 4)
                            {
                                if (AMR_D1.Take_x == 870 && AMR_D1.Take_y == 6170)
                                {
                                    if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && AMR_D1.y[m] - 4990 > 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = -D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D1.append("a1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (AMR_D1.x[m] - AMR_D1.x0 < 0 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        AMR_D1.Vx[m] = D1_Vx;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.x0) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D1.append("b1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.x0) <= 10 && AMR_D1.y[m] - 2625 > 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = -D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.x0) <= 10 && abs(AMR_D1.y[m] - 2625) <= 10)
                                    {
                                        Path_AMR_D1.append("b2,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (AMR_D1.x[m] - AMR_D1.Deliver_x < 0 && abs(AMR_D1.y[m] - 2625) <= 10)
                                    {
                                        AMR_D1.Vx[m] = D1_Vx;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Deliver_x) <= 10 && abs(AMR_D1.y[m] - 2625) <= 10)
                                    {
                                        Path_AMR_D1.append("d2,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Deliver_x) <= 10 && AMR_D1.y[m] - AMR_D1.Deliver_y < 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = D1_Vy;
                                    }
                                    if (abs(AMR_D1.x[m] - AMR_D1.Deliver_x) <= 10 && AMR_D1.y[m] - AMR_D1.Deliver_y > 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = -D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Deliver_x) <= 10 && abs(AMR_D1.y[m] - AMR_D1.Deliver_y) <= 10)
                                    {
                                        switch (AMR_D1.Deliver_y)
                                        {
                                        case 3807:Path_AMR_D1.append("s1|"); break;
                                        case 1653:Path_AMR_D1.append("s3|"); break;
                                        }
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                        AMR_D1.State = 6;
                                    }
                                }

                                if (AMR_D1.Take_x == 8735 && AMR_D1.Take_y == 6170)
                                {
                                    if (abs(AMR_D1.x[m] - 8735) <= 10 && AMR_D1.y[m] - 6815 < 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - 8735) <= 10 && abs(AMR_D1.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D1.append("h1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - 7785) <= 10 && abs(AMR_D1.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D1.append("f1,");
                                    }

                                    if (AMR_D1.x[m] - 6785 > 0 && abs(AMR_D1.y[m] - 6815) <= 10)
                                    {
                                        AMR_D1.Vx[m] = -D1_Vx;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - 6785) <= 10 && abs(AMR_D1.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D1.append("e1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - 6785) <= 10 && AMR_D1.y[m] - 4990 > 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = -D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - 6785) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D1.append("e2,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (AMR_D1.x[m] - 2847 > 0 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        AMR_D1.Vx[m] = -D1_Vx;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - 2847) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D1.append("b1,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - 2847) <= 10 && AMR_D1.y[m] - 2625 > 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = -D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - 2847) <= 10 && abs(AMR_D1.y[m] - 2625) <= 10)
                                    {
                                        Path_AMR_D1.append("b2,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (AMR_D1.x[m] - AMR_D1.Deliver_x < 0 && abs(AMR_D1.y[m] - 2625) <= 10)
                                    {
                                        AMR_D1.Vx[m] = D1_Vx;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Deliver_x) <= 10 && abs(AMR_D1.y[m] - 2625) <= 10)
                                    {
                                        Path_AMR_D1.append("d2,");
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Deliver_x) <= 10 && AMR_D1.y[m] - AMR_D1.Deliver_y < 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = D1_Vy;
                                    }
                                    if (abs(AMR_D1.x[m] - AMR_D1.Deliver_x) <= 10 && AMR_D1.y[m]<4800 && AMR_D1.y[m] - AMR_D1.Deliver_y > 0)
                                    {
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = -D1_Vy;
                                    }

                                    if (abs(AMR_D1.x[m] - AMR_D1.Deliver_x) <= 10 && abs(AMR_D1.y[m] - AMR_D1.Deliver_y) <= 10)
                                    {
                                        switch (AMR_D1.Deliver_y)
                                        {
                                        case 3807:Path_AMR_D1.append("s1|"); break;
                                        case 1653:Path_AMR_D1.append("s3|"); break;
                                        }
                                        AMR_D1.Vx[m] = 0;
                                        AMR_D1.Vy[m] = 0;
                                        AMR_D1.State = 6;
                                    }
                                }
                            }

                            //返回初始点
                            if (AMR_D1.State == 6)
                            {
                                //(870,6170)
                                if (abs(AMR_D1.x[m] - 870) <= 10 && AMR_D1.y[m] - 4990 > 0)
                                {
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = -D1_Vy;
                                }

                                if (abs(AMR_D1.x[m] - 870) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                {
                                    Path_AMR_D1.append("a1,");
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = 0;
                                }

                                if (AMR_D1.x[m] - 2847 < 0 && abs(AMR_D1.y[m] - 4990) <= 10)
                                {
                                    AMR_D1.Vx[m] = D1_Vx;
                                    AMR_D1.Vy[m] = 0;
                                }

                                if (abs(AMR_D1.x[m] - 2847) <= 10 && AMR_D1.y[m] - 2625 > 0)
                                {
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = -D1_Vy;
                                }

                                //(8735, 6170）位置
                                if (abs(AMR_D1.x[m] - 8735) <= 10 && AMR_D1.y[m] - 6815 < 0)
                                {
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = D1_Vy;
                                }

                                if (abs(AMR_D1.x[m] - 8735) <= 10 && abs(AMR_D1.y[m] - 6815) <= 10)
                                {
                                    Path_AMR_D1.append("h1,");
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = 0;
                                }

                                if (AMR_D1.x[m] - 6785 > 0 && abs(AMR_D1.y[m] - 6815) <= 10)
                                {
                                    AMR_D1.Vx[m] = -D1_Vx;
                                    AMR_D1.Vy[m] = 0;
                                }

                                if (abs(AMR_D1.x[m] - 7785) <= 10 && abs(AMR_D1.y[m] - 6815) <= 10)
                                {
                                    Path_AMR_D1.append("f1,");
                                }

                                if (abs(AMR_D1.x[m] - 6785) <= 10 && abs(AMR_D1.y[m] - 6815) <= 10)
                                {
                                    Path_AMR_D1.append("e1,");
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = 0;
                                }

                                if (abs(AMR_D1.x[m] - 6785) <= 10 && AMR_D1.y[m] - 4990 > 0)
                                {
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = -D1_Vy;
                                }

                                if (abs(AMR_D1.x[m] - 6785) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                {
                                    Path_AMR_D1.append("e2,");
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = 0;
                                }

                                if (AMR_D1.x[m] - 2847 > 0 && abs(AMR_D1.y[m] - 4990) <= 10)
                                {
                                    AMR_D1.Vx[m] = -D1_Vx;
                                    AMR_D1.Vy[m] = 0;
                                }

                                if (abs(AMR_D1.x[m] - 2847) <= 10 && abs(AMR_D1.y[m] - 4990) <= 10)
                                {
                                    Path_AMR_D1.append("b1,");
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = 0;
                                }

                                if (abs(AMR_D1.x[m] - 2847) <= 10 && AMR_D1.y[m] - 2625 > 0)
                                {
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = -D1_Vy;
                                }

                                //出入库接驳点位置
                                if (abs(AMR_D1.x[m] - 6130) <= 10 && AMR_D1.y[m]<4800 && AMR_D1.y[m] >2625)
                                {
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = -D1_Vy;
                                }
                                if (abs(AMR_D1.x[m] - 6130) <= 10 && AMR_D1.y[m] - 2625 < 0)
                                {
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = D1_Vy;
                                }

                                if (abs(AMR_D1.x[m] - 6130) <= 10 && abs(AMR_D1.y[m] - 2625) <= 10)
                                {
                                    Path_AMR_D1.append("d2,");
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = 0;
                                }

                                if (AMR_D1.x[m] - 2847 > 0 && abs(AMR_D1.y[m] - 2625) <= 10)
                                {
                                    AMR_D1.Vx[m] = -D1_Vx;
                                    AMR_D1.Vy[m] = 0;
                                }


                                if (abs(AMR_D1.x[m] - AMR_D1.x0) <= 10 && abs(AMR_D1.y[m] - AMR_D1.y0) <= 10)
                                {
                                    Path_AMR_D1.append("b2");
                                    AMR_D1.Vx[m] = 0;
                                    AMR_D1.Vy[m] = 0;
                                    AMR_D1.State = 0;
                                    AMR_D1.Task_State = 0;
                                    AMR_D1.Outbound_Task = 0;
                                    AMR_D1.Inbound_Task = 0;
                                }
                            }
                        }
                        if (AMR_D1.State == 0)
                        {
                            AMR_D1.Vx[m] = 0;
                            AMR_D1.Vy[m] = 0;
                        }

                        if (AMR_D2.Outbound_Task == 1 || AMR_D2.Inbound_Task == 1)
                        {
                            AMR_D2.Task_State = 1;
                            //执行出库任务
                                //执行出库到出入库接驳点取料箱任务
                            if (AMR_D2.State == 1)
                            {
                                if (abs(AMR_D2.x[m] - AMR_D2.Take_x) <= 10 && AMR_D2.y[m] - AMR_D2.Take_y > 0)
                                {
                                    AMR_D2.Vx[m] = 0;
                                    AMR_D2.Vy[m] = -D2_Vy;
                                }

                                if (abs(AMR_D2.x[m] - AMR_D2.Take_x) <= 10 && abs(AMR_D2.y[m] - AMR_D2.Take_y) <= 10)
                                {
                                    switch (AMR_D2.Take_y)
                                    {
                                    case 3807:Path_AMR_D2.append("s1|"); break;
                                    case 1653:Path_AMR_D2.append("s3|"); break;
                                    }
                                    AMR_D2.Vx[m] = 0;
                                    AMR_D2.Vy[m] = 0;
                                    AMR_D2.State = 2;
                                }
                            }

                            //执行出库送物料到指定机台任务
                            if (AMR_D2.State == 2)
                            {
                                if (AMR_D2.Deliver_x == 870 && AMR_D2.Deliver_y == 6170)
                                {
                                    if (abs(AMR_D2.x[m] - AMR_D2.Take_x) <= 10 && AMR_D2.y[m] - 4990 < 0)
                                    {
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = D2_Vy;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Take_x) <= 10 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D2.append("d1,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (AMR_D2.x[m] - 870 > 0 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        AMR_D2.Vx[m] = -D2_Vx;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - 870) <= 10 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D2.append("a1,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Deliver_x) <= 10 && AMR_D2.y[m] - AMR_D2.Deliver_y < 0)
                                    {
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = D2_Vy;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Deliver_x) <= 10 && abs(AMR_D2.y[m] - AMR_D2.Deliver_y) <= 10)
                                    {
                                        Path_AMR_D2.append("t1|");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                        AMR_D2.State = 6;
                                    }
                                }

                                if (AMR_D2.Deliver_x == 8735 && AMR_D2.Deliver_y == 6170)
                                {
                                    if (abs(AMR_D2.x[m] - AMR_D2.Take_x) <= 10 && AMR_D2.y[m] - 4990 < 0)
                                    {
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = D2_Vy;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Take_x) <= 10 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D2.append("d1,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (AMR_D2.x[m] - 6785 < 0 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        AMR_D2.Vx[m] = D2_Vx;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - 6785) <= 10 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D2.append("e2,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - 6785) <= 10 && AMR_D2.y[m] - 6815 < 0)
                                    {
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = D2_Vy;
                                    }

                                    if (abs(AMR_D2.x[m] - 6785) <= 10 && abs(AMR_D2.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D2.append("e1,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (AMR_D2.x[m] - 8735 < 0 && abs(AMR_D2.y[m] - 6815) <= 10)
                                    {
                                        AMR_D2.Vx[m] = D2_Vx;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - 7785) <= 10 && abs(AMR_D2.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D2.append("f1,");
                                        //AMR_D2.Vx[m] = 0;
                                        //AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - 8735) <= 10 && abs(AMR_D2.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D2.append("h1,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - 8735) <= 10 && AMR_D2.y[m] - 6170 > 0)
                                    {
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = -D2_Vy;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Deliver_x) <= 10 && abs(AMR_D2.y[m] - AMR_D2.Deliver_y) <= 10)
                                    {
                                        Path_AMR_D2.append("t2|");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                        AMR_D2.State = 6;
                                    }
                                }
                            }

                            //执行入库任务
                                //入库到指定机台取料箱任务
                            if (AMR_D2.State == 3)
                            {
                                if (AMR_D2.Take_x == 870 && AMR_D2.Take_y == 6170)
                                {
                                    if (AMR_D2.x[m] - AMR_D2.Take_x > 0 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        AMR_D2.Vx[m] = -D2_Vx;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Take_x) <= 10 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D2.append("a1,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Take_x) <= 10 && AMR_D2.y[m] - AMR_D2.Take_y < 0)
                                    {
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = D2_Vy;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Take_x) <= 10 && abs(AMR_D2.y[m] - AMR_D2.Take_y) <= 10)
                                    {
                                        Path_AMR_D2.append("t1|");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                        AMR_D2.State = 4;
                                    }
                                }

                                if (AMR_D2.Take_x == 8735 && AMR_D2.Take_y == 6170)
                                {
                                    if (AMR_D2.x[m] - 6785 < 0 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        AMR_D2.Vx[m] = D2_Vx;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - 6785) <= 10 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D2.append("e2,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - 6785) <= 10 && AMR_D2.y[m] - 6815 < 0)
                                    {
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = D2_Vy;
                                    }

                                    if (abs(AMR_D2.x[m] - 6785) <= 10 && abs(AMR_D2.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D2.append("e1,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (AMR_D2.x[m] - 8735 < 0 && abs(AMR_D2.y[m] - 6815) <= 10)
                                    {
                                        AMR_D2.Vx[m] = D2_Vx;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - 7785) <= 10 && abs(AMR_D2.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D2.append("f1,");
                                    }

                                    if (abs(AMR_D2.x[m] - 8735) <= 10 && abs(AMR_D2.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D2.append("h1,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - 8735) <= 10 && AMR_D2.y[m] - 6170 > 0)
                                    {
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = -D2_Vy;
                                    }

                                    if (abs(AMR_D2.x[m] - 8735) <= 10 && abs(AMR_D2.y[m] - 6170) <= 10)
                                    {
                                        Path_AMR_D2.append("t2|");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                        AMR_D2.State = 4;
                                    }
                                }
                            }

                            //执行入库送料箱到出入库接驳点任务
                            if (AMR_D2.State == 4)
                            {
                                if (AMR_D2.Take_x == 870 && AMR_D2.Take_y == 6170)
                                {
                                    if (abs(AMR_D2.x[m] - AMR_D2.Take_x) <= 10 && AMR_D2.y[m] - 4990 > 0)
                                    {
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = -D2_Vy;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Take_x) <= 10 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D2.append("a1,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (AMR_D2.x[m] - AMR_D2.Deliver_x < 0 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        AMR_D2.Vx[m] = D2_Vx;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Deliver_x) <= 10 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D2.append("d1,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Deliver_x) <= 10 && AMR_D2.y[m] - AMR_D2.Deliver_y > 0)
                                    {
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = -D2_Vy;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Deliver_x) <= 10 && abs(AMR_D2.y[m] - AMR_D2.Deliver_y) <= 10)
                                    {
                                        switch (AMR_D2.Deliver_y)
                                        {
                                        case 3807:Path_AMR_D2.append("s1|"); break;
                                        case 1653:Path_AMR_D2.append("s3|"); break;
                                        }
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                        AMR_D2.State = 6;
                                    }
                                }

                                if (AMR_D2.Take_x == 8735 && AMR_D2.Take_y == 6170)
                                {
                                    if (abs(AMR_D2.x[m] - 8735) <= 10 && AMR_D2.y[m] - 6815 < 0)
                                    {
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = D2_Vy;
                                    }

                                    if (abs(AMR_D2.x[m] - 8735) <= 10 && abs(AMR_D2.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D2.append("h1,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (AMR_D2.x[m] - 6785 > 0 && abs(AMR_D2.y[m] - 6815) <= 10)
                                    {
                                        AMR_D2.Vx[m] = -D2_Vx;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - 7785) <= 10 && abs(AMR_D2.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D2.append("f1,");
                                    }

                                    if (abs(AMR_D2.x[m] - 6785) <= 10 && abs(AMR_D2.y[m] - 6815) <= 10)
                                    {
                                        Path_AMR_D2.append("e1,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - 6785) <= 10 && AMR_D2.y[m] - 4990 > 0)
                                    {
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = -D2_Vy;
                                    }

                                    if (abs(AMR_D2.x[m] - 6785) <= 10 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D2.append("e2,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (AMR_D2.x[m] - AMR_D2.Deliver_x > 0 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        AMR_D2.Vx[m] = -D2_Vx;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Deliver_x) <= 10 && abs(AMR_D2.y[m] - 4990) <= 10)
                                    {
                                        Path_AMR_D2.append("d1,");
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Deliver_x) <= 10 && AMR_D2.y[m] - AMR_D2.Deliver_y > 0)
                                    {
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = -D2_Vy;
                                    }

                                    if (abs(AMR_D2.x[m] - AMR_D2.Deliver_x) <= 10 && abs(AMR_D2.y[m] - AMR_D2.Deliver_y) <= 10)
                                    {
                                        switch (AMR_D2.Deliver_y)
                                        {
                                        case 3807:Path_AMR_D2.append("s1|"); break;
                                        case 1653:Path_AMR_D2.append("s3|"); break;
                                        }
                                        AMR_D2.Vx[m] = 0;
                                        AMR_D2.Vy[m] = 0;
                                        AMR_D2.State = 6;
                                    }
                                }
                            }

                            //返回初始点
                            if (AMR_D2.State == 6)
                            {
                                //(8735, 6170）位置回待命点
                                if (abs(AMR_D2.x[m] - 8735) <= 10 && AMR_D2.y[m] - 6815 < 0)
                                {
                                    AMR_D2.Vx[m] = 0;
                                    AMR_D2.Vy[m] = D2_Vy;
                                }

                                if (abs(AMR_D2.x[m] - 8735) <= 10 && abs(AMR_D2.y[m] - 6815) <= 10)
                                {
                                    Path_AMR_D2.append("h1,");
                                    AMR_D2.Vx[m] = 0;
                                    AMR_D2.Vy[m] = 0;
                                }

                                if (AMR_D2.x[m] - 6785 > 0 && abs(AMR_D2.y[m] - 6815) <= 10)
                                {
                                    AMR_D2.Vx[m] = -D2_Vx;
                                    AMR_D2.Vy[m] = 0;
                                }

                                if (abs(AMR_D2.x[m] - 7785) <= 10 && abs(AMR_D2.y[m] - 6815) <= 10)
                                {
                                    Path_AMR_D2.append("f1,");
                                }

                                if (abs(AMR_D2.x[m] - 6785) <= 10 && abs(AMR_D2.y[m] - 6815) <= 10)
                                {
                                    Path_AMR_D2.append("e1,");
                                    AMR_D2.Vx[m] = 0;
                                    AMR_D2.Vy[m] = 0;
                                }

                                if (abs(AMR_D2.x[m] - 6785) <= 10 && AMR_D2.y[m] - 4990 > 0)
                                {
                                    AMR_D2.Vx[m] = 0;
                                    AMR_D2.Vy[m] = -D2_Vy;
                                }

                                if (abs(AMR_D2.x[m] - 6785) <= 10 && abs(AMR_D2.y[m] - 4990) <= 10)
                                {
                                    Path_AMR_D2.append("e2,");
                                    AMR_D2.Vx[m] = 0;
                                    AMR_D2.Vy[m] = 0;
                                }

                                if (AMR_D2.x[m] - AMR_D2.x0 > 0 && abs(AMR_D2.y[m] - AMR_D2.y0) <= 10)
                                {
                                    AMR_D2.Vx[m] = -D2_Vx;
                                    AMR_D2.Vy[m] = 0;
                                }

                                //(870, 6170）位置回待命点
                                if (abs(AMR_D2.x[m] - 870) <= 10 && AMR_D2.y[m] - AMR_D2.y0 > 0)
                                {
                                    AMR_D2.Vx[m] = 0;
                                    AMR_D2.Vy[m] = -D2_Vy;
                                }

                                if (abs(AMR_D2.x[m] - 870) <= 10 && abs(AMR_D2.y[m] - AMR_D2.y0) <= 10)
                                {
                                    Path_AMR_D2.append("a1,");
                                    AMR_D2.Vx[m] = 0;
                                    AMR_D2.Vy[m] = 0;
                                }

                                if (AMR_D2.x[m] - AMR_D2.x0 < 0 && abs(AMR_D2.y[m] - AMR_D2.y0) <= 10)
                                {
                                    AMR_D2.Vx[m] = D2_Vx;
                                    AMR_D2.Vy[m] = 0;
                                }

                                //出入库接驳点回待命点
                                if (abs(AMR_D2.x[m] - AMR_D2.x0) <= 10 && AMR_D2.y[m] - AMR_D2.y0 < 0)
                                {
                                    AMR_D2.Vx[m] = 0;
                                    AMR_D2.Vy[m] = D2_Vy;
                                }

                                if (abs(AMR_D2.x[m] - AMR_D2.x0) <= 10 && abs(AMR_D2.y[m] - AMR_D2.y0) <= 10)
                                {
                                    Path_AMR_D2.append("d1");
                                    AMR_D2.Vx[m] = 0;
                                    AMR_D2.Vy[m] = 0;
                                    AMR_D2.State = 0;
                                    AMR_D2.Task_State = 0;
                                    AMR_D2.Outbound_Task = 0;
                                    AMR_D2.Inbound_Task = 0;
                                }
                            }
                        }
                        if (AMR_D2.State == 0)
                        {
                            AMR_D2.Vx[m] = 0;
                            AMR_D2.Vy[m] = 0;
                        }

                        //AMR_D1位置计算
                        AMR_D1.x[m + 1] = AMR_D1.x[m] + AMR_D1.Vx[m] * delta_t;
                        AMR_D1.y[m + 1] = AMR_D1.y[m] + AMR_D1.Vy[m] * delta_t;

                        //AMR_D2位置计算
                        AMR_D2.x[m + 1] = AMR_D2.x[m] + AMR_D2.Vx[m] * delta_t;
                        AMR_D2.y[m + 1] = AMR_D2.y[m] + AMR_D2.Vy[m] * delta_t;

                        t[m + 1] = t[m] + delta_t;
                        //cout << AMR_D1.x[m] << "," << AMR_D1.y[m] << endl;
                    }
                    float time =(double)mstimer.nsecsElapsed()/(double)1000000;
                    qDebug()<<"AMR_D1路线："<<Path_AMR_D1.data();
                    qDebug()<<"AMR_D2路线："<<Path_AMR_D2.data();
                    return time;

    }





