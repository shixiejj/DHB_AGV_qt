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
    ~DRAWmap();

protected:
    void paintEvent(QPaintEvent* event);

private:
    QPen m_drawPen;
    QPainter* m_painter;
};

#endif // DRAWMAP_H
