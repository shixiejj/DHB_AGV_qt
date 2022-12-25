#include "device_con.h"
#include "ui_device_con.h"
#include "qpainter.h"
device_con::device_con(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::device_con)
{
    ui->setupUi(this);
    this->setWindowTitle("AMR管理与控制界面");//标题
}


void device_con::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen1(QColor(0,0,0));//指定画笔
    pen1.setWidth(3);//画笔宽度
    painter.setPen(pen1);//确定画笔
    //AMR控制管理
    painter.drawRect(QRect(89,80,1203,835));
    //AMR添加
    painter.drawRect(QRect(1363,80,468,835));

    QPen pen2(QColor(0,0,0));//指定画笔
    pen2.setWidth(1);//画笔宽度
    painter.setPen(pen2);//确定画笔
    painter.drawRect(QRect(99,90,1183,815));
    painter.drawRect(QRect(1373,90,448,815));



}



device_con::~device_con()
{
    delete ui;
}
