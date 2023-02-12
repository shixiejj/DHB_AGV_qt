#ifndef MAPREAD_H
#define MAPREAD_H
#include<iostream>
#include<string>
class MapRead
{
    public:
        int size_x;
        int size_y;
        double origin_x;
        double origin_y;
        char* m_jsonStr;
        void get_size();
        void get_json();
        void map_draw();
};
#endif // MAPREAD_H
