#ifndef DEVICE_CON_H
#define DEVICE_CON_H

#include <QWidget>

namespace Ui {
class device_con;
}

class device_con : public QWidget
{
    Q_OBJECT

public:
    explicit device_con(QWidget *parent = 0);
    ~device_con();

    void paintEvent(QPaintEvent *);



private:
    Ui::device_con *ui;
};

#endif // DEVICE_CON_H
