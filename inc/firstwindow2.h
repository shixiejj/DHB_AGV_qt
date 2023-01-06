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
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();

private:
    Ui::firstwindow2 *ui;

};

#endif // FIRSTWINDOW2_H
