#ifndef MYTHREAD2_H
#define MYTHREAD2_H
#include <QThread>
#include <QMainWindow>

class MyThread2 : public QThread
{
    Q_OBJECT
public:
    explicit MyThread2(QObject *parent = 0);
    void stop();
//    double x1  = 0;
//    double y1  = 0;
//    double theta1 = 0 ;
//    int p1  = 0;//小车取货，送货，回城状态
    double tro_num2;//小车编号



protected:
    void run();
private:
    volatile bool stopped;
};

#endif // MYTHREAD_H
