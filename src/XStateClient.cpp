#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <winsock2.h>
#include <string.h>
#include <unistd.h>
#include <hashtable.h>
#include <string>
#include <iostream>
#include "XStateClient.h"

XStateClient::~XStateClient() {}

bool XStateClient::x_connect()
{

    WSADATA wsaData;
    int iResult;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    _conn = socket(AF_INET, SOCK_STREAM, 0);
    if (_conn == -1)
    {
        cout << "init error" << endl;
        return false;
    }
    // connect
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(_ip);
    serverAddr.sin_port = htons(_port);

    if (connect(_conn, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cout << "conn error" << std::endl;
        return 0;
    }
    std::cout << "conn suss" << std::endl;

    return true;
}

bool XStateClient::x_close()
{
    return closesocket(_conn);
}

int XStateClient::x_send(XData data)
{
    return send(_conn, (char *)&data, data.size(), 0);
}

string XStateClient::x_recv()
{
    string info = "";
    char header[17];
    memset(header, 0, sizeof(header));
    // 检查头
    int header_len = recv(_conn, header, 16, 0);
    if (16 != header_len or 0x5a != header[0])
    {
        return info;
    }
    // 获取长度
    int len = (header[7] << 24) | (header[6] << 16) | (header[5] << 8) | (header[4]);
    len = ntohl(len);
    cout << "data_len " << len << endl;
    // 获取json串
    char data[len + 1];
    memset(data, 0, sizeof(data));
    int recv_len = 0;
    int all_recv_len = 0;
    while (all_recv_len < len)
    {
        recv_len = recv(_conn, data, len - all_recv_len, 0);
        if (recv_len <= 0)
        {
            cout << "recv_len " << recv_len << endl;
            sleep(1);
            continue;
        }
        data[recv_len] = '\0';
        info += data;
        all_recv_len += recv_len;
        cout << "recv_len " << recv_len << endl;
        cout << "all_recv_len " << all_recv_len << endl;
        cout << "len " << len << endl;
    }
    return info;
}

string XStateClient::x_get(int req)
{
    XData data;
    data.set_data(req);
    x_send(data);
    //cout << "XStateClient::x_get" << endl;
    string info = x_recv();
    return info;
}

/*
编号: 1000 (0x03E8)
名称: robot_status_info_req
描述: 查询机器人信息
JSON 数据区: 无
*/
string XStateClient::get_robot_info()
{
    return x_get(1000);
}

/*
编号: 1002 (0x03EA)
名称: robot_status_run_req
描述: 查询机器人的运行状态信息(如运行时间、里程等)
JSON 数据区: 无
*/
string XStateClient::get_robot_state()
{
    return x_get(1002);
}

/*
编号: 1004 (0x03EC)
名称: robot_status_loc_req
描述: 查询机器人位置
JSON 数据区: 无
*/
string XStateClient::get_location()
{
    return x_get(1004);
}

/*
编号: 1005 (0x03ED)
名称: robot_status_speed_req
描述: 查询机器人速度
JSON 数据区: 无
*/
string XStateClient::get_vel()
{
    return x_get(1005);
}

/*
编号: 1006 (0x03EE)
名称: robot_status_block_req
描述: 查询机器人的被阻挡状态
JSON 数据区: 无
*/
string XStateClient::get_block()
{
    return x_get(1006);
}

/*
编号: 1007 (0x03EF)
名称: robot_status_battery_req
描述: 查询机器人电池状态
JSON 数据区: 见下表
字段名	类型	描述	可缺省
simple	boolean	是否只返回简单数据, true = 是，false = 否，缺省则为否	是
*/
string XStateClient::get_battery()
{
    return x_get(1007);
}

/*
编号: 1040 (0x0410)
名称: robot_status_motor_req
描述: 查询电机状态信息
JSON 数据区: 见下表
字段名	类型	描述	可缺省
motor_names	array[string]	根据电机名称查询指定电机状态信息
如果缺省该字段表示查询所有电机状态信息	是
*/
string XStateClient::get_motor()
{
    return x_get(1040);
}

/*
编号: 1009 (0x03F1)
名称: robot_status_laser_req
描述: 查询机器人激光点云数据
JSON 数据区: 见下表
字段名	         类型	  描述	                                                      可缺省
return_beams3D	boolean	是否返回多线激光数据，true = 返回，false = 不返回，缺省则为不返回	是
*/
string XStateClient::get_laser()
{
    return x_get(1009);
}

/*
编号: 1011 (0x03F3)
名称: robot_status_area_req
描述: 查询机器人当前所在的区域信息
JSON 数据区: 无
*/
string XStateClient::get_area()
{
    return x_get(1011);
}

/*
编号: 1012 (0x03F4)
名称: robot_status_emergency_req
描述: 查询机器人急停按钮的状态
JSON 数据区: 无
*/
string XStateClient::get_emergency()
{
    return x_get(1012);
}

/*
编号: 1013 (0x03F5)
名称: robot_status_io_req
描述: 查询机器人 I/O 数据
JSON 数据区: 无
*/
string XStateClient::get_io()
{
    return x_get(1013);
}

/*
编号: 1014 (0x03F6)
名称: robot_status_imu_req
描述: 查询机器人 IMU 数据
JSON 数据区: 无
*/
string XStateClient::get_imu()
{
    return x_get(1014);
}

/*
编号: 1015 (0x03F7)
名称: robot_status_rfid_req
描述: 查询 RFID 数据
JSON 数据区: 无
*/
string XStateClient::get_rfid()
{
    return x_get(1015);
}

/*
编号: 1020 (0x03FC)
名称: robot_status_task_req
描述: 查询机器人当前的导航状态, 导航站点, 导航相关路径(已经经过的站点, 尚未经过的站点)等
JSON 数据区: simple字段
*/
string XStateClient::get_task_status()
{
    return x_get(1020);
}
