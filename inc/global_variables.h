#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
#include <string>
using namespace std;
//冲突区域全局变量

/*extern QString pot_sta_code1_character;//用于判断是否发指令的判断小车是否到达指定节点的，这串表示给小车发的三串指令中的第一串中的最后一个字符
extern QString pot_sta_code2_character;
extern QString pot_sta_code3_character;*/

//extern int pot_sta_code1_character_sta = "";

//点坐标
//#define a1_x 696
//#define a1_y 3884
//#define b1_x 2539
//#define b1_y 3884
//#define b2_x 2539
//#define b2_y 2260
//#define b3_x 2539
//#define b3_y 744
//#define c1_x 3732
//#define c1_y 3884
//#define c2_x 3732
//#define c2_y 2260
//#define c3_x 3732
//#define c3_y 744
//#define d1_x 4904
//#define d1_y 3884
//#define d2_x 4904
//#define d2_y 2260
//#define d3_x 4904
//#define d3_y 744
//#define e1_x 696
//#define e1_y 3884
//#define e2_x 2539
//#define e2_y 3884
//#define f1_x 5952
//#define f1_y 5793
//#define g1_x 6228
//#define g1_y 3992
//#define g2_x 6228
//#define g2_y 2100
//#define h1_x 6668
//#define h1_y 5793
//#define i1_x 8876
//#define i1_y 3992
//#define i2_x 8876
//#define i2_y 2100
//#define i3_x 8876
//#define i3_y 688
//#define j1_x 11524
//#define j1_y 3992
//#define j2_x 11524
//#define j2_y 2100
//#define j3_x 11524
//#define j3_y 688
//#define t1_x 696
//#define t1_y 4936
//#define t2_x 6668
//#define t2_y 4936
//#define s1_x 4904
//#define s1_y 3046
//#define s2_x 6228
//#define s2_y 3046
//#define s3_x 4904
//#define s3_y 1322
//#define s4_x 6228
//#define s4_y 1322
//#define l1_x 7144
//#define l1_y 3992
//#define l2_x 7556
//#define l2_y 3992
//#define l3_x 7950
//#define l3_y 3992
//#define l4_x 9794
//#define l4_y 3992
//#define l5_x 10200
//#define l5_y 3992
//#define l6_x 10610
//#define l6_y 3992
//#define l7_x 7144
//#define l7_y 2100
//#define l8_x 7556
//#define l8_y 2100
//#define l9_x 7950
//#define l9_y 2100
//#define l10_x 9794
//#define l10_y 2100
//#define l11_x 10200
//#define l11_y 2100
//#define l12_x 10610
//#define l12_y 2100
//#define u1_x 696
//#define u1_y 7498
//#define u2_x 6228
//#define u2_y 6860

#define a1_x 69
#define a1_y 388
#define b1_x 253
#define b1_y 388
#define b2_x 253
#define b2_y 226
#define b3_x 253
#define b3_y 74
#define c1_x 373
#define c1_y 388
#define c2_x 373
#define c2_y 226
#define c3_x 373
#define c3_y 74
#define d1_x 490
#define d1_y 388
#define d2_x 490
#define d2_y 226
#define d3_x 490
#define d3_y 74
#define e1_x 69
#define e1_y 388
#define e2_x 253
#define e2_y 388
#define f1_x 595
#define f1_y 579
#define g1_x 622
#define g1_y 399
#define g2_x 622
#define g2_y 210
#define h1_x 666
#define h1_y 579
#define i1_x 887
#define i1_y 399
#define i2_x 887
#define i2_y 210
#define i3_x 887
#define i3_y 68
#define j1_x 1152
#define j1_y 399
#define j2_x 1152
#define j2_y 210
#define j3_x 1152
#define j3_y 68
#define t1_x 69
#define t1_y 493
#define t2_x 666
#define t2_y 493
#define s1_x 490
#define s1_y 304
#define s2_x 622
#define s2_y 304
#define s3_x 490
#define s3_y 132
#define s4_x 622
#define s4_y 132
#define l1_x 714
#define l1_y 399
#define l2_x 755
#define l2_y 399
#define l3_x 795
#define l3_y 399
#define l4_x 979
#define l4_y 399
#define l5_x 1020
#define l5_y 399
#define l6_x 1061
#define l6_y 399
#define l7_x 714
#define l7_y 210
#define l8_x 755
#define l8_y 210
#define l9_x 795
#define l9_y 210
#define l10_x 979
#define l10_y 210
#define l11_x 1020
#define l11_y 210
#define l12_x 1061
#define l12_y 210
#define u1_x 69
#define u1_y 749
#define u2_x 622
#define u2_y 686

