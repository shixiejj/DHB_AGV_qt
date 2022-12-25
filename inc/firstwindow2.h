#ifndef FIRSTWINDOW2_H
#define FIRSTWINDOW2_H
#include "login.h"

#include "login2.h"
#include <QDialog>

namespace Ui {
class firstwindow2;
}

class firstwindow2 : public QDialog
{
    Q_OBJECT

public:
    explicit firstwindow2(QWidget *parent = 0);
    ~firstwindow2();

    login2 *log;

private slots:
    void on_pushButton_clicked();

private:
    Ui::firstwindow2 *ui;

};

#endif // FIRSTWINDOW2_H
