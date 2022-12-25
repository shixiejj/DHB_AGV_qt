#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QMainWindow>

#pragma once
void issue_command(int x, int y, int z, QString str, QString str2, QString str3, QString str4, QString str5, QString str6, QString str7, QString str8, QString str9);
void issue2_command(int x, int y, int z, QString str, QString str2, QString str3, QString str4, QString str5, QString str6, QString str7, QString str8, QString str9);


class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    void stop();
//    double x1  = 0;
//    double y1  = 0;
//    double theta1 = 0 ;
//    int p1  = 0;//小车取货，送货，回城状态
    double tro_num;//小车编号



protected:
    void run();
private:
    volatile bool stopped;
};

#endif // MYTHREAD_H
