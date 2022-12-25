#pragma once

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <winsock2.h>
#include <string.h>
#include <unistd.h>
#include <hashtable.h>
#include <string>
#include <iostream>
#include "XData.h"

using namespace std;

#ifndef _XXX___
    #define _XXX___

    /**
     *定义TCP客户端类
     * */
    class XStateClient
    {

    private:
        const char *_ip; // 客户端IP
        const int _port; //客户端端口
        int _conn;       // 连接

        int x_send(XData data); //发送数据函数
        string x_recv();        //接收数据函数
        string x_get(int req);

    public:       
        bool x_connect();       //连接到服务器函数
        bool x_close();         // 从服务端断开函数
        XStateClient(const char *ip, int port = STATE_PORT) : _ip(ip), _port(port) {
            cout<< ">>>>>>>>>><<<<<<<<<<<<<" << endl;
        }
        ~XStateClient();

        string get_robot_info();  //查询机器人信息
        string get_robot_state(); //查询机器人运行信息
        string get_location();    //查询机器人位置
        string get_vel();         //查询机器人速度
        string get_block();       //查询机器人的被阻挡状态
        string get_battery();     //查询机器人电池状态
        string get_motor();       //查询电机状态信息
        string get_laser();       //查询机器人激光点云数据
        string get_area();        //查询机器人当前所在区域
        string get_emergency();   //查询机器人急停状态
        string get_io();          //查询机器人I/O数据
        string get_imu();         //查询机器人 IMU 数据
        string get_rfid();        //查询 RFID 数据
        string get_task_status(); //查询机器人导航状态
    };



#endif
