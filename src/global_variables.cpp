#include "global_variables.h"
#include <string>
using namespace std;


//冲突区域全局变量
bool car_online1 = 0;
double x1  = -100;
double yy1  = 0;
double theta1 = 0  ;
double p1  = 0 ;//小车取货，送货，回城状态
int  k = 0 ;
int  i = 0;
int  j = 0;
int  k1 = 0 ;
int  i1 = 0;
int  jj1 = 0;

int ui_num = 0;

bool car_online2 = 0;
double x2  = -100;
double yy2  = 0;
double theta2 = 0  ;
int p2  = 0 ;//小车取货，送货，回城状态

bool car_online3 = 0;
double x3  = -1000;
double yy3  = 0;
double theta3 = 0  ;
int p3  = 0 ;//小车取货，送货，回城状态




int D2_task_percent = 0;//4车执行任务进度提示，0-空闲 没有执行任务  1-正在执行任务
int D1_task_percent = 0;//3车执行任务进度提示，0-空闲 没有执行任务  1-正在执行任务
int B2_task_percent = 0;//2车执行任务进度提示，0-空闲 没有执行任务  1-正在执行任务
int B1_task_percent = 0;//1车执行任务进度提示，0-空闲 没有执行任务  1-正在执行任务

//用于调度任务的全局变量
string Path_AMR_D1("");
string Path_AMR_D2("");
string Path_AMR_B1("");
string Path_AMR_B2("");



/*QString pot_sta_code1_character = "";//用于判断是否发指令的判断小车是否到达指定节点的，这串表示给小车发的三串指令中的第一串中的最后一个字符
QString pot_sta_code2_character = "";
QString pot_sta_code3_character = "";*/

//int pot_sta_code1_character_sta = 0;



double delta_t = 0.02;         //跌代时间
double t[2000] = { 0 };         //时间

//AMR额定速度
int B1_Vx = 1000;
int B1_Vy = 1000;
int B2_Vx = 1000;
int B2_Vy = 1000;
int D1_Vx = 1000;
int D1_Vy = 1000;
int D2_Vx = 1000;
int D2_Vy = 1000;

int Task = 0;                   //任务类型：0--无任务；1--出库任务；2--入库任务；3--移库任务
int Take_x = 0;                 //大任务取货点
int Take_y = 0;
int Deliver_x = 0;              //大任务送货点
int Deliver_y = 0;

int B_Outbound_Task_State = 0;  //AMR_B出库任务：0--无出库任务；1--有出库任务
int B_Inbound_Task_State = 0;   //AMR_B入库任务：0--无入库任务；1--有入库任务
int B_Take_x = 0;               //AMR_B取货点
int B_Take_y = 0;
int B_Deliver_x = 0;            //AMR_B送货点
int B_Deliver_y = 0;
int B_Task = 1;
int D_Task = 1;

int D_Outbound_Task_State = 0;  //AMR_D出库任务：0--无出库任务；1--有出库任务
int D_Inbound_Task_State = 0;   //AMR_D入库任务：0--无入库任务；1--有入库任务
int D_Take_x = 0;               //AMR_D取货点
int D_Take_y = 0;
int D_Deliver_x = 0;            //AMR_D送货点
int D_Deliver_y = 0;

int Conection_1_State = 0;      //接驳区1状态：0--空闲；1--忙碌
int Conection_2_State = 0;      //接驳区2状态：0--空闲；1--忙碌

double test_x;
double test_y;

Global_Variables::Global_Variables()
{

}
