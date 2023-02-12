#ifndef MAP_READ_H
#define MAP_READ_H
#include<iostream>
#include<string>
#include <QPainter>
#include "cJSON.h"
struct MyPoint //创建点的数据
{
    int x;
    int y;
};

class map_read
{
public:
    map_read();
    int size_x;
    int size_y;
    int sum_plot;
    double origin_x;
    double origin_y;
    cJSON* m_jsonStr;
    QVector <MyPoint> Mypoints;
    void get_size();
    void get_json();
    void map_draw();
};

#endif // MAP_READ_H
