#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "device_con.h"
#include <QThread>
#include "communicate.h"
#include "editwidget.h"
#include "editdialog.h"
#include "mythread.h"
#include "mythread2.h"
#include "mythread3.h"
#include "mythread4.h"
#include <QFileDialog>
#include <QFileInfo>

//sql实现表刷新更改
#include <QtSql>
#include <QDataWidgetMapper>
//重定义模型实现表格居中
#include "customClass.h"

#include "XStateClient.h"
#include "showunitywindowsinqt.h"
#include "car.h"





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QSqlDatabase DB;
    CustomSqlQueryModel *qryModel;
    CustomSqlQueryModel *qryModel3;
    CustomSqlQueryModel *qryModel4;
    CustomSqlQueryModel *qryModel5;
    CustomSqlQueryModel *qryModel6;
    QSqlQueryModel *qryModel2;
    QItemSelectionModel *theSelection;
    QSqlRecord newRecord;
    ShowUnityWindowsInQt* util;

    void updateRecord(int recNo); //更新记录
    void openTable();
    void DB_task();
    void test1_1(int x, int y);
    void test1_2(int x, int y);
    void test2_1(int x, int y);
    void test2_2(int x, int y);
    void test3_1(int x, int y);
    void test3_2(int x, int y);
    void test4_1(int x, int y);
    void test4_2(int x, int y);
    QSqlRecord getRecordData(QSqlQuery quer);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setStatusLed(QLabel* label, int color);

    device_con *deviceqt;

    //void paintEvent(QPaintEvent *);

private slots:

    //void on_pushButton_clicked();

    //void on_lan_cellClicked(int row, int column);

    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_startButton_2_clicked();

    void on_stopButton_2_clicked();

    void on_startButton_3_clicked();

    void on_stopButton_3_clicked();

    void on_startButton_4_clicked();

    void on_stopButton_4_clicked();

    void on_f_code_Button_clicked();//调试按钮

    void on_s_task1_Button_clicked();//料箱式任务发布按钮

   //void on_s_task2_Button_clicked();//配送式任务发布按钮

    void on_netManage_clicked();

    void on_offerManage_clicked();

    void on_diaoduManage_clicked();

    void on_stateMonitor_clicked();

    void on_AMRManage_clicked();

    void on_waishePanel_clicked();

    void on_elecMap_clicked();

    void on_dataCollect_clicked();

    void on_workData_clicked();

    void on_userManage_clicked();

    //void slotTime();//表格刷新函数



    //void on_newTask_Button_clicked();
    
    void on_netManage_toggled(bool checked);

    void on_offerManage_toggled(bool checked);

    void on_diaoduManage_toggled(bool checked);

    void on_stateMonitor_toggled(bool checked);

    void on_AMRManage_toggled(bool checked);

    void on_waishePanel_toggled(bool checked);

    void on_elecMap_toggled(bool checked);

    void on_dataCollect_toggled(bool checked);

    void on_workData_toggled(bool checked);

    void on_userManage_toggled(bool checked);

    void on_mapSwitch_stateChanged(int arg1);


    void on_shanchu_clicked();

    void on_xiugai_clicked();

    void on_tableTest_doubleClicked(const QModelIndex &index);

    void on_newOk_clicked();

    void on_debugSwitch_stateChanged(int arg1);

    void task_timeinfo();

    void cfunction_string(int task_info,int QgsPointX,int QgsPointY,int QgePointX,int QgePointY);

    void on_startButton_10_clicked();

    void getCarData(double x, double y, double angle);

    void connect_test();

    void after_connect();

    void on_stopButton_10_clicked();

    void on_rejectOffer_clicked();

    void on_acceptOffer_clicked();
    
    void on_maxVelocity_valueChanged(int value);

    void on_maxAcceleration_valueChanged(int value);

    void on_maxAngleVelocity_valueChanged(int value);

    void on_maxAngleAcceleration_valueChanged(int value);

    void on_pushButton_108_clicked();

    void on_pushButton_80_clicked();

signals:
    void startConnectSend(unsigned short,QString);

    void startConnectRecv();

    void disconnect();

    void readCar();

    void writeTcpData(quint16, const QByteArray&, quint16);

private:
    double tro_num = 1;//小车编号
    double tro_net = 0;//小车网络
    double tro_ele = 9;//小车电压
    double tro_load = 0;//小车是否有负载
    double ax1  = 0;
    double ay1  = 0;
    double atheta1 = 0 ;
    int ap1  = 0;//小车取货，送货，回城状态

    //小车2
    double tro_num2 = 1;//小车编号
    double tro_net2 = 0;//小车网络
    double tro_ele2 = 9;//小车电压
    double tro_load2 = 0; //小车是否有负载
    double ax2     = 0 ;
    double ay2     = 0;
    double atheta2 = 0 ;
    double v2 = 0;
    int ap2 = 0 ;//小车取货，送货，回城状态

    double tro_num3 = 1;//小车编号
    double tro_net3 = 0;//小车网络
    double tro_ele3 = 9;//小车电压
    double tro_load3 = 0;//小车是否有负载
    double ax3  = 0;
    double ay3  = 0;
    double atheta3 = 0 ;
    int ap3  = 0;//小车取货，送货，回城状态

    double tro_num4 = 1;//小车编号
    double tro_net4 = 0;//小车网络
    double tro_ele4 = 9;//小车电压
    double tro_load4 = 0;//小车是否有负载
    double ax4 = 0;
    double ay4  = 0;
    double atheta4 = 0 ;
    int ap4  = 0;//小车取货，送货，回城状态

    int DB_current = 0;

    Ui::MainWindow *ui;
    MyThread   thread;
    MyThread2  thread2;
    MyThread3  thread3;
    MyThread4  thread4;
    QThread* send_task;
    QThread* unity_task;

    NetThread* send;
    RecvThread recv_task;


     QTimer *timer1;//定时器
     QTimer *timer2;//代码定时器
     QTimer *timer3;//数据刷新
     QTimer *timer4;//接受数据库任务的刷新
     QTimer *timer5;//用于定时查询仙工小车状态
     QTimer *timer6;//用于定时更新系统时间

     //用车类创建测试所用的4辆车对象
     //TODO:后期可以根据网络管理页面动态管理车类对象
     car amr_d_1;
     car amr_d_2;
     car amr_s_1;
     car amr_s_2;


};

extern int code_send_sta;//1车发送第三段代码的标志位
extern int task_whole_B1;//1车发送第二段代码的标志位
extern QStringList AMR_B2_code;//2车代码段

extern int code_send_sta_2;//3车发送第三段代码的标志位
extern int task_whole_B2;//3车发送第二段代码的标志位
extern QStringList AMR_D2_code;
extern QStringList AMR_B1_code;

extern int code_send_sta_3;//4车发送第三段代码的标志位
extern int task_whole_D1;//4车发送第二段代码的标志位

extern int code_send_sta_4;//1车发送第三段代码的标志位
extern int task_whole_D2;//1车发送第二段代码的标志位
extern QStringList AMR_D1_code;//1车代码段

extern int code_sta_e3;
extern int code_sta_c1;
extern int code_sta_e3_2;
extern int code_sta_c1_2;

extern int end_pot_sta_g1;//1车终点状态位

extern int end_pot_sta_g2;//2车终点状态位

extern int end_pot_sta_c1;//3车终点状态位

extern int end_pot_sta_b2;//4车终点状态位

void Delay_function(unsigned int msec);

#endif // MAINWINDOW_H
