/*************************************************
* 定义仙工车类，新增车创建实体，后续主程序尽量采用对象形式
*************************************************/
#ifndef CAR_H
#define CAR_H

class car
{
private:
    //接收状态的属性
    enum {x = 0, y, angle};
    double battery_level;   //电池电量
    int task_status;    //导航状态
    double pos[3];  //小车位置


public:
    void set_motionPar(double speed, double wspeed, double acc, double wacc);

    //发送指令设置的属性
    bool online_status;
    double max_speed;   //最大速度
    double max_wspeed;  //最大角速度
    double max_acc;     //最大加速度
    double max_wacc;    //最大角加速度

};


#endif // CAR_H
