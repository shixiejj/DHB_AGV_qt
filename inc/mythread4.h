#ifndef MYTHREAD4_H
#define MYTHREAD4_H
extern bool car_online4;
extern double x4;
extern double yy4;
extern double theta4;
extern int p4;

#include <QThread>
#include <QMainWindow>

class MyThread4 : public QThread
{
    Q_OBJECT
public:
    explicit MyThread4(QObject *parent = 0);
    void stop();
//    double x1  = 0;
//    double y1  = 0;
//    double theta1 = 0 ;
//    int p1  = 0;//小车取货，送货，回城状态
    double tro_num4;//小车编号



protected:
    void run();
private:
    volatile bool stopped;
};

#endif // MYTHREAD4_H
