#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include <QJsonValue>
#include <QMetaType>
#include <QObject>
#include <QThread>
#include <stdint.h>
#include <QtEndian>
#include <QTcpSocket>
#include <qhostaddress.h>
#include <QMessageBox>
#include "XStateClient.h"

//发送控制命令类
class NetThread : public QObject
{
    Q_OBJECT
public:
    explicit NetThread(QObject *parent = nullptr);
    ~NetThread();

    void connectSend(unsigned short port, QString ip);
    void disconnectSend();
    void writeTcpData(quint16 sendCommand, const QByteArray &sendData, quint16 number);
signals:
    void connectOK();
private:
    QTcpSocket* m_tcp;
};

//接收小车状态类
class RecvThread : public QThread
{
    Q_OBJECT
public:
    RecvThread();
    void stopThread();
    int m_task_status;

protected:
    void  run() Q_DECL_OVERRIDE;  //线程任务

signals:
    void recv_value(double x,double y,double angle);

private:
    bool  m_Paused=true;
    bool  m_stop=false;
    XStateClient* xt;
    double m_x;
    double m_y;
    double m_angle;
    double m_battery_level;
};


class SeerHeader{
public:
    SeerHeader(){
        m_header = 0x5A;
        m_version = 0x01;
        m_number = 0;
        m_length = 0;
        m_type = 0;
        memset(m_reserved,0, 6);
    }

    uint8_t m_header;       //帧头
    uint8_t m_version;      //协议版本0x01
    uint16_t m_number;      //请求及响应序号（自行填入，请求和响应相对应）
    uint32_t m_length;      //发送的数据长度
    uint16_t m_type;        //报文类型（API编号）
    uint8_t m_reserved[6];
};


class SeerData{
public:
    SeerData(){}
    ~SeerData(){}
    int size(){
        return sizeof(SeerHeader) + m_header.m_length;
    }

    int setData(uint16_t type, uint8_t* data = NULL, int size = 0, uint16_t number = 0x00){
        m_header.m_header = 0x5A;
        m_header.m_version = 0x01;
        qToBigEndian(type, (uint8_t*)&(m_header.m_type));
        qToBigEndian(number, (uint8_t*)&(m_header.m_number));
        memset(m_header.m_reserved,0, 6);
        if (data != NULL) {
            memcpy(m_data, data, size);
        }
        qToBigEndian(size, (uint8_t*)&(m_header.m_length));
        return 16 + size;
    }
private:
    SeerHeader m_header;
    uint8_t m_data[1];
};

#endif // COMMUNICATE_H
