#include "firstwindow2.h"
#include "ui_firstwindow2.h"
#include "login.h"
//#include "ui_login.h"
#include "global_variables.h"
#include "login2.h"
#include "ui_login2.h"

firstwindow2::firstwindow2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::firstwindow2)
{
    ui->setupUi(this);
    this->setWindowTitle("多AMR调度控制系统");
}

firstwindow2::~firstwindow2()
{
    delete ui;
}
void firstwindow2::on_pushButton_clicked()
{
    log = new login2;
    log->show();
    ui_num = 0;
}
void firstwindow2::on_pushButton_2_clicked()
{
    log = new login2;
    log->show();
     ui_num = 1;
}
void firstwindow2::on_pushButton_3_clicked()
{
    log = new login2;
    log->show();
     ui_num = 2;
}
void firstwindow2::on_pushButton_4_clicked()
{
    log = new login2;
    log->show();
     ui_num = 3;
}
void firstwindow2::on_pushButton_5_clicked()
{
    log = new login2;
     ui_num = 4;
    log->show();
}
void firstwindow2::on_pushButton_6_clicked()
{
    log = new login2;
    log->show();
     ui_num = 5;
}
void firstwindow2::on_pushButton_7_clicked()
{
    log = new login2;
    log->show();
     ui_num = 6;
}
void firstwindow2::on_pushButton_8_clicked()
{
    log = new login2;
    log->show();
     ui_num = 7;
}
