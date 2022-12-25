/*************************************************
* 定义仙工车类，新增车创建实体，后续主程序尽量采用对象形式
*************************************************/
#ifndef CAR_H
#define CAR_H

class car
{
private:
    enum {x = 0, y, angle};
    double battery_level;   //电池电量
    int task_status;    //导航状态
    double pos[3];  //小车位置
public:


};

#endif // CAR_H
