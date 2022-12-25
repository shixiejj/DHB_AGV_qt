#pragma once

#ifndef _X_COM_
    #define _X_COM_

#define STATE_PORT 19204


#include <stdint.h>
#include <winsock2.h>

class XHeader
{
private:
    /* data */
public:
    uint8_t _sync = 0x5a;                      // 同步头
    uint8_t _version = 0x01;                   // 版本号
    uint16_t _number = 0;                      // 序号
    uint32_t _length = 0;                      // 数据区长度
    uint16_t _type = 0;                        // 报文类型
    uint8_t _reserved[6] = {0, 0, 0, 0, 0, 0}; // 保留字

    XHeader(/* args */);
    ~XHeader();
};



class XData
{
private:
    /* data */
public:
    XHeader _header;
    uint8_t _data[1];

    XData(/* args */);
    ~XData();

    int size()
    {
        return sizeof(XHeader) + _header._length;
    }

    void set_data(uint16_t type, uint8_t *data = NULL, int size = 0, uint16_t number = 0x00)
    {
        // host to net short int
        _header._number = htons(number);
        _header._type = htons(type);
        // host to net long int
        _header._length = htonl(size);
        if (data != NULL)
        {
            memcpy(_data, data, size);
        }
    }
};



#endif
