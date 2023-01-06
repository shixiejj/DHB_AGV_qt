#include "drawdraw.h"
#include "global_variables.h"
#include "mythread.h"
#include "mythread2.h"
#include "mythread3.h"
#include "mythread4.h"

DRAWmap::DRAWmap(QWidget *parent) : QWidget(parent)
{
    m_drawPen=QPen(Qt::yellow,20);		//设置画笔属性
    m_drawPen.setStyle(Qt::SolidLine);
    this->setMouseTracking(true);
}

void DRAWmap::GainChange(double scale)
{
    gain = scale;
}

DRAWmap::~DRAWmap()
{
    if(m_painter != NULL)
    {
        delete m_painter;
        m_painter = NULL;
    }
}

void DRAWmap::paintEvent(QPaintEvent* event)
{
    m_painter = new QPainter(this);
    m_painter->translate(220,115);      //偏移坐标系
    m_painter->scale(gain,gain);        //缩放地图

    int map_l=1224;
    int map_w=800;

    //给对应节点做标记
     QPen pend(QColor(255,255,255));
     m_painter->setPen(pend);
     m_painter->drawText(QRect(50,map_w-750,120,20),"u1");
     m_painter->drawText(QRect(50,map_w-494,120,20),"t1");
     m_painter->drawText(QRect(50,map_w-388,120,20),"a1");

     m_painter->drawText(QRect(234,map_w-388,120,20),"b1");
     m_painter->drawText(QRect(234,map_w-226,120,20),"b2");
     m_painter->drawText(QRect(234,map_w-74,120,20),"b3");

     m_painter->drawText(QRect(353,map_w-388,120,20),"c1");
     m_painter->drawText(QRect(353,map_w-226,120,20),"c2");
     m_painter->drawText(QRect(353,map_w-74,120,20),"c3");

     m_painter->drawText(QRect(470,map_w-388,120,20),"d1");
     m_painter->drawText(QRect(470,map_w-226,120,20),"d2");
     m_painter->drawText(QRect(470,map_w-74,120,20),"d3");

     m_painter->drawText(QRect(523,map_w-545,120,20),"e1");
     m_painter->drawText(QRect(523,map_w-388,120,20),"e2");

     m_painter->drawText(QRect(575,map_w-590,120,20),"f1");

     m_painter->drawText(QRect(603,map_w-686,120,20),"u2");
     m_painter->drawText(QRect(603,map_w-399,120,20),"g1");
     m_painter->drawText(QRect(603,map_w-210,120,20),"g2");

     m_painter->drawText(QRect(647,map_w-595,120,20),"h1");
     m_painter->drawText(QRect(647,map_w-494,120,20),"t2");

     m_painter->drawText(QRect(868,map_w-399,120,20),"i1");
     m_painter->drawText(QRect(868,map_w-210,120,20),"i2");
     m_painter->drawText(QRect(868,map_w-69,120,20),"i3");

     m_painter->drawText(QRect(1132,map_w-399,120,20),"j1");
     m_painter->drawText(QRect(1132,map_w-210,120,20),"j2");
     m_painter->drawText(QRect(1132,map_w-69,120,20),"j3");
     m_painter->drawText(QRect(470,map_w-305,120,20),"s1");
     m_painter->drawText(QRect(603,map_w-305,120,20),"s2");
     m_painter->drawText(QRect(470,map_w-132,120,20),"s3");
     m_painter->drawText(QRect(603,map_w-132,120,20),"s4");

     //绘制地图上实物
     pend.setWidth(1);
//     m_painter->setBrush(Qt::NoBrush);
//     m_painter->setPen(pend);
     m_painter->drawRect(QRect(192,map_w-726,272,254));//设备1的框
     m_painter->drawRect(QRect(821,map_w-726,307,254));//设备2的框
     m_painter->drawRect(QRect(100,map_w-515,57,43));//工作台1
     m_painter->drawRect(QRect(104,map_w-511,49,35));//工作台1
     m_painter->drawRect(QRect(729,map_w-515,57,43));//工作台2
     m_painter->drawRect(QRect(733,map_w-511,49,35));//工作台2

     m_painter->drawRect(QRect(521,map_w-326,57,43));//接驳台1
     m_painter->drawRect(QRect(525,map_w-322,49,35));//接驳台1
     m_painter->drawRect(QRect(521,map_w-154,57,43));//接驳台2
     m_painter->drawRect(QRect(525,map_w-150,49,35));//接驳台2

     m_painter->drawRect(QRect(464,map_w-726,60,120));//桌子1
     m_painter->drawRect(QRect(1128,map_w-592,60,120));//桌子2

     m_painter->drawRect(QRect(0,map_w-282,195,282));

     m_painter->drawText(QRect(85,map_w-39,100,48),"参观区");
     m_painter->drawRect(QRect(95,map_w-272,80,48));
     m_painter->drawText(QRect(95,map_w-272,80,48),"服务器");
     m_painter->drawRect(QRect(115,map_w-214,60,120));

     m_painter->setBrush(Qt::BDiagPattern);
     //货架1
     m_painter->drawRect(QRect(688,map_w-355,135,100));

     //货架2
     m_painter->drawRect(QRect(953,map_w-355,135,100));

     //货架3
     m_painter->drawRect(QRect(688,map_w-166,135,52));

     //货架4
     m_painter->drawRect(QRect(953,map_w-166,135,52));

     QFont font;
     font.setFamily("Microsoft YaHei");
     font.setPointSize(20);
     font.setBold(false);
     m_painter->setFont(font);
     m_painter->drawText(QRect(277,map_w-632,120,100),"设备1");
     m_painter->drawText(QRect(925,map_w-632,120,100),"设备2");


    QPen pen1(QColor(100,200,200));
    m_painter->setPen(pen1);
    pen1.setWidth(3);
    m_painter->setBrush(Qt::NoBrush);
    m_painter->setPen(pen1);

    m_painter->drawLine(QPoint(70,map_w-750) , QPoint(70,map_w-388));
    m_painter->drawLine(QPoint(70,map_w-388) , QPoint(543,map_w-388));
    m_painter->drawLine(QPoint(254,map_w-226) , QPoint(490,map_w-226));
    m_painter->drawLine(QPoint(254,map_w-74) , QPoint(490,map_w-74));
    m_painter->drawLine(QPoint(254,map_w-388) , QPoint(254,map_w-74));
    m_painter->drawLine(QPoint(373,map_w-388) , QPoint(373,map_w-74));
    m_painter->drawLine(QPoint(490,map_w-388) , QPoint(490,map_w-74));
    m_painter->drawLine(QPoint(543,map_w-388) , QPoint(543,map_w-545));
    m_painter->drawLine(QPoint(543,map_w-545) , QPoint(595,map_w-579));
    m_painter->drawLine(QPoint(595,map_w-579) , QPoint(667,map_w-579));
    m_painter->drawLine(QPoint(667,map_w-579) , QPoint(667,map_w-474));


    QPen pen2(QColor(200,10,10));
    m_painter->setPen(pen2);
    pen2.setWidth(3);
    m_painter->setBrush(Qt::NoBrush);
    m_painter->setPen(pen2);

    //物料分拣小车路线图
    m_painter->drawLine(QPoint(623,map_w-399) , QPoint(1152,map_w-399));
    m_painter->drawLine(QPoint(623,map_w-210) , QPoint(1152,map_w-210));
    m_painter->drawLine(QPoint(888,map_w-69) , QPoint(1152,map_w-69));
    m_painter->drawLine(QPoint(623,map_w-100) , QPoint(623,map_w-686));
    m_painter->drawLine(QPoint(888,map_w-69) , QPoint(888,map_w-399));
    m_painter->drawLine(QPoint(1152,map_w-69) , QPoint(1152,map_w-399));

    //工作台
    m_painter->drawEllipse(QPoint(70,map_w-494),5,5);//工作台1
    m_painter->drawEllipse(QPoint(667,map_w-494),5,5);//工作台2
    m_painter->drawRect(QRect(0,0,map_l,map_w));

    //接驳点1
    m_painter->drawEllipse(QPoint(490,map_w-305),5,5);
    m_painter->drawEllipse(QPoint(623,map_w-305),5,5);
    //接驳点2
    m_painter->drawEllipse(QPoint(490,map_w-132),5,5);
    m_painter->drawEllipse(QPoint(623,map_w-132),5,5);

    //状态监控页面
    //1号车车身绘画
    QPen cardraw1(QColor(255,255,255));
    m_painter->setPen(cardraw1);
    cardraw1.setWidth(2);
    m_painter->setBrush(Qt::NoBrush);
    m_painter->setPen(cardraw1);

    int p_a1_x,p_a1_y,p_b1_x,p_b1_y,p_c1_x,p_c1_y,p_d1_x,p_d1_y,L2 = 60, W2 = 40;

     p_a1_x=x1+(-L2/2)*cos(theta1)-(W2/2)*sin(theta1);
     p_a1_y=yy1+(-L2/2)*sin(theta1)+(W2/2)*cos(theta1);
     p_b1_x=x1+(L2/2)*cos(theta1)-(W2/2)*sin(theta1);
     p_b1_y=yy1+(L2/2)*sin(theta1)+(W2/2)*cos(theta1);
     p_c1_x=x1+(L2/2)*cos(theta1)-(-W2/2)*sin(theta1);
     p_c1_y=yy1+(L2/2)*sin(theta1)+(-W2/2)*cos(theta1);
     p_d1_x=x1+(-L2/2)*cos(theta1)-(-W2/2)*sin(theta1);
     p_d1_y=yy1+(-L2/2)*sin(theta1)+(-W2/2)*cos(theta1);

     m_painter->drawLine(QPoint(p_a1_x,p_a1_y) , QPoint(p_b1_x,p_b1_y));
     m_painter->drawLine(QPoint(p_a1_x,p_a1_y) , QPoint(p_d1_x,p_d1_y));
     m_painter->drawLine(QPoint(p_c1_x,p_c1_y) , QPoint(p_b1_x,p_b1_y));
     m_painter->drawLine(QPoint(p_c1_x,p_c1_y) , QPoint(p_d1_x,p_d1_y));

     QPen line1(QColor(20,100,20));
     line1.setWidth(3);
     m_painter->setPen(line1);
     m_painter->drawLine(QPoint((p_a1_x+p_b1_x)/2,(p_a1_y+p_b1_y)/2) , QPoint((p_b1_x+p_c1_x)/2,(p_b1_y+p_c1_y)/2));
     m_painter->drawLine(QPoint((p_c1_x+p_d1_x)/2,(p_c1_y+p_d1_y)/2) , QPoint((p_b1_x+p_c1_x)/2,(p_b1_y+p_c1_y)/2));


//     QBrush brush1;
//     m_painter->setBrush(Qt::Dense3Pattern);
//     m_painter->setPen(Qt::black);
//     m_painter->drawLine(QPoint(p_a1_x,p_a1_y) , QPoint(p_b1_x,p_b1_y));
//     m_painter->drawLine(QPoint(p_a1_x,p_a1_y) , QPoint(p_d1_x,p_d1_y));
//     m_painter->drawLine(QPoint(p_c1_x,p_c1_y) , QPoint(p_b1_x,p_b1_y));
//     m_painter->drawLine(QPoint(p_c1_x,p_c1_y) , QPoint(p_d1_x,p_d1_y));

     QBrush brush;

     if(p1 == 0)
     {
     m_painter->setBrush(Qt::yellow);
     m_painter->setPen(Qt::darkYellow);
     }
     else if(p1 == 1)
     {
     m_painter->setBrush(Qt::red);
     m_painter->setPen(Qt::darkRed);
     }
     else if(p1 == 2)
     {
     m_painter->setBrush(Qt::green);
     m_painter->setPen(Qt::green);
     }
     m_painter->drawEllipse(QPoint(x1,yy1),15,15);

     //2号车车身绘画
     QPen cardraw2(QColor(255,255,255));
     m_painter->setPen(cardraw2);
     cardraw2.setWidth(2);
     m_painter->setBrush(Qt::NoBrush);
     m_painter->setPen(cardraw2);
     int p_a2_x,p_a2_y,p_b2_x,p_b2_y,p_c2_x,p_c2_y,p_d2_x,p_d2_y,L3 = 60, W3 = 40;

      p_a2_x=x2 + (-L3/2) * cos(theta2) - (W3/2)  * sin(theta2);
      p_a2_y=yy2 + (-L3/2) * sin(theta2) + (W3/2)  * cos(theta2);
      p_b2_x=x2 + (L3/2)  * cos(theta2) - (W3/2)  * sin(theta2);
      p_b2_y=yy2 + (L3/2)  * sin(theta2) + (W3/2)  * cos(theta2);
      p_c2_x=x2 + (L3/2)  * cos(theta2) - (-W3/2) * sin(theta2);
      p_c2_y=yy2 + (L3/2)  * sin(theta2) + (-W3/2) * cos(theta2);
      p_d2_x=x2 + (-L3/2) * cos(theta2) - (-W3/2) * sin(theta2);
      p_d2_y=yy2 + (-L3/2) * sin(theta2) + (-W3/2) * cos(theta2);


      m_painter->drawLine(QPoint(p_a2_x,p_a2_y) , QPoint(p_b2_x,p_b2_y));
      m_painter->drawLine(QPoint(p_a2_x,p_a2_y) , QPoint(p_d2_x,p_d2_y));
      m_painter->drawLine(QPoint(p_c2_x,p_c2_y) , QPoint(p_b2_x,p_b2_y));
      m_painter->drawLine(QPoint(p_c2_x,p_c2_y) , QPoint(p_d2_x,p_d2_y));
      QPen line2(QColor(100,10,10));
      line2.setWidth(3);
      m_painter->setPen(line2);
      m_painter->drawLine(QPoint((p_a2_x+p_b2_x)/2,(p_a2_y+p_b2_y)/2) , QPoint((p_b2_x+p_c2_x)/2,(p_b2_y+p_c2_y)/2));
      m_painter->drawLine(QPoint((p_c2_x+p_d2_x)/2,(p_c2_y+p_d2_y)/2) , QPoint((p_b2_x+p_c2_x)/2,(p_b2_y+p_c2_y)/2));


//      QBrush brush2;
//      m_painter->setBrush(Qt::Dense3Pattern);
//      m_painter->setPen(Qt::black);
//      m_painter->drawLine(QPoint(p_a2_x,p_a2_y) , QPoint(p_b2_x,p_b2_y));
//      m_painter->drawLine(QPoint(p_a2_x,p_a2_y) , QPoint(p_d2_x,p_d2_y));
//      m_painter->drawLine(QPoint(p_c2_x,p_c2_y) , QPoint(p_b2_x,p_b2_y));
//      m_painter->drawLine(QPoint(p_c2_x,p_c2_y) , QPoint(p_d2_x,p_d2_y));



      QBrush brush3;


      if(p2 == 1)
      {
      m_painter->setBrush(Qt::red);
      m_painter->setPen(Qt::darkRed);
      }
      else
      {
      m_painter->setBrush(Qt::green);
      m_painter->setPen(Qt::green);
      }
      m_painter->drawEllipse(QPoint(x2,yy2),15,15);


      //3号车车身绘画
      QPen cardraw3(QColor(255,255,255));
      m_painter->setPen(cardraw3);
      cardraw3.setWidth(2);
      m_painter->setBrush(Qt::NoBrush);
      m_painter->setPen(cardraw3);
      int p_a3_x,p_a3_y,p_b3_x,p_b3_y,p_c3_x,p_c3_y,p_d3_x,p_d3_y,L4 = 60, W4 = 40;

       p_a3_x=x3 + (-L4/2) * cos(theta3) - (W4/2)  * sin(theta3);
       p_a3_y=yy3 + (-L4/2) * sin(theta3) + (W4/2)  * cos(theta3);
       p_b3_x=x3 + (L4/2)  * cos(theta3) - (W4/2)  * sin(theta3);
       p_b3_y=yy3 + (L4/2)  * sin(theta3) + (W4/2)  * cos(theta3);
       p_c3_x=x3 + (L4/2)  * cos(theta3) - (-W4/2) * sin(theta3);
       p_c3_y=yy3 + (L4/2)  * sin(theta3) + (-W4/2) * cos(theta3);
       p_d3_x=x3 + (-L4/2) * cos(theta3) - (-W4/2) * sin(theta3);
       p_d3_y=yy3 + (-L4/2) * sin(theta3) + (-W4/2) * cos(theta3);


       m_painter->drawLine(QPoint(p_a3_x,p_a3_y) , QPoint(p_b3_x,p_b3_y));
       m_painter->drawLine(QPoint(p_a3_x,p_a3_y) , QPoint(p_d3_x,p_d3_y));
       m_painter->drawLine(QPoint(p_c3_x,p_c3_y) , QPoint(p_b3_x,p_b3_y));
       m_painter->drawLine(QPoint(p_c3_x,p_c3_y) , QPoint(p_d3_x,p_d3_y));
       QPen line3(QColor(60,200,120));
       line3.setWidth(3);
       m_painter->setPen(line3);
       m_painter->drawLine(QPoint((p_a3_x+p_b3_x)/2,(p_a3_y+p_b3_y)/2) , QPoint((p_b3_x+p_c3_x)/2,(p_b3_y+p_c3_y)/2));
       m_painter->drawLine(QPoint((p_c3_x+p_d3_x)/2,(p_c3_y+p_d3_y)/2) , QPoint((p_b3_x+p_c3_x)/2,(p_b3_y+p_c3_y)/2));


//       QBrush brush5;
//       m_painter->setBrush(Qt::Dense3Pattern);
//       m_painter->setPen(Qt::black);
//       m_painter->drawLine(QPoint(p_a3_x,p_a3_y) , QPoint(p_b3_x,p_b3_y));
//       m_painter->drawLine(QPoint(p_a3_x,p_a3_y) , QPoint(p_d3_x,p_d3_y));
//       m_painter->drawLine(QPoint(p_c3_x,p_c3_y) , QPoint(p_b3_x,p_b3_y));
//       m_painter->drawLine(QPoint(p_c3_x,p_c3_y) , QPoint(p_d3_x,p_d3_y));



       QBrush brush6;


       if(p3 == 1)
       {
       m_painter->setBrush(Qt::red);
       m_painter->setPen(Qt::darkRed);
       }
       else
       {
       m_painter->setBrush(Qt::green);
       m_painter->setPen(Qt::green);
       }
       m_painter->drawEllipse(QPoint(x3,yy3),15,15);


       //4号小车绘画
       QPen cardraw4(QColor(255,255,255));
       m_painter->setPen(cardraw4);
       cardraw4.setWidth(2);
       m_painter->setBrush(Qt::NoBrush);
       m_painter->setPen(cardraw4);
        int p_a4_x,p_a4_y,p_b4_x,p_b4_y,p_c4_x,p_c4_y,p_d4_x,p_d4_y,L8 = 60, W8 = 40;

        p_a4_x=x4 + (-L8/2) * cos(theta4) - (W8/2)  * sin(theta4);
        p_a4_y=yy4 + (-L8/2) * sin(theta4) + (W8/2)  * cos(theta4);
        p_b4_x=x4 + (L8/2)  * cos(theta4) - (W8/2)  * sin(theta4);
        p_b4_y=yy4 + (L8/2)  * sin(theta4) + (W8/2)  * cos(theta4);
        p_c4_x=x4 + (L8/2)  * cos(theta4) - (-W8/2) * sin(theta4);
        p_c4_y=yy4 + (L8/2)  * sin(theta4) + (-W8/2) * cos(theta4);
        p_d4_x=x4 + (-L8/2) * cos(theta4) - (-W8/2) * sin(theta4);
        p_d4_y=yy4 + (-L8/2) * sin(theta4) + (-W8/2) * cos(theta4);


        m_painter->drawLine(QPoint(p_a4_x,p_a4_y) , QPoint(p_b4_x,p_b4_y));
        m_painter->drawLine(QPoint(p_a4_x,p_a4_y) , QPoint(p_d4_x,p_d4_y));
        m_painter->drawLine(QPoint(p_c4_x,p_c4_y) , QPoint(p_b4_x,p_b4_y));
        m_painter->drawLine(QPoint(p_c4_x,p_c4_y) , QPoint(p_d4_x,p_d4_y));
        QPen line4(QColor(20,100,120));
        line4.setWidth(3);
        m_painter->setPen(line4);
        m_painter->drawLine(QPoint((p_a4_x+p_b4_x)/2,(p_a4_y+p_b4_y)/2) , QPoint((p_b4_x+p_c4_x)/2,(p_b4_y+p_c4_y)/2));
        m_painter->drawLine(QPoint((p_c4_x+p_d4_x)/2,(p_c4_y+p_d4_y)/2) , QPoint((p_b4_x+p_c4_x)/2,(p_b4_y+p_c4_y)/2));


//        QBrush brush9;
//        m_painter->setBrush(Qt::Dense3Pattern);
//        m_painter->setPen(Qt::black);
//        m_painter->drawLine(QPoint(p_a4_x,p_a4_y) , QPoint(p_b4_x,p_b4_y));
//        m_painter->drawLine(QPoint(p_a4_x,p_a4_y) , QPoint(p_d4_x,p_d4_y));
//        m_painter->drawLine(QPoint(p_c4_x,p_c4_y) , QPoint(p_b4_x,p_b4_y));
//        m_painter->drawLine(QPoint(p_c4_x,p_c4_y) , QPoint(p_d4_x,p_d4_y));



        QBrush brush10;


        if(p4 == 1)
        {
        m_painter->setBrush(Qt::red);
        m_painter->setPen(Qt::darkRed);
        }
        else
        {
        m_painter->setBrush(Qt::green);
        m_painter->setPen(Qt::green);
        }
        m_painter->drawEllipse(QPoint(x4,yy4),15,15);

        update();

}