extern bool car_online1;
extern double x1;
extern double yy1;
extern double theta1;
extern double p1;
extern int k;
extern int i;
extern int j;
extern int k1;
extern int i1;
extern int jj1;

extern double test_x;
extern double test_y;

extern bool car_online2;
extern double x2;
extern double yy2;
extern double theta2;
extern int p2;

extern bool car_online3;
extern double x3;
extern double yy3;
extern double theta3;
extern int p3;

extern int ui_num ;


extern int D2_task_percent ;//4车执行任务进度提示，0-空闲 没有执行任务  1-正在执行任务
extern int D1_task_percent ;//3车执行任务进度提示，0-空闲 没有执行任务  1-正在执行任务
extern int B2_task_percent ;//2车执行任务进度提示，0-空闲 没有执行任务  1-正在执行任务
extern int B1_task_percent;//1车执行任务进度提示，0-空闲 没有执行任务  1-正在执行任务

extern string Path_AMR_D1;
extern string Path_AMR_D2;
extern string Path_AMR_B1;
extern string Path_AMR_B2;
class Robot
{
public:
    int x[2000] = { 0 };            //x位置
    int y[2000] = { 0 };            //y位置
    int Vx[2000] = { 0 };           //x速度
    int Vy[2000] = { 0 };           //y速度
    int x0;                        //初始x位置
    int y0;                        //初始y位置
    int Task_State = 0;            //任务状态：0--空闲；1--忙碌

    /*
    执行任务状态：
    0表示停止等待：取货等待、卸货等待、充电等待等；
    1表示接到出库任务前往存储区取料箱
    2表示接到出库任务送料箱到出入库接驳点出库
    3表示接到入库任务前往出入库接驳点取料箱
    4表示接到入库任务送料箱上料架入库
    5表示接到移库任务去取料箱
    6表示接到移库任务去送料箱到目标库位
    7表示接到充电任务去充电区充电
    8表示回待命区任务
    */
    int State = 0;
    int Take_x = 0;                //取料箱x坐标
    int Take_y = 0;                //取料箱y坐标
    int Deliver_x = 0;             //送料箱x坐标
    int Deliver_y = 0;             //送料箱y坐标
    int Destination_x = 0;         //最终目的地x坐标
    int Destination_y = 0;         //最终目的地y坐标
    int Route = 0;
    int Outbound_Task = 0;         //出库任务：0--无出库任务；1--有出库任务
    int Inbound_Task = 0;          //入库任务：0--无入库任务；1--有入库任务
    int Shift_Warehouse_Task = 0;  //移库任务：0--无移库任务；1--有移库任务
    int Outbound_Date = 0;         //更新出库数据
    int Inbound_Date = 0;          //更新入库数据
    int Shift_Warehouse_Date = 0;  //更新移库数据
};

extern double delta_t ;         //跌代时间
extern double t[2000] ;         //时间


//AMR额定速度
extern int B1_Vx ;
extern int B1_Vy ;
extern int B2_Vx ;
extern int B2_Vy ;
extern int D1_Vx ;
extern int D1_Vy ;
extern int D2_Vx ;
extern int D2_Vy ;

extern int Task ;                   //任务类型：0--无任务；1--出库任务；2--入库任务；3--移库任务
extern int Take_x ;                 //大任务取货点
extern int Take_y ;
extern int Deliver_x ;              //大任务送货点
extern int Deliver_y ;
extern int B_Task ;
extern int D_Task ;

extern int B_Outbound_Task_State ;  //AMR_B出库任务：0--无出库任务；1--有出库任务
extern int B_Inbound_Task_State ;   //AMR_B入库任务：0--无入库任务；1--有入库任务
extern int B_Take_x ;               //AMR_B取货点
extern int B_Take_y ;
extern int B_Deliver_x ;            //AMR_B送货点
extern int B_Deliver_y ;

extern int D_Outbound_Task_State ;  //AMR_D出库任务：0--无出库任务；1--有出库任务
extern int D_Inbound_Task_State ;   //AMR_D入库任务：0--无入库任务；1--有入库任务
extern int D_Take_x ;               //AMR_D取货点
extern int D_Take_y ;
extern int D_Deliver_x ;            //AMR_D送货点
extern int D_Deliver_y ;

extern int Conection_1_State ;      //接驳区1状态：0--空闲；1--忙碌
extern int Conection_2_State ;      //接驳

class Global_Variables
{
public:
    Global_Variables();
};

#endif // GLOBAL_VARIABLES_H
