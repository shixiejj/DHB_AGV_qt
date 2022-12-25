#ifndef MYTHREAD3_H
#define MYTHREAD3_H

#include <QThread>
#include <QMainWindow>

class MyThread3 : public QThread
{
    Q_OBJECT
public:
    explicit MyThread3(QObject *parent = 0);
    void stop();
//    double x1  = 0;
//    double y1  = 0;
//    double theta1 = 0 ;
//    int p1  = 0;//小车取货，送货，回城状态
    double tro_num3;//小车编号



protected:
    void run();
private:
    volatile bool stopped;
};

#endif // MYTHREAD3_H
