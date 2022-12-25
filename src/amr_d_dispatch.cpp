#include "amr_d_dispatch.h"
#include<iostream>
#include<QDebug>
#include "mainwindow.h"
#include "global_variables.h"
using namespace std;

//定义4个机器人类


/*
AMR_D_dispatch::AMR_D_dispatch()
{
       // D_dispatch(1, 6130, 1653, 870, 6170);


            //D1_task_percent =1;
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

                            if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && abs(AMR_D1.y[m] - 2625) <= 10)
                            {
                                Path_AMR_D1.append("d2,");
                                AMR_D1.Vx[m] = 0;
                                AMR_D1.Vy[m] = 0;
                            }

                            if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && AMR_D1.y[m] - AMR_D1.Take_y < 0)
                            {
                                AMR_D1.Vx[m] = 0;
                                AMR_D1.Vy[m] = D1_Vy;
                            }
                            if (abs(AMR_D1.x[m] - AMR_D1.Take_x) <= 10 && AMR_D1.y[m] - AMR_D1.Take_y > 0)
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



}
*/
