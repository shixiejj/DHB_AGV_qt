#ifndef LOGIN2_H
#define LOGIN2_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class login2;
}

class login2 : public QDialog
{
    Q_OBJECT

public:
    explicit login2(QWidget *parent = 0);
    ~login2();
    MainWindow *m;  

private slots:
    void on_pushButton_clicked();

private:
    Ui::login2 *ui;
};

class temp{
    public:
        static bool optEnable;
};

#endif // LOGIN2_H
