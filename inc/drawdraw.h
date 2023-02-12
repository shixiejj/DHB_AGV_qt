#ifndef DRAWDRAW_H
#define DRAWDRAW_H

#include <QWidget>
#include <QPen>
#include <QPainter>

class DRAWmap : public QWidget
{
    Q_OBJECT

public:
    DRAWmap(QWidget *parent = 0);
    void GainChange(double scale);
    ~DRAWmap();

protected:
    void paintEvent(QPaintEvent* event);

private:
    QPen m_drawPen;
    QPainter* m_painter;
    double gain;    //不同页面不同比例地
};

#endif // DRAWMAP_H
